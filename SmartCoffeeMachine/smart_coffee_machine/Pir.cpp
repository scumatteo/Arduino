#include "Pir.h"
#include "Arduino.h"

Pir::Pir(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);
}

bool Pir::isMoved(){
  return digitalRead(pin) == HIGH;
}
