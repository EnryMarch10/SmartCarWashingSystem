#ifndef __PERIODIC_TASK__
#define __PERIODIC_TASK__

#include "utils.h"
#include "ObservableTask.h"
#include "TaskObserver.h"
#include "Logger.h"

class PeriodicTask: public ObservableTask, public TaskObserver {

public:
    virtual void tick(void) = 0;

    void init(const unsigned period)
    {
        MyLogger.debugln(getPrefix() + TASK_INIT);
        myPeriod = period;
        timeElapsed = 0;
        laterInit();
    }

    virtual void laterInit(void) = 0;

    unsigned getPeriod(void)
    {
        return myPeriod;
    }

    bool updateAndCheckTime(const unsigned basePeriod)
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
        MyLogger.debugln(getPrefix() + TASK_STOP);
        active = false;
        inStop();
    }

    virtual void inStop(void) { }

    void resume(void)
    {
        MyLogger.debugln(getPrefix() + TASK_RESUME);
        active = true;
        inResume();
    }

    virtual void inResume(void) { }

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
    unsigned myPeriod;
    unsigned timeElapsed;

};

#endif
