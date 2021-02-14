#ifndef __TASK__
#define __TASK__

class Task {
  int myPeriod;
  int timeElapsed;
  int taskTime;

public:

  virtual void init(int period){
    myPeriod = period;
    timeElapsed = 0;
    taskTime = 0;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod){
      timeElapsed = 0;
      return true;
    } else {
      return false;
    }
  }

  int getTaskTime(){
    int i = taskTime;
    return i;
  }

  void updateTaskTime(){
    taskTime += myPeriod;
  }

  void resetTaskTime(){
    taskTime = 0;
  }
};

#endif
