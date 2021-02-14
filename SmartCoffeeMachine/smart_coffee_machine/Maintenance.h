#ifndef __MAINTENANCE__
#define __MAINTENANCE__

#include "Task.h"

class Maintenance : public Task{

public:
  Maintenance();
  void init(int period);
  void tick();
};

#endif
