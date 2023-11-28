#include "imgAlgsCpu.hpp"
#include "tracker.hpp"

extern "C"{

    Tracker* _Tracker(uint16_t* points, uint16_t* types, uint16_t size, uint8_t* img, uint16_t rows, uint16_t cols, bool visualize){
        return new Tracker(points, types, size, img, rows, cols, visualize);
    }

    void _track(Tracker *t, uint16_t* points, uint16_t* types, uint16_t size, uint8_t* img){
        t -> track(points, types, size, img);
    }

}