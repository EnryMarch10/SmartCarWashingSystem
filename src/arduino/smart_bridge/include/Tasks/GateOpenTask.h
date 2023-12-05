#ifndef __GATE_OPEN_TASK__
#define __GATE_OPEN_TASK__

#include "config.h"
#include "TasksFactory.h"
#include "PeriodicTask.h"
#include "Gate.h"

class GateOpenTask: public PeriodicTask {

public:
    GateOpenTask(Gate *pGate);
    const __FlashStringHelper *const getName(void) { return F("T_GATE_OPEN"); }
    void laterInit(void);
    void tick(void);
    void update(Task *pTask) { }
    ~GateOpenTask();

private:
    Gate *pGate;

};

#endif
