#include "Tasks/CarReadyTask.h"

CarReadyTask::CarReadyTask(Display *pDisplay, Light *pLight, Button *pButton)
{
    this->pDisplay = pDisplay;
    this->pLight = pLight;
    this->pButton = pButton;
}

void CarReadyTask::laterInit(void)
{
    pLight->switchOn();
    pDisplay->on();
    pDisplay->write(F("Ready to Wash"));
    PeriodicTask *pTask = MyTasksFactory.createGateCloseTask();
    pTask->addListener(this);
    stop();
    MyScheduler.addPeriodicTask(pTask);
}

void CarReadyTask::tick(void)
{
    if (pButton->isPressed()) {
        pDisplay->off();
        MyScheduler.taskReadyToDie(this);
        MyScheduler.addPeriodicTask(MyTasksFactory.createCountDownTask());
    }
}

void CarReadyTask::update(Task *pTask)
{
    resume();
}

CarReadyTask::~CarReadyTask(void) { }
