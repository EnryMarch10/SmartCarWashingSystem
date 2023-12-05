#ifndef __CAR_READY_TASK__
#define __CAR_READY_TASK__

#include "config.h"
#include "TasksFactory.h"
#include "PeriodicTask.h"
#include "Light.h"
#include "Display.h"
#include "Button.h"

class CarReadyTask: public PeriodicTask {

public:
    CarReadyTask(Display *pDisplay, Light *pLight, Button *pButton);
    const __FlashStringHelper *const getName(void) { return F("T_CAR_READY"); }
    void laterInit(void);
    void tick(void);
    void update(Task *pTask);
    ~CarReadyTask(void);

private:
    Display *pDisplay;
    Light *pLight;
    Button *pButton;

};

#endif
