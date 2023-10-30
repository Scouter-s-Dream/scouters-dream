import cv2 
import os

#I think there is a much better way to do this, but I just scramblem it in case it can be useful

def prepre_video(path: str, resize:tuple[int, int], cutY:tuple[int, int]=None, cutX:tuple[int, int]=None):
    """`prepare the video pre scouting `

    Args:
        path (str): path to the original video
        resize (tuple[int, int]): the new size of the video
        cutY (tuple[int, int], optional): cut in the Y axis, between the first and last arg of the tuple. Defaults to None.
        cutX (tuple[int, int], optional): cut in the Y axis, between the first and last arg of the tuple. Defaults to None.
        
        `saves the new video to the same path`
    """
    cap = cv2.VideoCapture(path)
    fourcc = cv2.VideoWriter_fourcc('M','J','P','G')
    
    if cutX and cutY is not None:
        writer = cv2.VideoWriter(path.split(".")[0], fourcc, 60.0, (cutX[1] - cutX[0], cutY[1] - cutY[0]), True)
    elif cutX is not None:
        writer = cv2.VideoWriter(path.split(".")[0], fourcc, 60.0, (cutX[1] - cutX[0], resize[1]), True)
        cutY = (0, resize[1])
    if cutY is not None:
        writer = cv2.VideoWriter(path.split(".")[0], fourcc, 60.0, (resize[0], cutY[1] - cutY[0]), True)
        cutX = (0, resize[0])
    else:
        writer = cv2.VideoWriter(path.split(".")[0], fourcc, 60.0, resize, True)
        cutY = (0, resize[1])
        cutX = (0, resize[0])
        
    while True:
        ret, frame = cap.read()
        if frame is None:
            break
        frame = cv2.resize(frame, resize)    
        frame = frame[cutY[0]:cutY[1], cutX[0], cutX[1]]

        
        cv2.imshow('Video', frame)
        writer.write(frame)  
        cv2.waitKey(1)
        
    print("DONE")

    cap.release()
    writer.release()
    cv2.destroyAllWindows()


