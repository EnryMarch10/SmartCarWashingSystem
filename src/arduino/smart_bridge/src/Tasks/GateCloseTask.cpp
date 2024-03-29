#include "Tasks/GateCloseTask.h"

GateCloseTask::GateCloseTask(Gate *pGate)
{
    this->pGate = pGate;    
}

void GateCloseTask::laterInit(void)
{
    pGate->on();
}

void GateCloseTask::tick(void)
{
    if (pGate->close()) {
        MyScheduler.periodicTaskReadyToDie(this);
    }
}

GateCloseTask::~GateCloseTask(void)
{
    pGate->off();
}
