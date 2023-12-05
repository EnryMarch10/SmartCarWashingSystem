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
    MyScheduler.addPeriodicTask(pBlinkTask);
    pMonitorTask = MyTasksFactory.createMonitorTask(this, pBlinkTask);
    MyScheduler.addPeriodicTask(pMonitorTask);
}

void CountDownTask::tick(void)
{
    cycles--;
    pDisplay->clear();
    pDisplay->write(String(cycles));
    if (cycles == 0) {
        pDisplay->off();
        MyScheduler.taskReadyToDie(pBlinkTask);
        MyScheduler.taskReadyToDie(pMonitorTask);
        MyScheduler.taskReadyToDie(this);
        MyScheduler.addPeriodicTask(MyTasksFactory.createExitTask());
    }
}

CountDownTask::~CountDownTask(void) { }
