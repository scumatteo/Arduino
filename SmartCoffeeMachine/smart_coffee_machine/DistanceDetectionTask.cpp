#include "DistanceDetectionTask.h"
#include "Arduino.h"
#include "MsgService.h"

#define DT1 1000
#define DT2A 5000
#define DIST1 0.3
#define DIST2 0.1

extern bool on;
extern bool ready;
extern bool done;
extern bool maintenance;
extern bool took;
extern bool standby;
extern bool doing;

DistanceDetectionTask::DistanceDetectionTask(int echoPin, int trigPin){
  this->echoPin = echoPin;
  this-> trigPin = trigPin;
}

void DistanceDetectionTask::init(int period){
  Task::init(period);
  sonar = new Sonar(echoPin, trigPin);
}

void DistanceDetectionTask::tick(){
  if(!maintenance){
    dist = sonar->getDistance(); 
    Serial.println(String(dist));
    if(!ready){
      if(on){
        this->updateTaskTime();
        dist < DIST1 ? minDist = true : minDist = false;
        if(minDist && preDist){
          if(this->getTaskTime() >= DT1){
            ready = true;
            MsgService.sendMsg("Welcome!");
            this->resetTaskTime();
          }
        }
        preDist = minDist;
      }
    }
    else{
      if(!done && !doing){
        this->updateTaskTime();
        dist < DIST1 ? minDist = true : minDist = false;
        if(!minDist && !preDist && this->getTaskTime() >= DT2A){
          ready = false;
          this->resetTaskTime();
        }
        preDist = minDist;
      }
      else if(done){
        dist < DIST2 ? minDist = true : minDist = false;
        if(minDist){
          took = true;
        }
      }
    }
  }
}
