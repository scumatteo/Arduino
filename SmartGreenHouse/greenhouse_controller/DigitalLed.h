#ifndef __D_LED__
#define __D_LED__

class DigitalLed { 
public:
  DigitalLed(int pin);
  void switchOn();
  void switchOff();
private:
  int pin;  
};

#endif
