#include <Arduino.h>
#include "ServoMotorImpl.h"

#define MIN_ANGLE 0
#define MAX_ANGLE 180

ServoMotorImpl::ServoMotorImpl(const int pin)
{
    this->pin = pin;
    pMotor = new ServoTimer2();
} 

void ServoMotorImpl::on(void)
{
    pMotor->attach(pin);    
}

int ServoMotorImpl::readPosition(void)
{
    return map(pMotor->read(), MIN_PULSE_WIDTH, MAX_PULSE_WIDTH, MIN_ANGLE, MAX_ANGLE);              
}

void ServoMotorImpl::setPosition(const int angle)
{
#ifdef __DEBUG__
    assert(angle >= MIN_ANGLE && angle <= MAX_ANGLE);
#endif
    pMotor->write(map(angle, MIN_ANGLE, MAX_ANGLE, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH));              
}

void ServoMotorImpl::off(void)
{
    pMotor->detach();    
}

ServoMotorImpl::~ServoMotorImpl(void)
{
    delete pMotor;
}
