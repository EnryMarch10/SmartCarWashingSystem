#include "BlinkTask.h"

BlinkTask::BlinkTask(const int pin) {
    this->pin = pin;    
}
  
void BlinkTask::init(const int period) {
    Task::init(period);
    led = new Led(pin); 
    state = OFF;    
}
  
void BlinkTask::tick(void) {
    switch (state) {
        case OFF:
            led->switchOn();
            state = ON; 
            break;
        case ON:
            led->switchOff();
            state = OFF;
            break;
    }
}
