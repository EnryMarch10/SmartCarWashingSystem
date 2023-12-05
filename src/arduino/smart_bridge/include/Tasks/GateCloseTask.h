#ifndef __GATE_CLOSE_TASK__
#define __GATE_CLOSE_TASK__

#include "config.h"
#include "TasksFactory.h"
#include "PeriodicTask.h"
#include "Gate.h"

class GateCloseTask: public PeriodicTask {

public:
    GateCloseTask(Gate *pGate);
    const __FlashStringHelper *const getName(void) { return F("T_GATE_CLOSE"); }
    void laterInit(void);
    void tick(void);
    void update(Task *pTask) { }
    ~GateCloseTask();

private:
    Gate *pGate;

};

#endif
