#ifndef __POT__
#define __POT__

class Pot {
public:
  Pot(int pin);
  int readPot();
private:
  int pin;
};

#endif
