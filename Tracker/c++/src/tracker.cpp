#include "tracker.hpp"
#include <string>
#include <sstream>
#include <iostream>

using std::cout, std::endl;

/*
The default Tracker constractor
-
*/
Tracker::Tracker(){
	
}

Tracker::Tracker(int* pointsWithClass, int size, uint8_t* img, int rows, int cols, bool visualize){
	this->visualize = visualize;
	this->rows = rows;
	this->cols = cols;
	setTrackPoints(pointsWithClass, size);
	setImg(img);
}

void Tracker::setImg(uint8_t* img){
	cout << "SetImg\n";
	this->img = cv::Mat(this->rows, this->cols, CV_8UC3, img);	
	// cv::cvtColor(this->img, this->img, cv::COLOR_BGR2GRAY);
}

std::vector<Entity> Tracker::boundingBoxesToEntites(std::vector<BoundingBox> boundingBoxes, int* pointsWithClass){
	
	std::vector<Entity> entities;
    entities.reserve(boundingBoxes.size());
	
	for (unsigned int i = 0, size = boundingBoxes.size(); i < size; i++){
        entities.emplace_back(i, (char) pointsWithClass[5*i + 4], boundingBoxes[i]);
	}
    //TODO switch magic numbers or give them explenations
	return entities;
}

/*
Sets the current BoundingBoxes of the tracker
-
Args: 
 - `pointsWithClass (int[])` -> xywh points with classes [x, y, w, h, c].
 - `size (int)` -> How many points are in the array (Size of the array / size of a point).
*/
void Tracker::setTrackPoints(int *pointsWithClass, int size){

	this->lastEntities = this->currentEntities;
	this->currentEntities = boundingBoxesToEntites(pointsToBoundingBoxes(pointsWithClass, size), pointsWithClass); //sets the currentStableStack inside stablePoints.
	
	cout << "Created\n"; 
}

void Tracker::drawBoundingBoxes(){
	for (unsigned int i = 0; i < this->currentEntities.size(); i++){
		int x = this->currentEntities[i].getBoundingBox()->getBox()[0] - this->currentEntities[i].getBoundingBox()->getBox()[2] / 2;
		int y = this->currentEntities[i].getBoundingBox()->getBox()[1] - this->currentEntities[i].getBoundingBox()->getBox()[3] / 2;
		int w = this->currentEntities[i].getBoundingBox()->getBox()[2];
		int h = this->currentEntities[i].getBoundingBox()->getBox()[3];
		cv::Rect2i rect(x, y, w, h);
		cv::rectangle(this->img, rect, CV_RGB(255, 0, 0), 2);
		cv::Point2i centerPoint(this->currentEntities[i].getBoundingBox()->getBox()[0], this->currentEntities[i].getBoundingBox()->getBox()[1]);
		cv::putText(this->img, std::to_string(this->currentEntities[i].getId()), centerPoint, cv::FONT_HERSHEY_DUPLEX, 1, CV_RGB(0, 0, 255), 2);
	}
}

//TODO More Advenced func, need to know how to use 
//CURRENTLY NOT WORKING!
/*
Finds points that are close together
-
Returns:
 - `SimilarPoints (int[])` -> array of indexes of the similar points 
[LocA, locB, locA, locB .... ,how many points removed]
- `All points between LocA and locB are similar.`

*/
int* Tracker::findSimilarBoundingBoxes(){return new int(0);}

// 	unsigned short reduced = 0;
// 	unsigned short index = 0;
// 	const int distance = 150;
// 	int* similar = new int[this->numOfCurrentBoundingBoxes + 1]; // [locA, locB, locA, locB] (locA and locB are similar).

// 	for (int i = 0, size = this->numOfCurrentBoundingBoxes; i < size ; i++){
		
// 		similar[i] = size + 1; 

// 		if (this->currentBoundingBoxes[i].isCloseTo(this->currentBoundingBoxes[i+1], distance)){

// 			similar[index] = i;
// 			similar[index + 1] = i + 1;

// 			for (int k = i + 1; k < size - i -1 ; k++){

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

// 	int *similar = this->findSimilarBoundingBoxes();
// 	int constant = 0;
// 	this->stableBoundingBoxes.reserve(this->numOfCurrentBoundingBoxes);
	
// 	for (int real = 0, size = this->numOfCurrentBoundingBoxes, reduced = similar[size]; real < size - reduced; real++){
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

void Tracker::track(){
	
	cout << this->visualize << "\n";

	if (this->visualize){
		cout << "v\n"; 
		this->drawBoundingBoxes();
		cv::imshow("frame", this->img);
		cv::waitKey(1);
	}

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