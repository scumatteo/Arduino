#ifndef __IRRIGATIONTASK__
#define __IRRIGATIONTASK__

#include "Task.h"
#include "AnalogLed.h"
#include "ServoTimer2.h"

class IrrigationTask : public Task{
  int pinL2;
  AnalogLed* led2;
  int servoPin;
  ServoTimer2* servoMotor;
  bool isOpen = false;

public:
  IrrigationTask(int pinL2, int servoPin);
  void init(int period);
  void tick();

};

#endif
