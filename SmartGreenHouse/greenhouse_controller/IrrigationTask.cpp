#include "Arduino.h"
#include "IrrigationTask.h"

#define MIN 30
#define MED 60
#define MAX 90
#define I_MIN 85
#define I_MED 170
#define I_MAX 255
#define SERVO_ZERO 750
#define SERVO_MIN 1000
#define SERVO_MED 1250
#define SERVO_MAX 1500


extern bool open;
extern int portata;

IrrigationTask::IrrigationTask(int pinL2, int servoPin){
  this->pinL2 = pinL2;
  this->servoPin = servoPin;
}

void IrrigationTask::init(int period){
  Task::init(period);
  led2 = new AnalogLed(pinL2);
  servoMotor = new ServoTimer2();
}

//messaggi da implementare
void IrrigationTask::tick(){
  if(open){
    if(!isOpen){
      isOpen = true;
      servoMotor->attach(servoPin);
    }
      if(portata == MIN){
        led2->setIntensity(I_MIN);
        servoMotor->write(SERVO_MIN);
      }
      else if(portata == MED){
        led2->setIntensity(I_MED);
        servoMotor->write(SERVO_MED);
      }
      else if(portata == MAX){
        led2->setIntensity(I_MAX);
        servoMotor->write(SERVO_MAX);
      }
  }
  else{
    if(isOpen){
      isOpen = false;
      led2->setIntensity(0);
      servoMotor->write(0);
	  servoMotor->detach();
    }
  }


}
