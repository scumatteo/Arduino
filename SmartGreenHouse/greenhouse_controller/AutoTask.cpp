#include "Arduino.h"
#include "AutoTask.h"
#include "MsgService.h"

extern bool open;
extern bool automatic;
extern int portata;

AutoTask::AutoTask(int pinL1){
  this->pinL1 = pinL1;
}

void AutoTask::init(int period){
  Task::init(period);
  led1 = new DigitalLed(pinL1);
}

//messaggi da implementare
void AutoTask::tick(){
  if(automatic){
    if(MsgService.isMsgAvailable()){
      Msg* message = MsgService.receiveMsg();
      String msg = message->getContent();
      open = true;
      portata = msg.toInt();
      delete message;
    }
    else{
      open = false;
      portata = 0;
    }
    if(!isOn){
      MsgService.sendMsg("a");
      led1->switchOn();
      isOn = true;
    }
  }
  else{
    if(isOn){
      isOn = false;
      led1->switchOff();
    }
  }

}
