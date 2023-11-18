#include "imgAlgsCpu.hpp"
using cv::Mat, cv::VideoCapture;

/*
Skips given number of frames
-
Args:

 - `cap (cv::VideoCapture)` -> the vidoe instance that is being captured
 - `framesToSkip (short)` -> the number of frames that is being skipped
*/
void skipFrames(VideoCapture cap, short framesToSkip){

	Mat blank;
	for (uint i = 0; i < framesToSkip; i++){
		cap.read(blank);
	}

}

/*
Filters the Red color from a given frame.
-
Args:
- `frame (Mat)` -> the frame being filtered

Returns:
- `filtered (Mat)` -> the filtered Frame
*/
Mat filterRed(Mat frame){

	Mat filtered;

	cv::GaussianBlur(frame, filtered, {5, 5}, 1, 1);
	cv::inRange(frame, cv::Scalar(90, 45, 45), cv::Scalar(150, 255, 255), filtered);

	Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 9));

	cv::morphologyEx(filtered, filtered, cv::MORPH_OPEN, kernel);

	return filtered;

}

/*
Filters the Blue color from a given frame.
-
Args:
- `frame (Mat)` -> the frame being filtered

Returns:
- `filtered` (Mat) -> the filtered Frame
*/
Mat filterBlue(Mat frame){

	Mat filtered;

	cv::GaussianBlur(frame, filtered, {5, 5}, 1, 1);
	cv::inRange(frame, cv::Scalar(130, 50, 50), cv::Scalar(190, 255, 255), filtered);

	Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 9));

	cv::morphologyEx(filtered, filtered, cv::MORPH_OPEN, kernel);
	

	return filtered;
}



//TODO make alg that cuts only the field from the video