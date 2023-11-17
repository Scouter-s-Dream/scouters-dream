#ifndef __TRACKER__HPP
#define __TRACKER_HPP

#include "boundingBox.hpp"
#include <memory>
#include <vector>
#include <opencv2/opencv.hpp>
#include "entity.hpp"

class Tracker{
    
    public:
        bool visualize;
        cv::Mat img;
        int rows;
        int cols;
        std::vector<Entity> lastEntities;
        std::vector<Entity> currentEntities;

        Tracker();

        Tracker(int* pointsWithClass, int size, uint8_t* img, int rows, int cols, bool visualize);

        void setTrackPoints(int* pointsWithClass, int size);

        void setImg(uint8_t* img);

        void drawBoundingBoxes();
        
        int* findSimilarBoundingBoxes();

        std::vector<Entity> boundingBoxesToEntites(std::vector<BoundingBox> boundingBoxes, int* pointsWithClass);

        void stablePoints();

        void track();

};


#endif