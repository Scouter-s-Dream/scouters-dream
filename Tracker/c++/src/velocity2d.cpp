#include "velocity2d.hpp"

std::ostream& operator<<(std::ostream& os, const Velocity2D& v){
    os << "[" << v.velX << ", " << v.velY << "]";
}
