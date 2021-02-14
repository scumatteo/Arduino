#include "MovementDetectionTask.h"
#include "Arduino.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include "MsgService.h"

#define DT2B 5000

extern bool on;
extern bool maintenance;
extern bool standby;
extern bool ready;

MovementDetectionTask::MovementDetectionTask(int pin){
  this->pin = pin;
}

void MovementDetectionTask::init(int period){
    Task::init(period);
    pir = new Pir(pin);
}

void MovementDetectionTask::tick(){
  if(!maintenance){
    if(!ready){
      if(standby){
        set_sleep_mode(SLEEP_MODE_IDLE);
        sleep_enable();
        power_adc_disable();
        power_spi_disable();
        power_timer0_disable(); // only timer 1
        power_timer2_disable(); // on
        power_twi_disable();
        sleep_mode();
        sleep_disable();
        power_all_enable();
      }
      pir->isMoved() ? mnt = true : mnt = false; //legge il pir
      if(mnt){
        if(!on){
          standby = false;
          on = true;
        } 
        this->resetTaskTime();       
      }
      else{
        if(on){
          this->updateTaskTime();
          if(this->getTaskTime() >= DT2B){
            this->resetTaskTime(); //se non si muove lo resetta
            on = false;
            standby = true;
          }
        }
      }
    }
  }
}
