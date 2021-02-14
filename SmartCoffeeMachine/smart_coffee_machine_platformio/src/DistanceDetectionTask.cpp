#include "DistanceDetectionTask.h"
#include "Arduino.h"
#include "MsgService.h"

extern bool movement;
extern bool ready;
extern bool done;
extern bool maintenance;
extern bool took;

DistanceDetectionTask::DistanceDetectionTask(int echoPin, int trigPin){
  this->echoPin = echoPin;
  this-> trigPin = trigPin;
}

void DistanceDetectionTask::init(int period){
  Task::init(period);
  sonar = new Sonar(echoPin, trigPin);
}

/*
Da vedere come funziona se perde/prende un giro
*/
void DistanceDetectionTask::tick(){
  if(movement && !done){ //forse ci vuole maintenance
    sonar->getDistance() < 0.3 ? minDist = true : minDist = false;
    this->updateTaskTime();
    if(minDist && preDist){
      if(this->getTaskTime() >= 1000){
        ready = true;
        MsgService.sendMsg("Welcome!");
        this->resetTaskTime();
      }
    }
    else if(minDist && !preDist){
      this->resetTaskTime();
    }
    else if(!minDist && preDist){
      this->resetTaskTime();
    }
    else if(!minDist && !preDist){
      if(this->getTaskTime() >= 5000){
        ready = false;
        this->resetTaskTime();
      }
    }
    preDist = minDist;
  }
  else if(done && !took){ //forse ci vuole maintenance
    sonar->getDistance() < 0.1 ? minDist = true : minDist = false;
    if(minDist){
      took = true;
      if(!maintenance){
        ready = true;
      }
      else{
        ready = false;
      }
    }
  }
}
