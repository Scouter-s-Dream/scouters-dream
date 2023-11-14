#include "imgAlgsCpu.hpp"
#include "tracker.hpp"

extern "C"{

    Tracker* _Tracker(int* pointsWithClass, int size, int* img, int width, int height){
        return new Tracker(pointsWithClass, size, img, width, height);
    }
    void _setTrackPoints(Tracker* t, int* points, int size){
        t -> setTrackPoints(points, size);
    }

}