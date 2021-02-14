#ifndef __MANUALTASK__
#define __MANUALTASK__

#include "Task.h"
#include "DigitalLed.h"
#include "AnalogLed.h"
#include "BTMsgService.h"
#include "MsgService.h"

class ManualTask : public Task{
  int redLedPin;
  DigitalLed* redLed;
  BTMsgService* BTmsgService;
  bool isOn;

public:
  ManualTask(int redLedPin, BTMsgService* BTmsgService);
  void init(int period);
  void tick();

};

#endif
