#ifndef __BUTTON__
#define __BUTTON__

#include "run.h"

class Button {

public:
    virtual bool isPressed(void) = 0;
    virtual ~Button() {};

};

#endif
