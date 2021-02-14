#include "MovementDetectionTask.h"
#include "Arduino.h"
#include <avr/sleep.h>
#include <avr/power.h>

extern bool movement;
extern bool maintenance;
extern bool sleep;

MovementDetectionTask::MovementDetectionTask(int pin){
  this->pin = pin;
}

void MovementDetectionTask::init(int period){
    Task::init(period);
    pir = new Pir(pin);
}

void MovementDetectionTask::tick(){
  //TODO
  //Gestire lo sleep.
  if(sleep && !maintenance){
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    power_adc_disable();
    power_spi_disable();
    power_timer0_disable(); // only timer 1
    power_timer2_disable(); // on
    power_twi_disable();
    sleep_mode();
    /* back */
    sleep_disable();
    power_all_enable();

  }
  pir->isMoved() ? mnt = true : mnt = false; //legge il pir
  if(mnt &&!maintenance){
    sleep = false;
    movement = true;
    this->resetTaskTime();
  }
  else if(!mnt && !maintenance){
    this->updateTaskTime();
    if(this->getTaskTime() >= 5000 && !sleep){
      this->resetTaskTime(); //se non si muove lo resetta
      movement = false;
      sleep = true;
    }
  }
}
