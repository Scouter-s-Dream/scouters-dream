import cv2

def click_event(event, x, y, flags, params):
    if event == cv2.EVENT_LBUTTONDOWN:
        print(x, ' ', y)

cap = cv2.VideoCapture(r'Final 1 dis 1 ISR - Made with Clipchamp.mp4')
object_detector = cv2.createBackgroundSubtractorMOG2(100, 200, False)

detections = []
  
while True:
    ret, frame = cap.read()
    roi = frame[240:504, 151:1217] 
    
    mask = object_detector.apply(roi)
    
    cv2.imshow('Mask', mask)
    
    contours, hierarchy = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    
    for cnt in contours:
        area = cv2.contourArea(cnt)
        
        if area > 400:
            x, y, w, h = cv2.boundingRect(cnt)
            cv2.rectangle(roi, (x, y), (x + w, y + h), (0, 255, 0), 3)
            detections.append([x, y, w, h])
            
    cv2.imshow('Frame', frame)

    cv2.setMouseCallback('Frame', click_event)

    key = cv2.waitKey(1)
    
    if key == ord('q'):
        break
    
cv2.destroyAllWindows()
cap.release()