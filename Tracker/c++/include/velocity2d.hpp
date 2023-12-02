#ifndef __VEL2D
#define __VEL2D

#include <iostream>

using std::cout;

typedef struct Velocity2D Velocity2D;

struct Velocity2D{

    int velX;
    int velY;
    Velocity2D(int velX, int velY) : velX(velX), velY(velY) {}
    Velocity2D() : velX(0), velY(0) {}
};

std::ostream& operator<<(std::ostream& os, const Velocity2D& v);

#endif