#ifndef __TRACKER__HPP
#define __TRACKER_HPP

#include "boundingBox.hpp"
#include <memory>
#include <vector>
#include <opencv2/opencv.hpp>
#include "entity.hpp"

class Tracker{
    
    public:
        cv::Mat img;
        int width;
        int height;
        std::vector<Entity> lastEntities;
        std::vector<Entity> currentEntities;

        Tracker();

        Tracker(int* pointsWithClass, int size, int* img, int width, int height);

        void setTrackPoints(int* pointsWithClass, int size);

        void setImg(int* img);

        int* findSimilarBoundingBoxes();

        std::vector<Entity> boundingBoxesToEntites(std::vector<BoundingBox> boundingBoxes, int* pointsWithClass);

        void stablePoints();

        void track();

};


#endif