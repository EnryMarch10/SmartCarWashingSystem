#include "Tasks/WelcomeTask.h"

WelcomeTask::WelcomeTask(Light *pLight, Display *pDisplay, const unsigned char cycles)
{
    this->pLight = pLight;
    this->pDisplay = pDisplay;
    this->cycles = cycles;
}

void WelcomeTask::laterInit(void)
{
    pLight->switchOn();
    pDisplay->on();
    pDisplay->write(F("Welcome"));
}

void WelcomeTask::tick(void)
{
    if (cycles == 0) {
        pLight->switchOff();
        pDisplay->off();
        MyScheduler.taskReadyToDie(this);
        MyScheduler.addPeriodicTask(MyTasksFactory.createEnterTask());
    }
    cycles--;
}

WelcomeTask::~WelcomeTask(void) { }
