import cv2

def mouse_callback(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        print(f"Clicked pixel coordinates: ({x}, {y})")

cap = cv2.VideoCapture(r'test_videos\y2mate.is - Match 5 (R2) - 2023 ISR District Event #4-AVFERc-CEwQ-720p-1692187241.mp4')

while True:
    ret, frame = cap.read()
    
    cv2.imshow('Frame', frame)
    key = cv2.waitKey(1)

    cv2.setMouseCallback('Frame', mouse_callback)
    
    if key == 27:
        break

cv2.destroyAllWindows()
