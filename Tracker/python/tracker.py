import cpp_utils as cpp
import numpy as np

class Tracker():        
    
    @staticmethod
    def YoloToPointsWithClasses(YOLO_result, point_size):
        boxes = YOLO_result.boxes.cpu().numpy()
        xywhWithCls = np.concatenate((boxes.xywh, np.reshape(boxes.cls, (boxes.cls.shape[0], 1))), 1)       
        points = np.array(xywhWithCls[xywhWithCls[:, 0].argsort()], dtype=np.int32).flatten()
        
        return (points, len(points)//point_size)
    
    
    @staticmethod
    def setFuncs():
        
        cpp.lib._Tracker.argtypes = [cpp.int_array, cpp.int, cpp.uint8_t_array, cpp.int, cpp.int, cpp.bool]
        cpp.lib._Tracker.restype = cpp.object
        
        cpp.lib._setTrackPoints.argtypes = [cpp.object, cpp.int_array, cpp.int]
        
        cpp.lib._track.argtypes = [cpp.object, cpp.int_array, cpp.int, cpp.uint8_t_array]
        
        cpp.lib._setImg.argtypes = [cpp.object, cpp.uint8_t_array]
        
        
    def __init__(self, YOLO_result, img: np.ndarray, visualize = False) -> None:
        """Creates a Tracker object
        """
        
        Tracker.setFuncs()
        
        points, size = Tracker.YoloToPointsWithClasses(YOLO_result, 5)

        self.obj = cpp.lib._Tracker(points, cpp.c_int(size), np.array(img.flatten(), dtype=np.uint8), cpp.c_int(img.shape[0]), cpp.c_int(img.shape[1]), cpp.c_bool(visualize))
    
    def track(self, YOLO_result, coloredImg: np.ndarray):
        points, size = Tracker.YoloToPointsWithClasses(YOLO_result, 5)
        cpp.lib._track(self.obj, points, size, np.array(coloredImg.flatten(), dtype=np.uint8))
    
    
    
        
        