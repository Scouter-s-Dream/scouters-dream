#ifndef __IMG_ALGS_CPP__
#define __IMG_ALGS_CPP__

#include <opencv2/opencv.hpp>
#include <stdio.h>

using cv::Mat, cv::VideoCapture;

void skipFrames(VideoCapture cap, short framesToSkip);

Mat filterRed(Mat frame);

Mat filterBlue(Mat frame);

#endif
