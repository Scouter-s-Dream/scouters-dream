import numpy as np

class Robot():
    
    def __init__(self, number:int, team: bool):
        self.number = number
        self.team = team #red = False, blue = True
        self.cones = np.zeros(3, dtype=np.uint8) #[High, Mid, Low]
        self.cubes = np.zeros(3, dtype=np.uint8) #[High, Mid, Low]
        self.trajectory = []
    
    