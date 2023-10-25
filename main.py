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
        2: '1690',
        3: '5990',
        4: '2630',
        5: '1577',
        6: '1576'
    }

    trajectories = sdu.setup_trajectories(id_to_robot_number)

    model = sdu.setup_model()

    source = r'test_videos\dis 1 final 1.mp4'

    for idx, result in enumerate(model.track(source=source, show=False, stream=True, verbose=False)):
        frame = result.orig_img

        data = []
        missing_id = -1
        
        legitimate_ids = set(id_to_robot_number.keys())
        current_ids = set(result.boxes.id.tolist())
        
        bad_robots = current_ids.difference(legitimate_ids)
        
        print('===========Number of iteration: %s===========' % idx)
        
        if legitimate_ids.issubset(current_ids) and bad_robots:
            print('False Positives detected %s' % bad_robots)  
            print(f'Current len: {len(current_ids)}')

            for idx in range(6):
                try: 
                    data.append(torch.cat((result.boxes.xyxy[idx][0].reshape(1), result.boxes.xyxy[idx][1].reshape(1), result.boxes.xyxy[idx][2].reshape(1), result.boxes.xyxy[idx][3].reshape(1),
                    result.boxes.id[idx].reshape(1), result.boxes.conf[idx].reshape(1), result.boxes.cls[idx].reshape(1))))
                    print(f'Appended Data {data[-1]}')
                except Exception as e:
                    print(f'Error {e}') 
                    
            print('Removed bad Robots')
            
            modified_data = torch.stack(data)
            result.update(modified_data)

            data.clear()
            bad_robots.clear()
            
        elif bad_robots:
            print(f'{bad_robots} in result.boxes.id')
            print(f'{result.boxes.id=}')
            bad_id = bad_robots.pop()            
            
            for i in id_to_robot_number.keys():
                if torch.tensor(i) not in result.boxes.id:
                    missing_id = i
                    print(f'{i=}')
                    break

            print("Missing Robot id: %s" % missing_id)

            for idx, tensor in enumerate(result.boxes.id):
                try:
                    if torch.tensor(bad_id) == result.boxes.id[idx]:
                        print("Found bad id: %s" % bad_id)
                        data.append(torch.cat((result.boxes.xyxy[idx][0].reshape(1), result.boxes.xyxy[idx][1].reshape(1), result.boxes.xyxy[idx][2].reshape(1), result.boxes.xyxy[idx][3].reshape(1),
                                    torch.tensor([missing_id]).reshape(1), result.boxes.conf[idx].reshape(1), result.boxes.cls[idx].reshape(1))))
                        print(f'Appended Data Without Bad Id {data[-1]}')
                    else:
                        data.append(torch.cat((result.boxes.xyxy[idx][0].reshape(1), result.boxes.xyxy[idx][1].reshape(1), result.boxes.xyxy[idx][2].reshape(1), result.boxes.xyxy[idx][3].reshape(1),
                                    result.boxes.id[idx].reshape(1), result.boxes.conf[idx].reshape(1), result.boxes.cls[idx].reshape(1))))
                        print(f'Appended Data {data[-1]}')
                except Exception as e:
                    print(f'Error {e}')

            modified_data = torch.stack(data)

            result.update(modified_data)
            
            data.clear()
            bad_robots.clear()
            
        print(f'Updated ids: {result.boxes.id}')
            
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
