#ifndef __BOUNDING_BOX_HPP
#define __BOUNDING_BOX_HPP

#include "mathUtils.hpp"
#include "vectorFuncs.hpp"

using std::vector;

class BoundingBox{

    private:

        vector<uint16_t> box; //[x, y, w, h] the x y is of the center.
        uint area;
        uint perimeter;

    public:

        BoundingBox();
        BoundingBox(uint16_t* pointWithClasses);

        void setBox(uint16_t* pointWithClasses);

        vector<uint16_t> getBox();

        vector<uint16_t> getCenter();

        uint16_t getWidth();      

        uint16_t getHeight();

        uint getArea();

        uint getPerimeter();

        uint squareDistanceTo(BoundingBox b);

        bool isIntersectingTo(BoundingBox boundingBox, uint difference = 0);

        bool isCloseTo(BoundingBox b, double distance);

        // BoundingBox operator=(const BoundingBox& box);

};

std::ostream& operator<<(std::ostream& os, BoundingBox boundingBox);

std::vector<BoundingBox> pointsToBoundingBoxes(uint16_t *pointsWithClass, uint16_t size);

void avrageBoundingBoxes(BoundingBox dest, std::vector<BoundingBox> boundingBoxes, uint8_t startLoc, uint8_t stopLoc);

#endif 