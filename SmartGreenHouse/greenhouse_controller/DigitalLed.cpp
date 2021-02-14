#include "DigitalLed.h"
#include "Arduino.h"

DigitalLed::DigitalLed(int pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

void DigitalLed::switchOn(){
  digitalWrite(pin,HIGH);
}

void DigitalLed::switchOff(){
  digitalWrite(pin,LOW);
}
