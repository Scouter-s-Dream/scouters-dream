import cv2
from ultralytics import YOLO

bumper_model = YOLO(r'bumper_weights\best.pt')
tracker = DeepSort(max_iou_distance=10, max_age=100)
cap = cv2.VideoCapture(r'test_videos\Final 1 dis 1 ISR - Made with Clipchamp.mp4')
object_detector = cv2.createBackgroundSubtractorMOG2(100, 100, False)

detections = []

while True:
    ret, frame = cap.read()
    for result in results.boxes.data.tolist():
        x1, y1, x2, y2, score, class_id = result
        
        if score > threshold:
            cv2.rectangle(roi, (int(x1), int(y1)), (int(x2), int(y2)), (0, 255, 0), 2)
                        
        det_frame = roi[int(y1):int(y2), int(x1):int(x2)]
        
        detections.append([[x1, y1, x2 - x1, y2 - y1], score, class_id])
        
        
        results = model(det_frame)[0]

        for result in results.boxes.data.tolist():
            x1, y1, x2, y2, score, class_id = result
            
            cv2.rectangle(det_frame, (int(x1), int(y1)), (int(x2), int(y2)), (0, 0, 0), 1)
            cv2.putText(det_frame, results.names[int(class_id)].upper(), (int(x1), int(y1 - 10)),
            cv2.FONT_HERSHEY_SIMPLEX, 0.4, (0, 0, 255), 2, cv2.LINE_AA)
            
    cv2.imshow('Frame', frame)

    cv2.setMouseCallback('Frame', click_event)

    key = cv2.waitKey(1)

    if key == ord('q'):
        break

cv2.destroyAllWindows()
cap.release()
