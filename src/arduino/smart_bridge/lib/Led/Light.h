#ifndef __LIGHT__
#define __LIGHT__

class Light {

public:
    virtual bool isOn(void) = 0;
    virtual bool isOff(void) = 0;
    virtual void switchOn(void) = 0;
    virtual void switchOff(void) = 0;
    virtual void toggle(void) = 0;
    virtual ~Light() {};

};

#endif

