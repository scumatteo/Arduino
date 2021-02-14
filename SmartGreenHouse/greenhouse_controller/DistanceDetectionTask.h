#ifndef __DISTANCEDETECTIONTASK__
#define __DISTANCEDETECTIONTASK__

#include "Task.h"
#include "Sonar.h"
#include "MsgService.h"

class DistanceDetectionTask : public Task{
  int echoPin;
  int trigPin;
  Sonar* sonar;
  float dist;

public:
  DistanceDetectionTask(int echoPin, int trigPin);
  void init(int period);
  void tick();

};

#endif
