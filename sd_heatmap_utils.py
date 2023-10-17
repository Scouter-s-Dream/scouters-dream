import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

class Qual:
    """
    A class used to represent an FRC Qualification Round :D
    
    Attributes
    ----------
    - qual_num : int
        the qualification round number
    - blue_alliance : list
        a list of team members in the blue alliance
    - red_alliance : list
        a list of team members in the red alliance

    Methods
    -------
    - generate_heatmap(roi, robot_trajectories, robot_numbers, pixel_size=10)
        - Generate and display a heatmap of robot trajectories.
    """

    def __init__(self, qual_num: int, blue_allince: list, red_allince: list):
        """
        Initialize a Qual object.
        ...

        Args:
        ----
        - qual_num: The qualification number.
        - blue_allince: List of team members in the blue alliance.
        - red_allince: List of team members in the red alliance.
        """
        self.qual_num = qual_num
        self.blue_allince = blue_allince
        self.red_allince = red_allince

    def _update_heatmap(self, frame, resized_shape, robot_trajectories, robot_trails, pixel_size, im, ax, team_number_annotations, colormap):
        """
        Update the heatmap and robot trajectories for a specific frame.
        
        Args:
        - frame: The frame to update the heatmap for.
        - resized_shape: The shape of the resized heatmap.
        - robot_trajectories: Dictionary of robot trajectories.
        - robot_trails: Dictionary of robot trails.
        - pixel_size: Size of pixels in the heatmap.
        - im: Matplotlib image object for the heatmap.
        - ax: Matplotlib axis for displaying the heatmap and trajectories.
        - team_number_annotations: Dictionary of team number annotations.
        - colormap: Matplotlib colormap for robot trail colors.

        Returns:
        -------
        - im: Updated Matplotlib image object.
        """
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
        """
        Generate and display a heatmap of robot trajectories.
        ...
        Args:
        ----
        - roi: Region of interest of frame.
        - robot_trajectories: Dictionary of robot trajectories.
        - robot_numbers: List of robot numbers.
        - pixel_size: Size of pixels in the heatmap (default is 10).

        Returns: None
        """
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
        ani.save(output_file, writer='Pillow')
