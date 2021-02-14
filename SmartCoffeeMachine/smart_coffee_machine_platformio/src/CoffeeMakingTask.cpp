#include "Arduino.h"
#include "CoffeeMakingTask.h"
#include "MsgService.h"

extern bool ready;
extern bool doing;
extern bool done;
extern int current_coffee;
extern bool maintenance;
extern bool took;
extern bool movement;

CoffeeMakingTask::CoffeeMakingTask(int pin_button, int pin_pot){
  this->pin_button = pin_button;
  this->pin_pot = pin_pot;
}

void CoffeeMakingTask::init(int period){
  Task::init(period);
  button = new Button(pin_button);
  pot = new Pot(pin_pot);
}

void CoffeeMakingTask::tick(){
  if(ready && !done && !doing){
    sugar = pot->readPot() % 4; // 4 livelli di zucchero
    MsgService.sendMsg((String)sugar);
    button->isPressed() ? isPressed = true : isPressed = false;
    if(isPressed){
      doing = true;
      MsgService.sendMsg("Making a coffee");
      this->resetTaskTime();
    }
  }
  else if(this->getTaskTime() >= 3000 && doing){
    done = true;
    doing = false;
    MsgService.sendMsg("The coffee is ready");
    current_coffee--;
    if(current_coffee <= 0){
      maintenance = true;
      movement = false;
      ready = false;
      MsgService.sendMsg("No more coffee, waiting for recharge.");
    }
  }
  else if((this->getTaskTime() >= 8000 && done) || took){
    done = false;
    doing = false;
    took = false;
    this->resetTaskTime();
  }
  this->updateTaskTime();
}
