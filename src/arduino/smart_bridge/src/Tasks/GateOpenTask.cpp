#include "Tasks/GateOpenTask.h"

GateOpenTask::GateOpenTask(Gate *pGate)
{
    this->pGate = pGate;    
}

void GateOpenTask::laterInit(void)
{
    pGate->on();
}

void GateOpenTask::tick(void)
{
    if (pGate->open()) {
        MyScheduler.taskReadyToDie(this);
    }
}

GateOpenTask::~GateOpenTask(void)
{
    pGate->off();
}
