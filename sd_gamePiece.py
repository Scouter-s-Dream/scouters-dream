from ultralytics import YOLO
from sd_robot import Robot
import numpy as np

GREED_POSITION = (np.array([0, 0]), np.array(0, 0))

class GamePiece():
    
    def __init__(self,id:int, type:bool, position: tuple[np.ndarray, np.ndarray]):
        self.id = id
        self.type = type
        self.position = position
        
    def update_position(self, position: tuple[np.ndarray, np.ndarray]):
        self.position = position
        
    def get_position(self):
        return self.position   
 
    