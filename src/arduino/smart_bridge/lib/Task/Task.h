#ifndef __TASK__
#define __TASK__

#include "utils.h"

class Task {

public:
    virtual const __FlashStringHelper *const getName(void) = 0;
    String getPrefix(void)
    {
        return String(getName()) + F(": ");
    }
    virtual void tick(void) = 0;
    bool operator==(const Task& rhs) const
    {
        return this == &rhs;
    }
    virtual ~Task(void) { }

};

#endif
