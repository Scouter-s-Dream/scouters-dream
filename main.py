import cv2
import numpy as np
from ultralytics import YOLO
from deep_sort_realtime.deepsort_tracker import DeepSort
from time import time
from sd_utills import show_pixel_location, show_fps, skip_frames, Qual

bumper_model = YOLO(r'bumper_weights\best.pt')
tracker = DeepSort(max_iou_distance=10, max_age=10)
threshold = 0.3

cap = cv2.VideoCapture(r'test_videos\Final 1 dis 1 ISR - Made with Clipchamp.mp4')
frame_count = 0

start = time()

robot_numbers = [5990, 1943, 1690, 2630, 1576, 1577]
tracked_robots = {}

robot_trajectories = {robot_id: [] for robot_id in robot_numbers}

while True:
    ret, frame = cap.read()
    
    skip_frames(cap, skip_frames=5)
    
    fps_start = time()

    if not ret:
        break

    roi = frame[240:504, 151:1217]  # DIS 1 ROI

    results = bumper_model(roi)[0]

    detections = []
    
    for result in results.boxes.data.tolist():
        x1, y1, x2, y2, score, class_id = result
        
        if score > threshold:
            cv2.rectangle(roi, (int(x1), int(y1)), (int(x2), int(y2)), (0, 255, 0), 2)
                        
        det_frame = roi[int(y1):int(y2), int(x1):int(x2)]
        
        detections.append([[x1, y1, x2 - x1, y2 - y1], score, class_id])
        
    tracks = tracker.update_tracks(detections, frame=roi)

    for track in tracks:
        if not track.is_confirmed():
            continue
        
        track_id = track.track_id

        if track_id not in tracked_robots:
            if len(tracked_robots) >= 6:
                continue

            custom_id = robot_numbers[len(tracked_robots)]
            tracked_robots[track_id] = custom_id
        
        custom_id = tracked_robots[track_id]
        
        ltrb = track.to_ltrb()
        
        xmin, ymin, xmax, ymax = int(ltrb[0]), int(ltrb[1]), int(ltrb[2]), int(ltrb[3])
        
        cv2.rectangle(roi, (xmin, ymin), (xmax, ymax), (0, 255, 0), 2)
        cv2.rectangle(roi, (xmin, ymin - 25), (xmin + 50, ymin), (0, 255, 0), -1)
        
        cv2.putText(roi, str(custom_id), (xmin + 5, ymin - 8),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
        
        robot_trajectories[custom_id].append((xmin + (xmax - xmin) / 2, ymin + (ymax - ymin) / 2))

                    
    show_fps(frame, fps_start)

    cv2.imshow('Frame', frame)

    cv2.setMouseCallback('Frame', show_pixel_location)

    key = cv2.waitKey(1)

    if key == ord('q'):
        break

cv2.destroyAllWindows()
cap.release()

overall_time = (time() - start) / 60

print('Time minutes: {:.2f}'.format(overall_time))

qual = Qual(1, [5990, 1943, 2630], [1690, 1576, 1577])

qual.generate_heatmap(roi, robot_trajectories, robot_numbers, pixel_size=10)