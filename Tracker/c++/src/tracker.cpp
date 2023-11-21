#include "tracker.hpp"
#include <string>
#include <sstream>
#include <iostream>

using std::cout, std::endl;

Tracker::Tracker(uint16_t* pointsWithClass, uint16_t size, uint8_t* img, uint16_t rows, uint16_t cols, bool visualize) 
	: visualize(visualize), rows(rows), cols(cols){
	setTrackPoints(pointsWithClass, size);
	setImg(img);
	this->entitys.reserve(this->currentEntities.size());
	for (uint i = 0; i < this->entitys.size(); i++){
		this->entitys[i] = this->currentEntities[i];
	}
}

void Tracker::setImg(uint8_t* img){
	this->img = cv::Mat(this->rows, this->cols, CV_8UC3, img);	
}

std::vector<Entity> Tracker::boundingBoxesToEntites(std::vector<BoundingBox> boundingBoxes, uint16_t* pointsWithClass){
	
	std::vector<Entity> entities;
    entities.reserve(boundingBoxes.size());
	uint8_t pointsWithClassSize = 5; //pointWithClassSize - 1 means points without class
	
	for (uint16_t i = 0, size = boundingBoxes.size(); i < size; i++){
        entities.emplace_back(i, pointsWithClass[pointsWithClassSize*i + pointsWithClassSize-1], boundingBoxes[i]);
	}
	return entities;
}

/*
Sets the current BoundingBoxes of the tracker
-
Args: 
 - `pointsWithClass (uint[])` -> xywh points with classes [x, y, w, h, c].
 - `size (uint)` -> How many points are in the array (Size of the array / size of a point).
*/
void Tracker::setTrackPoints(uint16_t *pointsWithClass, uint16_t size){
	this->currentEntities = boundingBoxesToEntites(pointsToBoundingBoxes(pointsWithClass, size), pointsWithClass); //sets the currentStableStack inside stablePoints.
}

void Tracker::drawBoundingBoxes(){
	for (uint16_t i = 0, size = this->entitys.size(); i < size; i++){
		uint16_t x = this->entitys[i].getBoundingBox().getBox()[0] - this->entitys[i].getBoundingBox().getBox()[2] / 2;
		uint16_t y = this->entitys[i].getBoundingBox().getBox()[1] - this->entitys[i].getBoundingBox().getBox()[3] / 2;
		uint16_t w = this->entitys[i].getBoundingBox().getBox()[2];
		uint16_t h = this->entitys[i].getBoundingBox().getBox()[3];
		cv::Rect2i rect(x, y, w, h);
		cv::rectangle(this->img, rect, CV_RGB(255, 0, 0), 2);
		cv::Point2i centerPoint(this->entitys[i].getBoundingBox().getBox()[0], this->entitys[i].getBoundingBox().getBox()[1]);
		cv::putText(this->img, std::to_string(this->entitys[i].getId()), centerPoint, cv::FONT_HERSHEY_DUPLEX, 1, CV_RGB(0, 0, 255), 2);
	}
}

//TODO More Advenced func, need to know how to use 
//CURRENTLY NOT WORKING!
/*
Finds points that are close together
-
Returns:
 - `SimilarPoints (uint[])` -> array of indexes of the similar points 
[LocA, locB, locA, locB .... ,how many points removed]
- `All points between LocA and locB are similar.`

*/
uint* Tracker::findSimilarBoundingBoxes(){return new uint(0);}

// 	uint16_t reduced = 0;
// 	uint16_t index = 0;
// 	const uint distance = 150;
// 	uint* similar = new uint[this->numOfCurrentBoundingBoxes + 1]; // [locA, locB, locA, locB] (locA and locB are similar).

// 	for (uint i = 0, size = this->numOfCurrentBoundingBoxes; i < size ; i++){
		
// 		similar[i] = size + 1; 

// 		if (this->currentBoundingBoxes[i].isCloseTo(this->currentBoundingBoxes[i+1], distance)){

// 			similar[index] = i;
// 			similar[index + 1] = i + 1;

// 			for (uint k = i + 1; k < size - i -1 ; k++){

// 				if (this->currentBoundingBoxes[k].isCloseTo(this->currentBoundingBoxes[k+1], distance) && this->currentBoundingBoxes[i].isCloseTo(this->currentBoundingBoxes[i+1], (distance-50) * (k-i+1.5))){
					
// 					similar[index + 1] = k + 1;

// 					if (k == size - i - 1){ //last time
// 						reduced += k-i;
// 					}

// 				}
// 				else{
// 					reduced += k - i;
// 					i += k - i - 1;
// 					break;
// 				}


// 			}
			
// 			index+=2;

// 		}


// 	}

// 	similar[this->numOfCurrentBoundingBoxes] = reduced;

// 	return similar;

// }

/*
Stables the BoundingBoxes that are stored in stableBoundingBoxes
-
*/




void Tracker::stablePoints(){}

// 	uint *similar = this->findSimilarBoundingBoxes();
// 	uint constant = 0;
// 	this->stableBoundingBoxes.reserve(this->numOfCurrentBoundingBoxes);
	
// 	for (uint real = 0, size = this->numOfCurrentBoundingBoxes, reduced = similar[size]; real < size - reduced; real++){
// 		if (real == similar[real] + constant){
// 			avrageBoundingBoxes(this->stableBoundingBoxes[real], this->currentBoundingBoxes, similar[real] + constant, similar[real+1] + constant);
// 			constant += (similar[real+1] - similar[real]);
// 		}
// 		else{
// 			this->stableBoundingBoxes[real].setBox(this->currentBoundingBoxes[real + constant].getBox());
// 		}
		
// 	}
	
// 	this->numOfLastStableBoundingBoxes = this->numOfStableBoundingBoxes;
// 	this-> numOfStableBoundingBoxes = this->numOfCurrentBoundingBoxes - similar[this->numOfCurrentBoundingBoxes];
// 	delete[] similar;
// }

void Tracker::track_by_distance(){

	uint16_t size = this->entitys.size();
	// uint16_t newSize = this->currentEntities.size();

	for (uint16_t i = 0; i < size; i++){
		entitys[i].setBox(entitys[i].findClosest(this->currentEntities).getBoundingBox());
	}


	// if (size < newSize){
	// 	this->entitys.reserve(newSize);
	// 	std::cout << this->entitys.size() << "  " << newSize << "\n";

	// 	for (uint16_t i = size; i < newSize - size; i++){
	// 		Entity newEntity = this->currentEntities[i - size + 1];
	// 		this->entitys.emplace_back(size + 1, newEntity.getType(), newEntity.getBoundingBox());
	// 	}
	// } 

}

void Tracker::track(uint16_t* pointsWithClasses, uint16_t size, uint8_t* img){
	

	this->setTrackPoints(pointsWithClasses, size);
	this->setImg(img);

	this->track_by_distance();
	
	if (this->visualize){
		cout << "CURRENT --------\n";
		for (uint i = 0; i < this->currentEntities.size(); i++){
			cout << this->currentEntities[i].getBoundingBox() << endl;
		}
		cout << "ENTITIES --------\n";
		for (uint i = 0; i < this->entitys.size(); i++){
			cout << this->entitys[i].getBoundingBox() << endl;
		}
		this->drawBoundingBoxes();
		cv::imshow("frame", this->img);
		cv::waitKey(0);
	}
	this->currentEntities.clear();
	/*
		Tracker psudo code:

			
			get bounding boxes and the img the were in at the start.

			for each of the new bounding boxes
				make predictions to the other boundingboxes based on

					position
					velocity
					color
					last seen of lost bounding boxes
					size of boundingbox

			determine predictions.

			set ids to the new points

	*/


}	