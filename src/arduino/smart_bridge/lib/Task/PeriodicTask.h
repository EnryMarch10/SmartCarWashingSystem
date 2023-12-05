#ifndef __PERIODIC_TASK__
#define __PERIODIC_TASK__

#include "utils.h"
#include "ObservableTask.h"
#include "TaskObserver.h"
#include "Logger.h"

class PeriodicTask: public ObservableTask, public TaskObserver {
  
public:
    virtual void tick(void) = 0;

    void init(const int period)
    {
        MyLogger.debug(String(getName()) + F(": ") + TASK_INIT);
        myPeriod = period;  
        timeElapsed = 0;
        laterInit();
    }

    virtual void laterInit(void) = 0;

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

    void stop(void)
    {
        MyLogger.debug(String(getName()) + F(": ") + TASK_STOP);
        active = false;
    }

    void resume(void)
    {
        MyLogger.debug(String(getName()) + F(": ") + TASK_RESUME);
        active = true;
    }

    bool isActive(void)
    {
        return active;
    }

    virtual ~PeriodicTask(void)
    {
        ObservableTask::notifyListeners();
    }

private:
    bool active = true;
    int myPeriod;
    int timeElapsed;

};

#endif
