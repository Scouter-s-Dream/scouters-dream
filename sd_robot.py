import numpy as np
from sd_utils import center
from sd_globals import *

class Robot():
    
        
    def __init__(self, number:int, team: bool, position: tuple[np.ndarray[int, int], np.ndarray[int, int]]):
        self.number = number
        if team:
            ROBOT_BLUESIDE.append(self)
        else:
            ROBOT_REDSIDE.append(self)
        self.position = position
        self.cones = np.zeros(3, dtype=np.uint8) #[High, Mid, Low]
        self.cubes = np.zeros(3, dtype=np.uint8) #[High, Mid, Low]
        self.trajectory = []
        self.center = center(position)
        
    def update_position(self, position: tuple[np.ndarray, np.ndarray]):
        self.position = position
        
    def get_position(self) -> np.ndarray[int, int]:
        return self.position