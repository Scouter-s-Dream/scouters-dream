#include "mathUtils.hpp"

using cv::Mat;

/*
Returns the highest number in a matrix
-
Args:
 - `frame (Mat)` the frame being maxPooled
return:
- `highest (Double)` the highest number in the frame
*/
double max(Mat frame){

	double highest;
	cv::minMaxLoc(frame, NULL, &highest, NULL, NULL);
	return highest;
}

/*
Returns the lowest number in a matrix
-
Args:
 - `frame (Mat)` the frame being maxPooled
return:
- `lowest (Double)` the lowest number in the frame
*/
double min(Mat frame){

	double lowest;
	cv::minMaxLoc(frame, &lowest, NULL, NULL, NULL);

	return lowest;
}

/*
Returns The square distance between two points.
-
Args: 
 - `pointA (number[])` -> the first point.
 - `pointB (number[])` -> the second point
Returns:
 - `squareDistance (int)` -> the distance between the points.
*/
double squareDistance(int *pointA, int *pointB){
    return pow(pointA[0] - pointB[0], 2) + pow(pointA[1] - pointB[1], 2);
}
