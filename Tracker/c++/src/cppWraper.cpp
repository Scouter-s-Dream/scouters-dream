#include "imgAlgsCpu.hpp"
#include "tracker.hpp"

extern "C"{

    Tracker* _Tracker(int* pointsWithClass, int size, uint8_t* img, int rows, int cols, bool visualize){
        return new Tracker(pointsWithClass, size, img, rows, cols, visualize);
    }

    void _setImg(Tracker *t, uint8_t* img){
        t -> setImg(img);
    }

    void _setTrackPoints(Tracker *t, int* pointsWithClasses, int size){
        t -> setTrackPoints(pointsWithClasses, size);
    }

    void _track(Tracker *t, int* pointsWithClasses, int size, uint8_t* img){
        t -> track(pointsWithClasses, size, img);
    }

}