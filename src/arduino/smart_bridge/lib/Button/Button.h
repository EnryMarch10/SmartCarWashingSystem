#ifndef __BUTTON__
#define __BUTTON__

class Button {

public:
    virtual bool isPressed(void) = 0;
    virtual ~Button() {};

};

#endif
