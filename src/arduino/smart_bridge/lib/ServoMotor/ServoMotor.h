#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

class ServoMotor {

public:
    virtual void on(void) = 0;
    virtual void setPosition(const int angle) = 0;
    virtual void off(void) = 0;
    virtual ~ServoMotor() {};

};

#endif
