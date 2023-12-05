#ifndef __BLINK_TASK__
#define __BLINK_TASK__

#include "config.h"
#include "TasksFactory.h"
#include "PeriodicTask.h"
#include "Light.h"

class BlinkTask: public PeriodicTask {

public:
    BlinkTask(Light *pLight);
    const __FlashStringHelper *const getName(void) { return F("T_BLINK"); }
    void laterInit(void);
    void tick(void);
    void update(Task *pTask) { }
    ~BlinkTask();

private:
    Light *pLight;

};

#endif
