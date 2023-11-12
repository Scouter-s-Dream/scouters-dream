#ifndef __BOUNDING_BOX_HPP
#define __BOUNDING_BOX_HPP

#include "mathUtils.hpp"
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <memory>
#include <vector>

class BoundingBox{

    private:

        int box[4]; //[x, y, w, h]
        int area;
        int perimeter;
        int center[2];

    public:

        BoundingBox();
        BoundingBox(int *pointWithClasses);
                
        void setBox(int *pointWithClasses);

        int* getBox();

        int* getCenter();

        double squareDistanceTo(BoundingBox b);

        bool isIntersectingTo(BoundingBox b, int difference = 0);

        bool isCloseTo(BoundingBox b, double distance);

        void print();


};

std::vector<BoundingBox> pointsToBoundingBoxes(int *pointsWithClass, int size);

void avrageBoundingBoxes(BoundingBox dest, std::vector<BoundingBox> boundingBoxes, int startLoc, int stopLoc);

#endif 