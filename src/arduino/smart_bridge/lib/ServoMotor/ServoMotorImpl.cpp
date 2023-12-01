#include <Arduino.h>
#include "ServoMotorImpl.h"

#ifdef __DEBUG__
    #include <assert.h>
#endif

#define MIN_ANGLE 0
#define MAX_ANGLE 180

ServoMotorImpl::ServoMotorImpl(const int pin)
{
    this->pin = pin;  
} 

void ServoMotorImpl::on(void)
{
    motor.attach(pin);    
}

int ServoMotorImpl::readPosition(void)
{
    return map(motor.read(), MIN_PULSE_WIDTH, MAX_PULSE_WIDTH, MIN_ANGLE, MAX_ANGLE);              
}

void ServoMotorImpl::setPosition(const int angle)
{
#ifdef __DEBUG__
    assert(angle >= MIN_ANGLE && angle <= MAX_ANGLE);
#endif
    motor.write(map(angle, MIN_ANGLE, MAX_ANGLE, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH));              
}

void ServoMotorImpl::off(void)
{
    motor.detach();    
}
