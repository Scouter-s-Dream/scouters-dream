import cv2
from time import time
import numpy as np
import scipy.spatial


def show_pixel_location(event, x, y, flags, params):
    """
    Callback function to display pixel coordinates upon left mouse button click.

    Args:
    ----
    - event: The event type (e.g., cv2.EVENT_LBUTTONDOWN).
    - x: X-coordinate of the clicked pixel.
    - y: Y-coordinate of the clicked pixel.
    - flags: Additional event flags.
    - params: Additional parameters (not in use, but this param is required by OpenCV).
    """
    if event == cv2.EVENT_LBUTTONDOWN:
        print(x, ' ', y)


def show_fps(frame, time_then):
    """
    Display the frames per second (FPS) on a given frame.

    Args:
    ----
    - frame: The frame to display FPS on.
    - time_then: The timestamp of the previous frame for FPS calculation.
    """
    fps = 1 / (time() - time_then)
    cv2.putText(frame, f'FPS: {fps:.2f}', (0, 25),
                cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)


def skip_frames(cap, skip_frames: int):
    """
    Skip a specified number of frames in a video capture object.
    
    Args:
    ----
    - cap: Video capture object.
    - skip_frames: Number of frames to skip.
    """
    for _ in range(skip_frames):
        cap.read()

def center(position: tuple[np.ndarray, np.ndarray]) -> np.ndarray[int, int]:
    """`finds the center of a rectangle.`

    Args:
        position (tuple[np.ndarray, np.ndarray]): points of the bounding rect (leftTop and rightBottom).

    Returns:
        np.ndarray[int, int]: the center of the rectangle.
    """
    x_center = (position[0][0] + position[1][0]) / 2
    y_center = (position[0][1] + position[1][1]) / 2
    return np.array([x_center, y_center], dtype=np.uint32)


def distance(pointA: np.ndarray, pointB:np.ndarray) -> float:
    """calculates the distance between two points.

    Args:
        pointA (np.ndarray): the first 2D point.
        pointB (np.ndarray): the seconds 2D point.   

    Returns:
        float: the distance between the two points.
    """
    return scipy.spatial.distance.euclidean(pointA, pointB)