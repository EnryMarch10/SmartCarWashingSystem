#ifndef __ENTER_TASK__
#define __ENTER_TASK__

#include "config.h"
#include "TasksFactory.h"
#include "PeriodicTask.h"
#include "Display.h"
#include "Sonar.h"

class EnterTask: public PeriodicTask {

public:
    EnterTask(Display *pDisplay, Sonar *pSonar, unsigned int enterTime);
    const __FlashStringHelper *const getName(void) { return F("T_ENTER"); }
    void laterInit(void);
    void tick(void);
    void update(Task *pTask);
    ~EnterTask(void);

private:
    unsigned int enterTime;
    PeriodicTask *pBlinkTask;
    Display *pDisplay;
    Sonar *pSonar;
    enum {IN, OUT} carState;

};

#endif
