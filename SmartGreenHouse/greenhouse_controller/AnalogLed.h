#ifndef __A_LED__
#define __A_LED__

class AnalogLed { 
public:
  AnalogLed(int pin);
  void setIntensity(int u);    
private:
  int pin;  
};

#endif
