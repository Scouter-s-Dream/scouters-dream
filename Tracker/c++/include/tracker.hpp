#ifndef __TRACKER__HPP
#define __TRACKER_HPP

#include "entity.hpp"
#include <string>
#include <sstream>
#include <iostream>

enum Types{
    BlueRobot = 0, RedRobot
};


class Tracker{
    
    public:
        const bool visualize;
        const uint16_t rows;
        const uint16_t cols;
        cv::Mat img;
        vector<Entity> entities;
        vector<Entity> currentRecognition;
        vector<Entity> currentPrediction;

        Tracker(uint16_t* points, uint16_t* types, uint16_t size, uint8_t* img, uint16_t rows, uint16_t cols, bool visualize);

        void setTrackPoints(uint16_t* points, uint16_t* types, uint16_t size);

        void setImg(uint8_t* img);

        void drawEntities();

        void drawPredictions();
        
        uint* findSimilarRectes();

        vector<Entity> rectsToEntites(vector<Rect> rects, uint16_t* pointsWithClass);

        void stablePoints();

        void distanceTrack();

        void addToTrajectory();

        void track(uint16_t* points, uint16_t* types, uint16_t size, uint8_t* img);

        void makePredictions();

        cv::Scalar chooseColor(Entity& e);


};  


#endif