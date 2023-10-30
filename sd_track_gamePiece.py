import cv2
import supervision as sv
from sd_heatmap_utils import Qual
from sd_tracking_utils import SdUtils as sdu
import platform
from time import time
import sd_utils as utils

def main():
    box_annotator = sv.BoxAnnotator(
        thickness=2,
        text_thickness=1,
        text_scale=0.35
    )

    id_to_robot_number = {
        1: '1943',
        2: '5990',
        3: '1577',
        4: '1576',
        5: '1690',
        6: '2630'
    }
    
    trajectories = sdu.setup_trajectories(id_to_robot_number)

    lost_robots = {}
    current_robots = set()
    bad_robots = set()
    
    
    model = sdu.setup_model("bumper_weights/v4/best (3).pt")

    source = r'test_videos\dis 1 final 1.mp4' if platform.system() == "Windows" else './test_videos/d1FinalFull.mp4'
    
    cap = cv2.VideoCapture(source)
    # for result in model.track(source=source, show=False, stream=True, verbose=False):
            
        # success, frame = cap.read()
        
        # if success:    
        #     frame = cv2.resize(frame, (640, 640))
        #     frame = frame[230:487]
    for result in model.track(source=source, show=False, stream=True, verbose=False):
                
        frame = result.orig_img
        detections = sv.Detections.from_yolov8(result)
    
        if result.boxes.id is not None:
            detections.tracker_id = sdu.map_tracker_ids(id_to_robot_number, result.boxes.id.cpu().numpy())
                        
            bad_robots = set(detections.tracker_id) - set(id_to_robot_number.values())
                                    
            for detection, tracker_id in zip(detections.xyxy, detections.tracker_id):
                current_robots.add(tracker_id)
                                
                if lost_robots and bad_robots:
                    print(f'Lost Robot: {lost_robots} Bad Robot: {bad_robots}')
                    print(f'Bad Robot? {detections.tracker_id[-1]}')

                else:
                    x1, y1, x2, y2 = detection
                    
                    try:
                        center_x = (x1 + x2) // 2
                        center_y = (y1 + y2) // 2
                        
                        trajectories[tracker_id].append((center_x, center_y))
                    except:
                        pass
                
            lost_robots = set(id_to_robot_number.values()) - set(current_robots)
            current_robots.clear()
                
        labels = [
            f'Robot: {tracker_id} Conf:{confidence:.2f}'
            for _, confidence, _, tracker_id 
            in detections
        ]
        
        frame = box_annotator.annotate(
            scene=frame,
            detections=detections,
            labels=labels
        )
        
        # utils.show_fps(frame, start_time )

        cv2.imshow('Final-1-Dis-1', frame)
        

        if (cv2.waitKey(1) == ord('q')):
            break

    cv2.destroyAllWindows()
    
    qual = Qual(1, [5990, 1943, 2630], [1690, 1576, 1577])
    
    
if __name__ == "__main__":
    main()
