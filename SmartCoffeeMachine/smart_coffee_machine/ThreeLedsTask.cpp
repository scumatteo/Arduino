#include "ThreeLedsTask.h"
#include "Arduino.h"
#include "MsgService.h"

#define DT4 5000

extern bool doing;
extern bool done;
extern bool took;
extern bool maintenance;

ThreeLedsTask::ThreeLedsTask(int pin0, int pin1, int pin2){
  this->pin[0] = pin0;
  this->pin[1] = pin1;
  this->pin[2] = pin2;
}

void ThreeLedsTask::init(int period){
  Task::init(period);
  for (int i = 0; i < 3; i++){
    led[i] = new Led(pin[i]);
  }
  currentPin = 0;
}

void ThreeLedsTask::tick(){
  if(!maintenance){
    if(doing){ //forse ci vuole maintenance
      if(currentPin < 3){
        led[currentPin]->switchOn();
        currentPin++;
      }
    }
    else if(done){
      this->updateTaskTime();
    }
    else if(this->getTaskTime() >= DT4 || took){ //così sta acceso finchè non passa DT4 o ritiro il caffè
      for(int i = 0; i < 3; i++){
        led[i]->switchOff();
        currentPin = 0;        
      }
      took = false;
      this->resetTaskTime();
    }
  }
  else{
     for(int i = 0; i < 3; i++){
        led[i]->switchOff();
        currentPin = 0;        
      }
  }
}
