#include <Arduino.h>
#include "ServoMotorImpl.h"

ServoMotorImpl::ServoMotorImpl(const int pin){
    this->pin = pin;  
} 

void ServoMotorImpl::on(void){
    motor.attach(pin);    
}

void ServoMotorImpl::setPosition(const int angle){
    motor.write(angle);              
}

void ServoMotorImpl::off(void){
    motor.detach();    
}
