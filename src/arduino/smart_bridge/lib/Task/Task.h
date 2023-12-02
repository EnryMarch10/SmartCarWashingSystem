#ifndef __TASK__
#define __TASK__

#include "utils.h"

class Task {
  
public:
    virtual void tick(void) = 0;

    virtual void init(const int period)
    {
        myPeriod = period;  
        timeElapsed = 0;
    }

    int getPeriod(void)
    {
        return myPeriod;
    }

    bool updateAndCheckTime(const int basePeriod)
    {
        timeElapsed += basePeriod;
        if (timeElapsed >= myPeriod) {
            timeElapsed = 0;
            return true;
        } else {
            return false; 
        }
    }

    // void resume(void)
    // {
    //     active = true;
    // }

    // void stop(void)
    // {
    //     active = false;
    // }

    bool isActive(void)
    {
        return active;
    }

    virtual ~Task() { };

private:
    bool active = true;
    int myPeriod;
    int timeElapsed;

};

#endif

