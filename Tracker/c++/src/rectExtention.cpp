#include "rectExtention.hpp"

using std::cout;

uint Rect::squareDistanceTo(Rect& r){
    return squareDistance(this->tl(), r.tl());
}

bool Rect::isCloseTo(Rect& r, double distance){
	return this->squareDistanceTo(r) <  distance;
}

// bool Rect::isIntersectingTo(Rect& rect){
// 	return this->x < (rect.x + rect.width) && 
//     (this->x + this->width) > (rect.x) && 
//     this->y < (rect.y + rect.height) && 
//     (this->y + this->height) > (rect.y);
// }

// void avrageRectes(Rect dest, std::vector<Rect> boundingBoxes, uint8_t startLoc, uint8_t stopLoc){

//     uint16_t x = 0, y = 0, w = 0, h = 0;
//     for (uint8_t i = startLoc; i < stopLoc + 1; i++){
//         x += boundingBoxes[i].getBox()[0];
//         y += boundingBoxes[i].getBox()[1];
//         w += boundingBoxes[i].getBox()[2];
//         h += boundingBoxes[i].getBox()[3];
//     }
//     uint16_t times = stopLoc - startLoc + 1;
//     uint16_t out[POINT_SIZE] = {static_cast<uint16_t>(x /times), static_cast<uint16_t>(y /times), static_cast<uint16_t>(w /times), static_cast<uint16_t>(h /times)};

//     dest.setBox(out);
// }

//TODO this function gets her values from python - validity check in python is VERY IMPORTANT! 
std::vector<Rect> pointsToRects(uint16_t *points, uint16_t size){
	
	std::vector<Rect> rects;
    rects.reserve(size);
    cout << "size: " << size << "\n";
	for (uint16_t i = 0; i < size; i++){
        uint16_t* currentPoint = points + i*POINT_SIZE;
        Point A = Point(currentPoint[0], currentPoint[1]);
        Point B = Point(currentPoint[2], currentPoint[3]);
        rects.emplace_back(A, B);
	}
    
	return rects;  

}

std::ostream& operator<<(std::ostream& os, Rect& rect){
    // Printing all the elements
    os << "[" << rect.x << " " << rect.y << " " << rect.width << " " << rect.height << "]";
    os << "Area: " << rect.area() << "\n"; 
    return os;
}

