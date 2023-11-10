#ifndef __BOUNDING_BOX_HPP
#define __BOUNDING_BOX_HPP

#include "mathUtils.hpp"
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <memory>

class BoundingBox{

    private:

        int id; 
        int box[4]; //[x, y, w, h]
        char type; 
        int area;
        int perimeter;
        int center[2];

    public:

        BoundingBox();
        BoundingBox(int *pointWithClasses, int id);
                
        void setBox(int *pointWithClasses);

        int* getBox();

        char getClass();

        int* getCenter();

        double squareDistanceTo(BoundingBox b);

        bool isIntersectingTo(BoundingBox b, int difference = 0);

        bool isCloseTo(BoundingBox b, double distance);

        void print();


};

std::shared_ptr<BoundingBox[]> pointsToBoundingBoxes(int *pointsWithClass, int size);

void avrageBoundingBoxes(BoundingBox dest, std::shared_ptr<BoundingBox[]> boundingBoxes, int startLoc, int stopLoc);

#endif 