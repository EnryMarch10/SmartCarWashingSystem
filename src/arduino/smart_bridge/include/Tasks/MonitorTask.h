#ifndef __MONITOR_TASK__
#define __MONITOR_TASK__

#include "config.h"
#include "TasksFactory.h"
#include "PeriodicTask.h"
#include "TemperatureSensor.h"
#include "Display.h"

class MonitorTask: public PeriodicTask {

public:
    MonitorTask(PeriodicTask *pCountDownTask, PeriodicTask *pBlinkTask, Display *pDisplay, TemperatureSensor *pTSensor, unsigned int errorTime);
    const __FlashStringHelper *const getName(void) { return F("T_MONITOR"); }
    void laterInit(void);
    void tick(void);
    void update(Task *pTask) { }
    ~MonitorTask(void);

private:
    long startErrorTime;
    unsigned int errorTime;
    PeriodicTask *pCountDownTask;
    PeriodicTask *pBlinkTask;
    TemperatureSensor *pTSensor;
    Display *pDisplay;
    float lastT;
    enum {OK, BEFORE_ERROR, ERROR} state;

};

#endif
