#ifndef __TASK__
#define __TASK__

class Task {
  
public:
    virtual void tick(void) = 0;

    virtual void init(const int period) {
        myPeriod = period;  
        timeElapsed = 0;
    }

    bool updateAndCheckTime(const int basePeriod) {
        timeElapsed += basePeriod;
        if (timeElapsed >= myPeriod) {
            timeElapsed = 0;
            return true;
        } else {
            return false; 
        }
    }

private:
    int myPeriod;
    int timeElapsed;

};

#endif

