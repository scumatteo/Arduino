#include "Scheduler.h"
#include "MsgService.h"
#include "BTMsgService.h"
#include "DistanceDetectionTask.h"
#include "AutoTask.h"
#include "ManualTask.h"
#include "IrrigationTask.h"
#include <Wire.h>

#define ECHOPIN 13
#define TRIGPIN 12
#define TXD 1
#define RXD 2
#define L1 4
#define L2 5
#define LRED 6
#define SERVO 8

bool open = false;
bool automatic = true;
int portata = 0;

Scheduler sched;
BTMsgService* BTmsgService = new BTMsgService(TXD,RXD);

void setup() {
  MsgService.init();
  BTmsgService->init();
  sched.init(50);
  Task* distanceTask = new DistanceDetectionTask(ECHOPIN, TRIGPIN);
  Task* manualTask = new ManualTask(LRED, BTmsgService);
  Task* autoTask = new AutoTask(L1);
  Task* irrigationTask = new IrrigationTask(L2, SERVO);
  distanceTask->init(100);
  manualTask->init(200);
  autoTask->init(200);
  irrigationTask->init(100);
  sched.addTask(autoTask);
  sched.addTask(distanceTask);
  sched.addTask(manualTask);
  sched.addTask(irrigationTask);
}

void loop() {
  sched.schedule();
}
