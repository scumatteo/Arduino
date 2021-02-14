#ifndef __AUTOTASK__
#define __AUTOTASK__

#include "Task.h"
#include "DigitalLed.h"
#include "AnalogLed.h"
#include "MsgService.h"

class AutoTask : public Task{
  DigitalLed* led1;
  int pinL1;
  bool isOn;

public:
  AutoTask(int pinL1);
  void init(int period);
  void tick();

};

#endif
