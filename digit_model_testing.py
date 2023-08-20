from ultralytics import YOLO
import cv2

model = YOLO(r'digit_weights\best.pt')
threshold = 0.2
img = cv2.imread(r'test_images\close robot.png')
    
results = model(img)[0]

for result in results.boxes.data.tolist():
    x1, y1, x2, y2, score, class_id = result
    
    if score > threshold:
        cv2.rectangle(img, (int(x1), int(y1)), (int(x2), int(y2)), (0, 255, 0), 4)
        cv2.putText(img, results.names[int(class_id)].upper(), (int(x1), int(y1 - 10)),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.4, (0, 255, 0), 3, cv2.LINE_AA)
                    
cv2.imshow('Img', img)

cv2.waitKey(0)