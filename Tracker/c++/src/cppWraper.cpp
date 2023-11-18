#include "imgAlgsCpu.hpp"
#include "tracker.hpp"

extern "C"{

    Tracker* _Tracker(uint* pointsWithClass, uint size, uint8_t* img, uint rows, uint cols, bool visualize){
        return new Tracker(pointsWithClass, size, img, rows, cols, visualize);
    }

    void _setImg(Tracker *t, uint8_t* img){
        t -> setImg(img);
    }

    void _setTrackPoints(Tracker *t, uint16_t* pointsWithClasses, uint size){
        t -> setTrackPoints(pointsWithClasses, size);
    }

    void _track(Tracker *t, uint16_t* pointsWithClasses, uint size, uint8_t* img){
        t -> track(pointsWithClasses, size, img);
    }

}