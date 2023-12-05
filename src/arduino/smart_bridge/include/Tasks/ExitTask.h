#ifndef __EXIT_TASK__
#define __EXIT_TASK__

#include "config.h"
#include "TasksFactory.h"
#include "PeriodicTask.h"
#include "Display.h"
#include "Sonar.h"
#include "Light.h"

class ExitTask: public PeriodicTask {

public:
    ExitTask(Light *pLight, Display *pDisplay, Sonar *pSonar, unsigned int enterTime);
    const __FlashStringHelper *const getName(void) { return F("T_EXIT"); }
    void laterInit(void);
    void tick(void);
    void update(Task *pTask);
    ~ExitTask(void);

private:
    PeriodicTask *pGateOpenTask;
    PeriodicTask *pGateCloseTask;
    unsigned int enterTime;
    Light *pLight;
    Display *pDisplay;
    Sonar *pSonar;
    enum {IN, OUT} carState;

};

#endif
