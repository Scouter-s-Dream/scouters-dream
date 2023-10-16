import cv2
import numpy as np
from time import time
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import matplotlib.colors as mcolors
from functools import partial


def show_pixel_location(event, x, y, flags, params):
    if event == cv2.EVENT_LBUTTONDOWN:
        print(x, ' ', y)


def show_fps(frame, time_then):
    fps = 1 / (time() - time_then)
    cv2.putText(frame, f'FPS: {fps:.2f}', (0, 25),
                cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)


def skip_frames(cap, skip_frames: int):
    for _ in range(skip_frames):
        cap.read()


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

    def _update_heatmap(self, frame, resized_shape, robot_trajectories, robot_trails, pixel_size, im, ax, team_number_annotations, colormap):
        new_heatmap = np.zeros(resized_shape)

        for robot_id, trajectory in robot_trajectories.items():
            if frame < len(trajectory):
                x, y = trajectory[frame]

                x /= pixel_size
                y /= pixel_size

                new_heatmap[int(y)][int(x)] += 1

                if robot_id not in robot_trails:
                    robot_trails[robot_id] = []

                robot_trails[robot_id].append((int(y), int(x)))

        im.set_data(new_heatmap)
        ax.set_title(f'Frame: {frame}')

        for annotation in team_number_annotations.values():
            annotation.remove()

        team_number_annotations.clear()

        for i, (robot_id, trajectory) in enumerate(robot_trajectories.items()):
            if frame < len(trajectory):
                x, y = trajectory[frame]

                x /= pixel_size
                y /= pixel_size

                annotation = ax.text(x, y, str(robot_id), color='red', fontsize=10,
                                     ha='center', va='center')

                team_number_annotations[robot_id] = annotation

                trail = np.array(robot_trails[robot_id])
                plt.plot(trail[:, 1], trail[:, 0],
                         color=colormap(i), linewidth=2)

        return im,

    def generate_heatmap(self, roi, robot_trajectories, robot_numbers, pixel_size=10):
        resized_shape = (roi.shape[0] // pixel_size,
                         roi.shape[1] // pixel_size)
        heatmap = np.zeros(resized_shape)

        for robot_id, trajectory in robot_trajectories.items():
            for x, y in trajectory:
                heatmap[int(y // pixel_size)][int(x // pixel_size)] += 1

        heatmap /= np.max(heatmap)

        num_robots = len(robot_numbers)
        colormap = plt.cm.get_cmap('tab20', num_robots)

        fig, ax = plt.subplots(figsize=(10, 8))
        im = ax.imshow(np.zeros(resized_shape), cmap='viridis',
                       interpolation='nearest', aspect='auto')

        team_number_annotations = {}
        robot_trails = {}

        ani = FuncAnimation(fig, self._update_heatmap,
                            frames=len(robot_trajectories[robot_numbers[0]]), blit=True,
                            fargs=(resized_shape, robot_trajectories, robot_trails, pixel_size, im, ax, team_number_annotations, colormap))

        output_file = f'trajectory_animation_qual{self.qual_num}.gif'
        ani.save(output_file, writer='imagemagick')
