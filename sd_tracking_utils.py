from ultralytics import YOLO
import platform
from ultralytics.yolo.engine.results import Results
import torch

class SdUtils:
    """
    ## Utility class for handling basic (but ugly) operations in SD's (scouter's dream) tracking system.
    ---
    """

    @staticmethod
    def setup_trajectories(robot_mapping: dict) -> dict:
        """
        ## Set up an empty trajectory dictionary for each robot.

        Args:
        ----
            - robot_mapping (dict): A mapping of robot IDs to names.

        Returns:
        ---
            - dict: A dictionary with robot names as keys and empty trajectory lists as values.
        """
        return {robot_id: [] for robot_id in robot_mapping.values()}

    @staticmethod
    def setup_model(path: str) -> YOLO:
        """
        ## Set up the YOLO model with pre-trained weights.
        -----
        Args:
        ----
            - path (str): A path to the model weights.
        Returns:
        ---
           - YOLO: The YOLO model configured with pre-trained weights.
        """
        return YOLO(path)

      
    @staticmethod
    def map_tracker_ids(robot_mapping: dict, id_list: list) -> list:
        """
        ## Map tracker IDs to robot names using the provided robot mapping.
        ----
        Args:
        ---- 
            - robot_mapping (dict): A mapping of robot IDs to names.
            - id_list (list): A list of tracker IDs.

        Returns:
        --------
            - list: A list of robot names corresponding to the given tracker IDs.
        """
        return [robot_mapping.get(int(id), id) for id in id_list]

    def find_lost_robot_id(bad_robots: set, result_boxes_id: torch.Tensor, id_to_robot_number: dict) -> tuple:
        """ 
        ## Gets the id and the value of a lost robot in result.boxes.id tensor
        ----
        Args:
        ----
            - bad_robots (set): A set of known bad ids
            - result_boxes_id (torch.Tensor): Tensor containing the IDs of detected robots.
            - id_to_robot_number (dict): A mapping of robot IDs to names used to represent the good robot ids/values.

        Returns:
        --------
            - tuple: A tuple containing the missing robot's ID and the ID of the lost robot.
        """

        print(f'{bad_robots} in result.boxes.id')
        print(f'{result_boxes_id=}')

        # This code can be optimized alotttt but I want to keep it simple until everyhing is 100% working
        bad_id = bad_robots.pop()

        for i in id_to_robot_number.keys():
            if torch.tensor(i) not in result_boxes_id:
                missing_id = i
                print(f'{i=}')
                break

        return missing_id, bad_id

    @staticmethod
    def is_bad_id(id_tensor: torch.Tensor, bad_id: int) -> bool:
        """
        ## Check if the given ID matches the bad ID.
        ----
        Args:
        ----
            - id_tensor (torch.Tensor): Tensor containing an object's ID.
            - bad_id (int): The ID of the bad robot detection.

        Returns:
        -------
            - bool: True if the ID matches the bad ID, False otherwise.
        """
        return torch.tensor(bad_id) == id_tensor

    @staticmethod
    def process_data(xyxy_tensor: torch.Tensor, id_tensor: torch.Tensor, conf_tensor: torch.Tensor, cls_tensor: torch.Tensor) -> torch.Tensor:
        """
        ## Process and concatenate data tensors into a single tensor to achieve the yolo Results obj format.
        ----
        Args:
        ----
            - xyxy_tensor (torch.Tensor): Tensor containing bounding box coordinates.
            - id_tensor (torch.Tensor): Tensor containing object IDs.
            - conf_tensor (torch.Tensor): Tensor containing confidence scores.
            - cls_tensor (torch.Tensor): Tensor containing class labels.

        Returns:
        --------
            - torch.Tensor: A concatenated tensor containing all the input data.
        """
        return (
            torch.cat((xyxy_tensor[0].reshape(1),
                       xyxy_tensor[1].reshape(1),
                       xyxy_tensor[2].reshape(1),
                       xyxy_tensor[3].reshape(1),
                       id_tensor.reshape(1),
                       conf_tensor.reshape(1),
                       cls_tensor.reshape(1))))

    @staticmethod
    def process_data_with_bad_id(xyxy_tensor: torch.Tensor, missing_id: int, conf_tensor: torch.Tensor, cls_tensor: torch.Tensor) -> torch.Tensor:
        """
        ## Process and concatenate data tensors with a missing ID into a single tensor to achieve the yolo Results obj format.
        ----
        Args:
        ----
            - xyxy_tensor (torch.Tensor): Tensor containing bounding box coordinates.
            - missing_id (int): The ID of the missing object.
            - conf_tensor (torch.Tensor): Tensor containing confidence scores.
            - cls_tensor (torch.Tensor): Tensor containing class labels.

        Returns:
        --------
            - torch.Tensor: A concatenated tensor containing all the input data with the missing ID.
        """
        return (
            torch.cat((xyxy_tensor[0].reshape(1),
                       xyxy_tensor[1].reshape(1),
                       xyxy_tensor[2].reshape(1),
                       xyxy_tensor[3].reshape(1),
                       torch.tensor([missing_id]).reshape(1),
                       conf_tensor.reshape(1),
                       cls_tensor.reshape(1))))

    @staticmethod
    def process_result_list(result: Results, bad_id: int, missing_id: int) -> list:
        """
        ## Process a YOLO Results object, filtering out data with a specific bad ID and replacing it with a the data with the missing ID.
        ----
        Args:
        ----
            - result (Results): The Results object containing data to be processed.
            - bad_id (int): The ID of the data to be filtered out.
            - missing_id (int): The ID to replace the filtered data with.

        Returns:
        ----
            - list: A list of processed data tensors with the missing ID.

        """
        data = []

        for idx, tensor in enumerate(result.boxes.id):
            try:
                if SdUtils.is_bad_id(result.boxes.id[idx], bad_id):
                    print("Found bad id: %s" % bad_id)

                    data.append(SdUtils.process_data_with_bad_id(
                        result.boxes.xyxy[idx], missing_id, result.boxes.conf[idx], result.boxes.cls[idx]))
                    print(f'Appended Data Without Bad Id {data[-1]}')
                else:
                    data.append(SdUtils.process_data(
                        result.boxes.xyxy[idx], result.boxes.id[idx], result.boxes.conf[idx], result.boxes.cls[idx]))
                    print(f'Appended Data {data[-1]}')

            except Exception as e:
                print(f'Error {e}')

        return data

    @staticmethod
    def update_yolo_result(data: list, result: Results) -> None:
        """
        ## Update a Results object with the processed data.
        ----
        Args:
        ----
            - data (list): A list of processed data tensors.
            - result (Results): The YOLO Results object to be updated.
        """
        modified_data = torch.stack(data)

        result.update(modified_data)

    @staticmethod
    def remove_false_detections_from_list(data: list, result: Results) -> list:
        """
        ## Remove false detections from a list of data.
        ----
        Args:
        ----
            - data (list): A list of data tensors to be updated.
            - result (Results): The YOLO Results object containing detection data.

        Returns:
        ----
            - list: The updated list of data tensors.

        """
        for idx in range(6):
            try:
                data.append(SdUtils.process_data(
                    result.boxes.xyxy[idx], result.boxes.id[idx], result.boxes.conf[idx], result.boxes.cls[idx]))
                print(f'Appended Data {data[-1]}')
            except Exception as e:
                print(f'Error {e}')

        print('Removed bad Robots')

        return data

    @staticmethod
    def get_legitimate_ids(id_to_robot_number: dict) -> set:
        """
        ## Get the set of legitimate robot IDs from a dictionary.
        ---- 
        Args:
        ----
            - id_to_robot_number (dict): A dictionary mapping IDs to robot numbers.

        Returns:
        ----
            - set: A set of legitimate robot IDs.

        """
        return set(id_to_robot_number.keys())

    @staticmethod
    def get_current_ids(result: Results) -> set:
        """
        ## Get the set of current robot IDs from a Results object.
        ----
        Args:
        ----
            - result (Results): The Results object containing robot IDs.

        Returns:
        ----
            - set: A set of current robot IDs.

        """
        return set(result.boxes.id.tolist())

    def get_bad_robot_ids(current_ids: set, legitimate_ids: set) -> set:
        """
        ## Get the set of bad robot IDs by finding the difference between current IDs and legitimate IDs.
        ----
        Args:
        ----
            - current_ids (set): A set of current robot IDs.
            - legitimate_ids (set): A set of legitimate robot IDs.

        Returns:
        ----
            - set: A set of bad robot IDs.

        """
        return current_ids.difference(legitimate_ids)

    