import cv2
from ultralytics import YOLO
import supervision as sv
from sd_utills import Qual

def main():
    box_annotator = sv.BoxAnnotator(
        thickness=2,
        text_thickness=1,
        text_scale=0.35
    )
    
    id_to_robot_number = {
        1: '5990',
        2: '1943',
        3: '1577',
        4: '1576',
        5: '1690',
        6: '2630'
    }
    
    trajectories = {robot_id: [] for robot_id in id_to_robot_number.values()}
    
    model = YOLO(r"bumper_weights\best.pt")

    source = r'test_videos\Final 1 dis 1 ISR - Made with Clipchamp.mp4'
    
    for result in model.track(source=source, show=False, stream=True):
        frame = result.orig_img
        
        detections = sv.Detections.from_yolov8(result)
        
        if result.boxes.id is not None:
            detections.tracker_id = [id_to_robot_number.get(int(id), id) for id in result.boxes.id.cpu().numpy()]
            
            for detection, tracker_id in zip(detections.xyxy, detections.tracker_id):
                x1, y1, x2, y2 = detection

                center_x = (x1 + x2) // 2
                center_y = (y1 + y2) // 2

                trajectories[tracker_id].append((center_x, center_y))
                
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
        
        cv2.imshow('Final-1-Dis-1', frame)
        
        if (cv2.waitKey(1) == ord('q')):
            break
    
    cv2.destroyAllWindows()
    
    qual = Qual(1, [5990, 1943, 2630], [1690, 1576, 1577])
    
    qual.generate_heatmap(frame, trajectories, list(id_to_robot_number.values()), pixel_size=10)

if __name__ == "__main__":
    main()
