import cv2
import supervision as sv
import torch

from sd_heatmap_utils import Qual
from sd_tracking_utils import SdUtils as sdu


def main():
    print(f'{torch.cuda.is_available()=}')

    box_annotator = sv.BoxAnnotator(
        thickness=2,
        text_thickness=1,
        text_scale=0.35
    )

    id_to_robot_number = {
        1: '1943',
        5: '5990',
        4: '1577',
        3: '1576',
        2: '1690',
        6: '2630'
    }

    trajectories = sdu.setup_trajectories(id_to_robot_number)

    model = sdu.setup_model()

    source = r'test_videos\dis 1 final 1.mp4'

    for result in model.track(source=source, show=False, stream=True, verbose=False):
        frame = result.orig_img

        data = []
        missing = -1

        if torch.tensor(7) in result.boxes.id:
            print('7 in result.boxes.id')
            for i in id_to_robot_number.keys():
                if torch.tensor(i) not in result.boxes.id:
                    missing = i
                    break

            print("Missing Robot %s" % missing)

            for idx, tensor in enumerate(result.boxes.id):
                print(f'{idx=}, {tensor=}\n {type(idx)=}, {type(tensor)=}')

                try:
                    if torch.tensor(7) == result.boxes.id[idx]:
                        print("Found 7")
                        data.append(torch.cat((result.boxes.xyxy[idx][0].reshape(1), result.boxes.xyxy[idx][1].reshape(1), result.boxes.xyxy[idx][2].reshape(1), result.boxes.xyxy[idx][3].reshape(1),
                                    torch.tensor([missing]).reshape(1), result.boxes.conf[idx].reshape(1), result.boxes.cls[idx].reshape(1))))
                        print(f'Appended Data {data[-1]}')
                    else:
                        data.append(torch.cat((result.boxes.xyxy[idx][0].reshape(1), result.boxes.xyxy[idx][1].reshape(1), result.boxes.xyxy[idx][2].reshape(1), result.boxes.xyxy[idx][3].reshape(1),
                                    result.boxes.id[idx].reshape(1), result.boxes.conf[idx].reshape(1), result.boxes.cls[idx].reshape(1))))
                        print(f'Appended Data {data[-1]}')
                except Exception as e:
                    print(f'Error {e}')

            modified_data = torch.stack(data)

            result.update(modified_data)
            data.clear()

        detections = sv.Detections.from_ultralytics(result)

        if result.boxes.id is not None:
            detections.tracker_id = sdu.map_tracker_ids(
                id_to_robot_number, result.boxes.id.numpy())

            for detection, tracker_id in zip(detections.xyxy, detections.tracker_id):
                x1, y1, x2, y2 = detection

                try:
                    center_x = (x1 + x2) // 2
                    center_y = (y1 + y2) // 2

                    trajectories[tracker_id].append((center_x, center_y))
                except:
                    pass

        labels = [
            f'Robot: {tracker_id} Conf: {confidence:.2f}'
            for _, _, confidence, _, tracker_id
            in detections
        ]

        frame = box_annotator.annotate(
            scene=frame,
            detections=detections,
            labels=labels
        )

        cv2.imshow('Final-1-Dis-1', frame)

        if (cv2.waitKey(1) == ord('q')):
            break

    cv2.destroyAllWindows()

    qual = Qual(1, [5990, 1943, 2630], [1690, 1576, 1577])

    qual.generate_heatmap(frame, trajectories, list(
        id_to_robot_number.values()), pixel_size=10)


if __name__ == "__main__":
    main()
