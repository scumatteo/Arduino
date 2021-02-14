#include "Pot.h"
#include "Arduino.h"

Pot::Pot(int pin){
  this->pin = pin;
}

int Pot::readPot(){
  return analogRead(pin);
}
