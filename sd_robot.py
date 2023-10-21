import numpy as np

class Robot():
    
    def __init__(self, number:int, team: bool, position: tuple[np.ndarray, np.ndarray]):
        self.number = number
        self.team = team #red = False, blue = True
        self.position = position
        self.cones = np.zeros(3, dtype=np.uint8) #[High, Mid, Low]
        self.cubes = np.zeros(3, dtype=np.uint8) #[High, Mid, Low]
        self.trajectory = []
        
    def update_position(self, position: tuple[np.ndarray, np.ndarray]):
        self.position = position
        
    def get_position(self):
        return self.position