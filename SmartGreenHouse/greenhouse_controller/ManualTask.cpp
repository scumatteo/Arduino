#include "Arduino.h"
#include "ManualTask.h"

extern bool automatic;
extern bool open;
extern int portata;

ManualTask::ManualTask(int redLedPin, BTMsgService* BTmsgService){
  this->redLedPin = redLedPin;
  this->BTmsgService = BTmsgService;
}

void ManualTask::init(int period){
  Task::init(period);
  redLed = new DigitalLed(redLedPin);
}

//messaggi da implementare
void ManualTask::tick(){
  if(!automatic){
    if(BTmsgService->isMsgAvailable()){
      Msg* message = BTmsgService->receiveMsg();
      String msg = message->getContent();
      MsgService.sendMsg(msg);
      open = true;
      portata = msg.toInt();
      delete message;
    }
    else{
      open = false;
      portata = 0;
    }
    if(MsgService.isMsgAvailable()){
      Msg* message = MsgService.receiveMsg();
      String msg = message->getContent();
      BTmsgService->sendMsg(msg);
      delete message;
    }
    if(!isOn){
      MsgService.sendMsg("m");
      redLed->switchOn();
      isOn = true;
    }
  }
  else{
    if(isOn){
      isOn = false;
      redLed->switchOff();
    }
  }

}
