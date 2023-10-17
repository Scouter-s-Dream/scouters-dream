from ultralytics import YOLO

class SdUtils:
    """
    ## Utility class for handling basic (but ugly) operations in SD's (scouter's dream) tracking system.
    ---
    """

    @staticmethod
    def setup_trajectories(robot_mapping):
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
    def setup_model():
        """
        ## Set up the YOLO model with pre-trained weights.
        ----
        Returns:
        ---
           - YOLO: The YOLO model configured with pre-trained weights.
        """
        return YOLO(r"bumper_weights\v3\best (2).pt")

    @staticmethod
    def map_tracker_ids(robot_mapping, id_list):
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
