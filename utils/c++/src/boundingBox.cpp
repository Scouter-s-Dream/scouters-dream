#include "boundingBox.hpp"

using std::cout;

/*
BoundingBox default constractor.
-
*/
BoundingBox::BoundingBox(){
    this->id = -1;
}

/*
BoundingBox constractor.
-
Args:
 - `pointWithClass (int[])` -> xywh point with class [x, y, w, h, c].
 - `id (int)` -> Represents that id of the BoundingBox.
*/
BoundingBox::BoundingBox(int *pointWithClass, int id){
    this-> id = id;
    this->setBox(pointWithClass);
    this->type = (char) pointWithClass[4];
}

/*
Sets the box and other parameters of the BoundingBox.
-
Args:
 - `pointWithClass (int[])` -> xywh point with class [x, y, w, h, c].
*/
void BoundingBox::setBox(int *pointWithClass){

    memcpy(this->box, pointWithClass, 4 * sizeof(int));
    this->area = pointWithClass[2] * pointWithClass[3]; //w * h

    this->perimeter = 2 * (pointWithClass[2] + pointWithClass[3]);
    
}

/*
Prints the parameters of the BoundingBox.
-
*/
void BoundingBox::print(){
    cout << "id " << this->id << "\n"; 
    cout << "x " << this->box[0] << " y " << this->box[1] << " w " << this->box[2] << " h " << this->box[3] << "\n"; //[x, y, w, h]
    cout << "type " << this->type << "\n";
    cout << "area " << this->area << "\n";
    cout << "perimeter " << this->perimeter << "\n";
    cout << "center " << *this->center << "\n";
}

/*
Returns The box of the BoundingBox.
-
*/
int* BoundingBox::getBox(){
    return this->box;
}

/*
Returns The class of the BoundingBox.
-
*/
char BoundingBox::getClass(){
    return this->type;
}

/*
Returns The center of the BoundingBox.
-
*/
int* BoundingBox::getCenter(){
    return this->center;
}

/*
Returns The square distance between centers to a BoundingBox.
-
Args: 
 - `boundingBox (BoundingBox)` -> the BoundingBox to claculate center to.

Returns:
 - `squareDistance (int)` -> the distance to the BoundingBox.
*/
double BoundingBox::squareDistanceTo(BoundingBox boundingBox){
    return squareDistance(this->center, boundingBox.getCenter());
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
 - `difference (int)` -> the increse in size of one boundingBox to help intersect.

Returns:
 - `isIntersecting (bool)` -> if intersecting to the BoundingBox or not.
*/
bool BoundingBox::isIntersectingTo(BoundingBox boundingBox, int difference){
 
	return this->getBox()[0] < (boundingBox.getBox()[0] + boundingBox.getBox()[2]+ difference) && (this->getBox()[0] + this->getBox()[2]) > (boundingBox.getBox()[0] - difference) && this->getBox()[1] < (boundingBox.getBox()[1] + boundingBox.getBox()[3]+ difference) && (this->getBox()[1] + this->getBox()[3]) > (boundingBox.getBox()[1] - difference);
	
}


/*
Avrages BoundingBoxes center from an array of BoundingBoxes.
-
Args: 
 - `dest (BoundingBox)` -> Output to the avraged BoundingBox.
 - `boundingBoxes (shared_ptr<BoundingBoxes[]>)` -> Shared_ptr the BoundingBox array.
 - `startLoc (int)` -> The location in the array to start avrage.
 - `stopLoc (int)` -> The location in the array to stop avrage 

*/
void avrageBoundingBoxes(BoundingBox dest, std::shared_ptr<BoundingBox[]> boundingBoxes, int startLoc, int stopLoc){

    int x = 0, y = 0, w = 0, h = 0;
    for (int i = startLoc; i < stopLoc + 1; i++){
        x += boundingBoxes[i].getBox()[0];
        y += boundingBoxes[i].getBox()[1];
        w += boundingBoxes[i].getBox()[2];
        h += boundingBoxes[i].getBox()[3];
    }
    short times = stopLoc - startLoc + 1;
    int out[4] = {x/times, y/times, w/times, h/times};

    dest.setBox(out);
}

/*
Turn long int[] of points with classes into BoundingBoxes.
-
Args: 
 - `pointsWithClass (int[])` -> SORTED xywh points with classes [x, y, w, h, c].
 - `size (int)` -> How many points are in the array (Size of the array / size of a point).

Returns:
 - `boundingBoxes (shared_ptr<BoundingBox[]>)` -> shared_ptr to the array of BoundingBoxes.
*/
std::shared_ptr<BoundingBox[]> pointsToBoundingBoxes(int *pointsWithClass, int size){
	
	std::shared_ptr<BoundingBox[]> boundingBoxes(new BoundingBox[size]);
	int pointWithClass[5]; //[x y w h Class] 

	for (int i = 0; i < size; i++){
		memcpy(&pointWithClass[0], &pointsWithClass[i*5], 5 * sizeof(int));
        boundingBoxes[i] = BoundingBox(pointWithClass, i);
	}
    
	return boundingBoxes;

}