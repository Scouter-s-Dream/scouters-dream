#ifndef __ENTITY__HPP__
#define __ENTITY__HPP__

#include "boundingBox.hpp"
#include <vector>
#include "linkedList.hpp"
using std::vector;


class Entity{

    private:
        unsigned short id;
        char type;
        short velocity;
        BoundingBox boundingBox;
        LinkedList trajectory;

};


#endif