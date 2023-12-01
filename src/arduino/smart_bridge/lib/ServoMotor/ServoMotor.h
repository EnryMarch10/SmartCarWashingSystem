#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

#include "utils.h"

class ServoMotor {

public:
    /**
     * Turns on the motor.
    */
    virtual void on(void) = 0;
    /**
     * Retrieves the angle of rotation in degrees 0 to 180.
    */
    virtual int readPosition(void) = 0;
    /**
     * Accepts the angle of rotation in degrees 0 to 180.
    */
    virtual void setPosition(const int angle) = 0;
    /**
     * Turns off the motor.
    */
    virtual void off(void) = 0;
    virtual ~ServoMotor() {};

};

#endif
