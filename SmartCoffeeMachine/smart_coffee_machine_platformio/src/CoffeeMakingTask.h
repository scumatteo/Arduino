#ifndef __COFFEEMACHINE__
#define __COFFEEMACHINE__

#include "Task.h"
#include "Button.h"
#include "Pot.h"

class CoffeeMakingTask : public Task{
  int pin_button;
  int pin_pot;
  Button* button;
  Pot* pot;
  bool isPressed;
  int sugar;

public:
  CoffeeMakingTask(int pin_button, int pin_pot);
  void init(int period);
  void tick();

};

#endif
