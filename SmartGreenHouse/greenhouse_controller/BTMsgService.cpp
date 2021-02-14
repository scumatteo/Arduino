#include "Arduino.h"
#include "BTMsgService.h"
#include "Msg.h"


BTMsgService::BTMsgService(int rxPin, int txPin){
  channel = new SoftwareSerial(rxPin, txPin);
}

void BTMsgService::init(){
  content.reserve(256);
  channel->begin(9600);
}

void BTMsgService::sendMsg(Msg msg){
  channel->println(msg.getContent());
}

bool BTMsgService::isMsgAvailable(){
  return channel->available();
}

Msg* BTMsgService::receiveMsg(){
  while (channel->available()) {
    char ch = (char) channel->read();
    if (ch == '\n'){
      Msg* msg = new Msg(content);
      content = "";
      return msg;
    } else {
      content += ch;
    }
  }
  return NULL;
}
