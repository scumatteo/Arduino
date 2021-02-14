#ifndef __BTMSGSERVICE__
#define __BTMSGSERVICE__

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Msg.h"

class BTMsgService {

public:
  BTMsgService(int rxPin, int txPin);
  void init();
  bool isMsgAvailable();
  Msg* receiveMsg();
  void sendMsg(Msg msg);

private:
  SoftwareSerial* channel;
  String content;

};

#endif
