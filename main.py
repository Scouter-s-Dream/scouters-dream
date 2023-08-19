import cv2
from ultralytics import YOLO

def click_event(event, x, y, flags, params):
    if event == cv2.EVENT_LBUTTONDOWN:
        print(x, ' ', y)
        
model = YOLO(r'weights\best.pt')
cap = cv2.VideoCapture(r'test_videos\Final 1 dis 1 ISR - Made with Clipchamp.mp4')
object_detector = cv2.createBackgroundSubtractorMOG2(100, 100, False)

detections = []

while True:
    ret, frame = cap.read()
    roi = frame[240:504, 151:1217] ## DIS 1 ROI
    # roi = frame[191:406, 161:1200] ## DIS 4 ROI 
    
    mask = object_detector.apply(roi)

    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3, 3))
    mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)

    cv2.imshow('Mask', mask)

    detections.clear()

    contours, hierarchy = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    for cnt in contours:
        area = cv2.contourArea(cnt)

        if area > 700:
            x, y, w, h = cv2.boundingRect(cnt)
            detections.append([x, y, w, h])

    detections.sort(key=lambda det: det[2] * det[3], reverse=True)

    for det in detections[:6]:
        x, y, w, h = det
        cv2.rectangle(roi, (x, y), (x + w, y + h), (0, 255, 0), 3)

        det_frame = roi[y:y + h, x:x + w]
        
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
