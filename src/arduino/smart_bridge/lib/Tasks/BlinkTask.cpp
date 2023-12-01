#include "BlinkTask.h"

BlinkTask::BlinkTask(const int pin)
{
    this->pin = pin;    
}

void BlinkTask::init(const int period)
{
    Task::init(period);
    led = new Led(pin);
}

void BlinkTask::tick(void)
{
    led->toggle();
}

BlinkTask::~BlinkTask(void)
{
    led->switchOff();
    delete led;
}
