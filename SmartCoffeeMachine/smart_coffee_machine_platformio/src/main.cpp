#include <Arduino.h>
#include "Scheduler.h"
#include "ThreeLedsTask.h"
#include "DistanceDetectionTask.h"
#include "MovementDetectionTask.h"
#include "Maintenance.h"
#include "CoffeeMakingTask.h"
#include "MsgService.h"

bool ready = false;
bool doing = false;
bool done = false;
bool movement = false;
bool took = false;
bool maintenance = false;
bool sleep = true;

Scheduler sched;

void setup() {
  sched.init(500);
  MsgService.init();
  //pin a caso per ora
  Task* leds = new ThreeLedsTask(7,8,9);
  Task* mov = new MovementDetectionTask(2);
  Task* dist = new DistanceDetectionTask(1, 3);
  Task* maint = new Maintenance();
  Task* coffee = new CoffeeMakingTask(4, A0);
  mov->init(500);
  leds->init(1000);
  dist->init(500);
  coffee->init(500);
  maint->init(500);
  sched.addTask(mov);
  sched.addTask(dist);
  sched.addTask(coffee);
  sched.addTask(leds);
  sched.addTask(maint);

}

void loop() {
  sched.schedule();
}
