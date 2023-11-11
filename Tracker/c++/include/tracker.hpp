#ifndef __TRACKER__HPP
#define __TRACKER_HPP

#include "boundingBox.hpp"
#include <memory>
#include <vector>

class Tracker{
    
    public:

        std::vector<BoundingBox> stableBoundingBoxes;
        std::vector<BoundingBox> lastStableBoundingBoxes;
        std::vector<BoundingBox> currentBoundingBoxes;
        int numOfStableBoundingBoxes = 0;
        int numOfLastStableBoundingBoxes = 0;
        int numOfCurrentBoundingBoxes = 0;

        Tracker();

        void setTrackPoints(int *pointsWithClass, int size);


        int* findSimilarBoundingBoxes();

        void stablePoints();

        void track();

};


#endif