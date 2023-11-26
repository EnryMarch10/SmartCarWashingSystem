#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include "ServoMotor.h"
#include <Servo.h>

class ServoMotorImpl: public ServoMotor {

public:
    ServoMotorImpl(const int pin);
    void on(void);
    void setPosition(const int angle);
    void off(void);
    ~ServoMotorImpl() {};

private:
    int pin;
    Servo motor;

};

#endif
