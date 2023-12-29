#include "Tasks/CountDownTask.h"

CountDownTask::CountDownTask(Display *pDisplay, const unsigned char cycles)
{
    this->pDisplay = pDisplay;
    this->cycles = cycles;
}

void CountDownTask::laterInit(void)
{
    pDisplay->on();
    pDisplay->write(String(cycles));
    pBlinkTask = MyTasksFactory.createSlowBlinkTask();
    MyScheduler.periodicTaskReadyToAdd(pBlinkTask);
    pMonitorTask = MyTasksFactory.createMonitorTask(this, pBlinkTask);
    MyScheduler.periodicTaskReadyToAdd(pMonitorTask);
}

void CountDownTask::inStop(void)
{
    pDisplay->off();
}

void CountDownTask::inResume(void)
{
    pDisplay->on();
}

void CountDownTask::tick(void)
{
    cycles--;
    pDisplay->clear();
    pDisplay->write(String(cycles));
    if (cycles == 0) {
        pDisplay->off();
        MyScheduler.periodicTaskReadyToDie(pBlinkTask);
        MyScheduler.periodicTaskReadyToDie(pMonitorTask);
        MyScheduler.periodicTaskReadyToDie(this);
        MyScheduler.periodicTaskReadyToAdd(MyTasksFactory.createExitTask());
    }
}

CountDownTask::~CountDownTask(void) { }
