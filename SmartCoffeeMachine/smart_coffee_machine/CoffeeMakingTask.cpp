#include "Arduino.h"
#include "CoffeeMakingTask.h"
#include "MsgService.h"

#define pot1 341
#define pot2 682
#define DT3 3000
#define S8 8000

extern bool ready;
extern bool doing;
extern bool done;
extern int current_coffee;
extern bool maintenance;
extern bool took;
extern bool on;

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
  if(!maintenance){
    if(ready){
      if(!done && !doing){
        potLevel = pot->readPot();
        if(potLevel == 0){
          sugar = 0;
        }
        else if(potLevel > 0 && potLevel <= pot1){
          sugar = 1;
        }
        else if(potLevel > pot1 && potLevel <= pot2){
          sugar = 2;
        }
        else if(potLevel > pot2){
          sugar = 3;
        }
        if(sugar != prevSugar){
          MsgService.sendMsg(String(sugar));
        }
        prevSugar = sugar;
        button->isPressed() ? isBPressed = true : isBPressed = false;
        if(isBPressed){
          doing = true;
          MsgService.sendMsg("Making a coffee");
          this->resetTaskTime();
        }
      }
      else if(this->getTaskTime() >= DT3 && doing){
        done = true;
        doing = false;
        MsgService.sendMsg("The coffee is ready");
        current_coffee--;
      }
      else if((this->getTaskTime() >= S8 && done) || took){
        this->resetTaskTime();
        done = false;
        if(current_coffee <= 0){
          maintenance = true;
          on = false;
          ready = false;
          MsgService.sendMsg("m");
          MsgService.sendMsg("No more coffee, waiting for recharge.");
        }
      }
      this->updateTaskTime();
    }
  }
}
