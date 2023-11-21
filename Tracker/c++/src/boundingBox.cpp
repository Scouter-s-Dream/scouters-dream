#include "boundingBox.hpp"

using std::cout;

/*
BoundingBox default constractor.
-
*/
BoundingBox::BoundingBox(){}

/*
BoundingBox constractor.
-
Args:
 - `pointWithClass (uint[])` -> xywh point with class [x, y, w, h].
*/
BoundingBox::BoundingBox(uint16_t* pointWithClass){
    this->setBox(pointWithClass);
}

/*
Sets the box and other parameters of the BoundingBox.
-
Args:
 - `pointWithClass (uint[])` -> xywh point with class [x, y, w, h].
*/
void BoundingBox::setBox(uint16_t* point){
    uint8_t pointSize = 4;
    this->box.reserve(pointSize);
    for (uint8_t i = 0; i < pointSize; i++){
        this->box.push_back(point[i]);
    }
    this->area = point[2] * point[3]; //w * h
    this->perimeter = 2 * (point[2] + point[3]);    
}



/*
Returns The box of the BoundingBox.
-
*/
vector<uint16_t> BoundingBox::getBox(){
    return this->box;
}

uint BoundingBox::getArea(){
    return this->area;
}

uint BoundingBox::getPerimeter(){
    return this->perimeter;
}

vector<uint16_t> BoundingBox::getCenter(){
   return vector<uint16_t> (this->box.begin(), this->box.begin() + 2); 
}

uint16_t BoundingBox::getWidth(){
    return this->box[2];
} 

uint16_t BoundingBox::getHeight(){
    return this->box[3];
}
/*
Returns The square distance between centers to a BoundingBox.
-
Args: 
 - `boundingBox (BoundingBox)` -> the BoundingBox to claculate center to.

Returns:
 - `squareDistance (uint)` -> the distance to the BoundingBox.
*/
uint BoundingBox::squareDistanceTo(BoundingBox boundingBox){
    return squareDistance(this->getCenter(), boundingBox.getCenter());
}

/*
Returns if a BoundingBox is close to this BoundingBox by a certain distance.
-
Args: 
 - `boundingBox (BoundingBox)` -> the BoundingBox to claculate distance to.

Returns:
 - `isClose (bool)` -> if close or not.
*/
bool BoundingBox::isCloseTo(BoundingBox boundingBox, double distance){
	return this->squareDistanceTo(boundingBox) <  distance;
}

/*
Checks if this BoundingBox is intersecting to other BoundingBox.
-
Args: 
 - `boundingBox (BoundingBox)` -> the BoundingBox to check.
 - `difference (uint)` -> the increse in size of one boundingBox to help intersect.

Returns:
 - `isIntersecting (bool)` -> if intersecting to the BoundingBox or not.
*/
bool BoundingBox::isIntersectingTo(BoundingBox boundingBox, uint difference){
	return this->getBox()[0] < (boundingBox.getBox()[0] + boundingBox.getBox()[2]+ difference) && (this->getBox()[0] + this->getBox()[2]) > (boundingBox.getBox()[0] - difference) && this->getBox()[1] < (boundingBox.getBox()[1] + boundingBox.getBox()[3]+ difference) && (this->getBox()[1] + this->getBox()[3]) > (boundingBox.getBox()[1] - difference);
}


/*
Avrages BoundingBoxes center from an array of BoundingBoxes.
-
Args: 
 - `dest (BoundingBox)` -> Output to the avraged BoundingBox.
 - `boundingBoxes (vector<BoundingBox)` -> the vector of the BoundingBoxes.
 - `startLoc (uint)` -> The location in the array to start avrage.
 - `stopLoc (uint)` -> The location in the array to stop avrage 

*/
void avrageBoundingBoxes(BoundingBox dest, std::vector<BoundingBox> boundingBoxes, uint8_t startLoc, uint8_t stopLoc){

    uint16_t x = 0, y = 0, w = 0, h = 0;
    for (uint8_t i = startLoc; i < stopLoc + 1; i++){
        x += boundingBoxes[i].getBox()[0];
        y += boundingBoxes[i].getBox()[1];
        w += boundingBoxes[i].getBox()[2];
        h += boundingBoxes[i].getBox()[3];
    }
    uint16_t times = stopLoc - startLoc + 1;
    uint16_t out[4] = {static_cast<uint16_t>(x /times), static_cast<uint16_t>(y /times), static_cast<uint16_t>(w /times), static_cast<uint16_t>(h /times)};

    dest.setBox(out);
}

/*
Turn uint[] of points with classes into BoundingBoxes.
-
Args: 
 - `points (uint[])` -> SORTED xywh points with classes [x, y, w, h].
 - `size (uint)` -> How many points are in the array (Size of the array / size of a point).

Returns:
 - `boundingBoxes (vector<BoundingBoxes>)` -> shared_ptr to the array of BoundingBoxes.
*/
std::vector<BoundingBox> pointsToBoundingBoxes(uint16_t *pointsWithClass, uint16_t size){
	
	std::vector<BoundingBox> boundingBoxes;
    boundingBoxes.reserve(size);

	for (uint i = 0; i < size; i++){
        boundingBoxes.emplace_back(pointsWithClass + i*5);
	}
    
	return boundingBoxes;

}

/*
Overides the << opertator to print parameters of the BoundingBox.
-
*/
std::ostream& operator<<(std::ostream& os, BoundingBox boundingBox){
    // Printing all the elements
    os << "Box: [";
    for (uint i = 0; i < 4; i++){
        cout << boundingBox.getBox()[i] << " ";
    }
    os << "\b]\n";
    os << "Perimeter: " << boundingBox.getPerimeter() << "\n";
    os << "Area: " << boundingBox.getArea() << "\n"; 
    os << "Center: [" << boundingBox.getCenter()[0] << ", " << boundingBox.getCenter()[1] << "]\n"; 
    return os;
}

// BoundingBox BoundingBox::operator=(const BoundingBox& box){
//     return box;
// }