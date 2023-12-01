#include "tracker.hpp"

Tracker::Tracker(uint16_t* points, uint16_t* types, uint16_t size, uint8_t* img, uint16_t rows, uint16_t cols, bool visualize) 
	: visualize(visualize), rows(rows), cols(cols){
	setTrackPoints(points, types, size);
	setImg(img);
	this->entities = vector<Entity>(this->currentRecognition);
	this->addToTrajectory();
}

void Tracker::setImg(uint8_t* img){
	this->img = cv::Mat(this->rows, this->cols, CV_8UC3, img);	
}

std::vector<Entity> Tracker::rectsToEntites(std::vector<Rect> rects, uint16_t* classes){
	std::vector<Entity> entities;
    entities.reserve(rects.size());

	for (uint16_t i = 0, size = rects.size(); i < size; i++){
        entities.emplace_back(i, classes[i], rects[i]);
	}

	return entities;
}

/*
Sets the current Rectes of the tracker
-
Args: 
 - `pointsWithClass (uint[])` -> xywh points with classes [x, y, w, h, c].
 - `size (uint)` -> How many points are in the array (Size of the array / size of a point).
*/
void Tracker::setTrackPoints(uint16_t *points, uint16_t* types, uint16_t size){
	this->currentRecognition = rectsToEntites(pointsToRects(points, size), types); //sets the currentStableStack inside stablePoints.
}

void Tracker::drawEntities(){
	for (uint16_t i = 0, size = this->entities.size(); i < size; i++){
		Entity& drawnEntity = this->entities[i];
		cv::Scalar color;
		switch (drawnEntity.getType()){
			case RedRobot:
				color = CV_RGB(255, 0, 0);
				break;
			case BlueRobot:
				color = CV_RGB(0, 0, 255);
				break;
			default:
				color = CV_RGB(255, 255, 255);
		}
		drawnEntity.draw(this->img, color);
	}
}

void Tracker::drawPredictions(){
	if (!this->currentPrediction.empty()){
		cout << "NO PREDICTIONS\n";
		return;
	}
	for (uint16_t i = 0, size = this->entities.size(); i < size; i++){
		Entity& drawnEntity = this->entities[i];
		drawnEntity.draw(this->img, CV_RGB(255, 255, 255));
	}
}



void Tracker::makePredictions(){
	this->currentPrediction = vector<Entity>(this->entities);
	for (Entity& e : this->currentPrediction){
		e.clacVelocities();
		e.setBoundingRect(e.predictNextBoundingRect());
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
uint* Tracker::findSimilarRectes(){return new uint(0);}

// 	uint16_t reduced = 0;
// 	uint16_t index = 0;
// 	const uint distance = 150;
// 	uint* similar = new uint[this->numOfCurrentRectes + 1]; // [locA, locB, locA, locB] (locA and locB are similar).

// 	for (uint i = 0, size = this->numOfCurrentRectes; i < size ; i++){
		
// 		similar[i] = size + 1; 

// 		if (this->currentRectes[i].isCloseTo(this->currentRectes[i+1], distance)){

// 			similar[index] = i;
// 			similar[index + 1] = i + 1;

// 			for (uint k = i + 1; k < size - i -1 ; k++){

// 				if (this->currentRectes[k].isCloseTo(this->currentRectes[k+1], distance) && this->currentRectes[i].isCloseTo(this->currentRectes[i+1], (distance-50) * (k-i+1.5))){
					
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

// 	similar[this->numOfCurrentRectes] = reduced;

// 	return similar;

// }

/*
Stables the Rectes that are stored in stableRectes
-
*/




void Tracker::stablePoints(){}

// 	uint *similar = this->findSimilarRectes();
// 	uint constant = 0;
// 	this->stableRectes.reserve(this->numOfCurrentRectes);
	
// 	for (uint real = 0, size = this->numOfCurrentRectes, reduced = similar[size]; real < size - reduced; real++){
// 		if (real == similar[real] + constant){
// 			avrageRectes(this->stableRectes[real], this->currentRectes, similar[real] + constant, similar[real+1] + constant);
// 			constant += (similar[real+1] - similar[real]);
// 		}
// 		else{
// 			this->stableRectes[real].setBox(this->currentRectes[real + constant].getBox());
// 		}
		
// 	}
	
// 	this->numOfLastStableRectes = this->numOfStableRectes;
// 	this-> numOfStableRectes = this->numOfCurrentRectes - similar[this->numOfCurrentRectes];
// 	delete[] similar;
// }

void Tracker::distanceTrack(){

	// uint16_t size = this->entities.size();
	// uint16_t newSize = this->currentRecognition.size();
	uint16_t size = MIN(this->entities.size(), this->currentRecognition.size());
	for (uint16_t i = 0; i < size; i++){
		Entity& checkedEntity = this->entities[i];
		uint16_t closetEntityIndex = checkedEntity.findClosestEntityIndex(this->currentRecognition);
		Entity& closetEntity = this->currentRecognition[closetEntityIndex];
		checkedEntity.setBoundingRect(closetEntity.getBoundingRect());
		currentRecognition.erase(currentRecognition.begin() + closetEntityIndex);		
}
	// if (currentRecognition.empty()){
	// 	cout << "------------------------------------------------------------\n";
	// 	std::cin.get();
	// }


	// if (size < newSize){
	// 	this->entitys.reserve(newSize);
	// 	std:: << this->entitys.size() << "  " << newSize << "\n";

	// 	for (uint16_t i = size; i < newSize - size; i++){
	// 		Entity newEntity = this->currentRecognition[i - size + 1];
	// 		this->entitys.emplace_back(size + 1, newEntity.getType(), newEntity.getRect());
	// 	}
	// } 

}

void Tracker::addToTrajectory(){
	for (Entity& entity : this->entities){
		entity.addToTrajectory();
		cout << entity.getTrajetctory()->length << " ";
	}
	cout << "\n";
}
 
//TODO using a lot of shared pointers - performence heavy.
//TODO imporve all function performence!.
void Tracker::track(uint16_t* points, uint16_t* types, uint16_t size, uint8_t* img){
	
	this->setTrackPoints(points, types, size);

	this->setImg(img);

	this->addToTrajectory();

	this->makePredictions();

	this->distanceTrack();
	if (this->visualize){

		this->drawEntities();
		this->drawPredictions();
		cv::imshow("frame", this->img);
		cv::waitKey(1);
	}
	this->currentRecognition.clear();
	this->currentPrediction.clear();

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