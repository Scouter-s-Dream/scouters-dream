#include "tracker.hpp"

Tracker::Tracker(uint16_t* points, uint16_t* types, uint16_t size, uint8_t* img, uint16_t rows, uint16_t cols, bool visualize) 
	: visualize(visualize), rows(rows), cols(cols){
	setTrackPoints(points, types, size); // sets this current recognition
	setImg(img);
	this->entities = vector<Entity>(this->currentRecognition);
	this->addToTrajectory();
}

void Tracker::setImg(uint8_t* img){
	this->img = cv::Mat(this->rows, this->cols, CV_8UC3, img);	
}

std::vector<Entity> Tracker::rectsToEntites(std::vector<Rect> rects, uint16_t* classes){
	std::vector<Entity> recognition;
    recognition.reserve(rects.size());

	for (uint16_t i = 0, size = rects.size(); i < size; i++){
        recognition.emplace_back(i, classes[i], rects[i]);
	}

	return recognition;
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

void Tracker::addToTrajectory(){
	for (Entity& entity : this->entities){
		entity.addToTrajectory();
		cout << entity.getTrajetctory()->length << " ";
	}
	cout << "\n";
}

cv::Scalar Tracker::chooseColor(Entity& e){
	cv::Scalar color;
	switch (e.getType()){
			case RedRobot:
				color = CV_RGB(255, 0, 0);
				break;
			case BlueRobot:
				color = CV_RGB(0, 0, 255);
				break;
			default:
				color = CV_RGB(0, 0, 0);
		}
	return color;
}

void Tracker::makePredictions(){
	this->currentPrediction = std::vector<Entity>(this->entities);
	for (Entity& e : this->currentPrediction){
		cout << "ENTERED\n";
		e.clacVelocities();
		e.setBoundingRect(e.predictNextBoundingRect());
	}
	cout << this->currentPrediction;
	
}

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

	//at the end of the above loop current recognitions needs to be empty. if it doesnt, this loop is done to add to entities.
	for (uint16_t i = 0, size = this->currentRecognition.size(); i < size; i++){
		this->entities.emplace_back(this->currentRecognition[i]);
	}

	// if (size < newSize){
	// 	this->entitys.reserve(newSize);
	// 	std:: << this->entitys.size() << "  " << newSize << "\n";

	// 	for (uint16_t i = size; i < newSize - size; i++){
	// 		Entity newEntity = this->currentRecognition[i - size + 1];
	// 		this->entitys.emplace_back(size + 1, newEntity.getType(), newEntity.getRect());
	// 	}
	// } 

}


void Tracker::drawEntities(){
	for (uint16_t i = 0, size = this->entities.size(); i < size; i++){
		Entity& drawnEntity = this->entities[i];
		cv::Scalar color = chooseColor(drawnEntity);
		drawnEntity.draw(this->img, color);
	}
}

void Tracker::drawPredictions(){
	for (uint16_t i = 0, size = this->currentPrediction.size(); i < size; i++){
		Entity& drawnEntity = this->currentPrediction[i];
		drawnEntity.draw(this->img, CV_RGB(255, 255, 255));
	}
}


//TODO using a lot of shared pointers - performence heavy.
//TODO imporve all function performence!.
void Tracker::track(uint16_t* points, uint16_t* types, uint16_t size, uint8_t* img){
	
	this->makePredictions();

	this->setTrackPoints(points, types, size);

	this->setImg(img);

	this->addToTrajectory();

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