#include "Arduino.h"
#include "Maintenance.h"
#include "MsgService.h"

extern bool maintenance;
extern bool done;
extern int current_coffee;

Maintenance::Maintenance(){ }

void Maintenance::init(int period){
  Task::init(period);
}

void Maintenance::tick(){
  if(maintenance){
	MsgService.sendMsg("Maintenance");
    if (MsgService.isMsgAvailable()) {
      Msg* msg = MsgService.receiveMsg();
      if (msg->getContent() == "5"){
        current_coffee += 5;
      }
      else if (msg->getContent() == "10"){
        current_coffee += 10;
      }
      else if(msg->getContent() == "20"){
        current_coffee += 20;
      }
      maintenance = false;
      
    }
  }
}
