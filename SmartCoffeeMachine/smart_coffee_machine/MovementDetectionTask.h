#ifndef __MOVEMENTDETECTIONTASK__
#define __MOVEMENTDETECTIONTASK__

#include "Task.h"
#include "Pir.h"
#include "Timer.h"

class MovementDetectionTask : public Task{

  int pin;
  Pir* pir;
  bool mnt;

public:

  MovementDetectionTask(int pin);
  void init(int period);
  void tick();

};

#endif
