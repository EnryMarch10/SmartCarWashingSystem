#ifndef __COUNT_DOWN_TASK__
#define __COUNT_DOWN_TASK__

#include "config.h"
#include "TasksFactory.h"
#include "PeriodicTask.h"
#include "Display.h"

class CountDownTask: public PeriodicTask {

public:
    CountDownTask(Display *pDisplay, const unsigned char cycles);
    const __FlashStringHelper *const getName(void) { return F("T_COUNT_DOWN"); }
    void laterInit(void);
    void tick(void);
    void update(Task *pTask) { }
    ~CountDownTask(void);

private:
    unsigned char cycles;
    Display *pDisplay;
    PeriodicTask *pBlinkTask;
    PeriodicTask *pMonitorTask;

};

#endif
