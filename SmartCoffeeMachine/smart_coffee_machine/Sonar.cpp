#include "Arduino.h"
#include "Sonar.h"

const float vs = 331.5 + 0.6*20;

Sonar::Sonar(int echoPin, int trigPin){
  this->echoPin = echoPin;
  this->trigPin = trigPin;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float Sonar::getDistance(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin,LOW);
  /* ricevi l’eco */
  float tUS = pulseIn(echoPin, HIGH);
  float t = tUS / 1000.0 / 1000.0 / 2;
  float d = t*vs;
  return d;
}
