#include "imgAlgsCpu.hpp"
#include "tracker.hpp"

extern "C"{

    Tracker* _Tracker(){
        return new Tracker();
    }
    void _setTrackPoints(Tracker* t, int* points, int size){
        t -> setTrackPoints(points, size);
    }

}