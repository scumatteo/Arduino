#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include "Arduino.h"
#include "Msg.h"

class Pattern {
public:
  virtual boolean match(const Msg& m) = 0;
};

class MsgServiceClass{

public:

  Msg* currentMsg;
  bool msgAvailable;

  void init();

  bool isMsgAvailable();
  Msg* receiveMsg();

  bool isMsgAvailable(Pattern& pattern);
  Msg* receiveMsg(Pattern& pattern);

  void sendMsg(const String& msg);
};

extern MsgServiceClass MsgService;

#endif