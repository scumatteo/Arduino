#include "DistanceDetectionTask.h"
#include "Arduino.h"

#define DIST 0.3

extern bool automatic;

DistanceDetectionTask::DistanceDetectionTask(int echoPin, int trigPin){
  this->echoPin = echoPin;
  this-> trigPin = trigPin;
}

void DistanceDetectionTask::init(int period){
  Task::init(period);
  sonar = new Sonar(echoPin, trigPin);

}

void DistanceDetectionTask::tick(){
  dist = sonar->getDistance();
  if(dist < DIST){
    if(this->getTaskTime() > 1000){
      automatic = false;
      this->resetTaskTime();
    }
  }
  else{
    if(this->getTaskTime() > 2000){
      automatic = true;
      this->resetTaskTime();
    }
  }
  this->updateTaskTime();
}
