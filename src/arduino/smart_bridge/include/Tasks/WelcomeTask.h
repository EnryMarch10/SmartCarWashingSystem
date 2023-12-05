#ifndef __WELCOME_TASK__
#define __WELCOME_TASK__

#include "config.h"
#include "TasksFactory.h"
#include "PeriodicTask.h"
#include "Light.h"
#include "Display.h"

class WelcomeTask: public PeriodicTask {

public:
    WelcomeTask(Light *pLight, Display *pDisplay, const unsigned char cycles);
    const __FlashStringHelper *const getName(void) { return F("T_WELCOME"); }
    void laterInit(void);
    void tick(void);
    void update(Task *pTask) { }
    ~WelcomeTask(void);

private:
    unsigned char cycles;
    Light *pLight;
    Display *pDisplay;

};

#endif
