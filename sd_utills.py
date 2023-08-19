import cv2
import numpy as np

def click_event(event, x, y, flags, params):
    if event == cv2.EVENT_LBUTTONDOWN:
        print(x, ' ', y)

class Qual:
    def __init__(self, qual_num: int, blue_allince: list, red_allince: list):
        self.qual_num = qual_num

        self.blue_allince = blue_allince   
        self.red_allince = red_allince
    
    
    def set_qual_num(self, qual_num: int) -> None:
        self.qual_num = qual_num


    def set_blue_allince(self, blue_allince: list) -> None:
        self.blue_allince = blue_allince
    
    
    def set_red_allince(self, red_allince: list) -> None:
        self.red_allince = red_allince


    def is_red_or_blue_allince(self, frame: list) -> str:
        roi_height = frame.shape[0] // 4
        roi = frame[-roi_height:, :]
        
        lower_red = np.array([0, 200, 0], dtype="uint8")
        upper_red = np.array([0, 255, 0], dtype="uint8")

        red_mask = cv2.inRange(roi, lower_red, upper_red)
        num_red_pixels = cv2.countNonZero(red_mask)

        return 'RED' if num_red_pixels > red_mask.size * 0.5 else 'BLUE'


    def get_detected_bumber_number(self, detected_digits: list, frame: list) -> str:
        allince_color = self.is_red_or_blue_allince(frame)

        digits = [sublist[-1] for sublist in detected_digits]

        print(f'DIGITS:{digits}\nALLINCE:{allince_color}')
        
        max_matching_digits = 0
        most_matching_team_number = ''

        for team_number in self.red_allince if allince_color == 'RED' else self.blue_allince:
            count = sum(map(lambda x, y: x == y, digits, team_number))
            
            if count > max_matching_digits:
                max_matching_digits = count
                most_matching_team_number = team_number

        if max_matching_digits == 0:
            return None

        return most_matching_team_number


