import cv2
import supervision as sv

from sd_heatmap_utils import Qual
from sd_tracking_utils import SdUtils as sdu
from sd_utils import got_cuda

def main():
    print(f'{got_cuda()=}')

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

    model = sdu.setup_model(r"bumper_weights\v4\best (3).pt")

    source = r'test_videos\dis 1 final 1.mp4'

    for idx, result in enumerate(model.track(source=source, show=False, stream=True, verbose=False)):
        frame = result.orig_img

        data = []
        missing_id = -1

        legitimate_ids = sdu.get_legitimate_ids(id_to_robot_number)
        current_ids = sdu.get_current_ids(result)

        bad_robots = sdu.get_bad_robot_ids(current_ids, legitimate_ids)

        print('===========Number of iteration: %s===========' % idx)

        if legitimate_ids.issubset(current_ids) and bad_robots:
            print('False Positives detected %s' % bad_robots)
            print(f'Current len: {len(current_ids)}')

            data = sdu.remove_false_detections_from_list(data, result)
            
            sdu.update_yolo_result(data, result)

            data.clear()
            bad_robots.clear()

        elif bad_robots:
            missing_id, bad_id = sdu.find_lost_robot_id(bad_robots, result.boxes.id, id_to_robot_number)

            print("Missing Robot id: %s" % missing_id)

            data = sdu.process_result_list(result, bad_id, missing_id)

            sdu.update_yolo_result(data, result)

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
