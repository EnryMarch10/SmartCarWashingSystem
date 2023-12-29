#include "Tasks/ExitTask.h"

ExitTask::ExitTask(Light *pLight, Display *pDisplay, Sonar *pSonar, unsigned int enterTime)
{
    this->pDisplay = pDisplay;
    this->pSonar = pSonar;
    this->enterTime = enterTime;
    this->pLight = pLight;
    carState = OUT;
}

void ExitTask::laterInit(void)
{
    pLight->switchOn();
    pDisplay->on();
    pDisplay->write(F("Washing complete, you can leave the area"));
    pGateOpenTask = MyTasksFactory.createGateOpenTask();
    pGateOpenTask->addListener(this);
    stop();
    MyScheduler.periodicTaskReadyToAdd(pGateOpenTask);
}

void ExitTask::tick(void)
{
    static long timeElapsed;
    const float distance = pSonar->getDistance();
    MyLogger.debugln(getPrefix() + F("car distance = ") + distance + F(" m"));
    switch (carState)
    {
        case IN:
            if ((distance >= MAX_DIST) || (distance == Sonar::getErrorDistance())) {
                carState = OUT;
                timeElapsed = millis();
                MyLogger.debugln(getPrefix() + F("CAR OUT"));
            }
            break;
        case OUT:
            if ((distance < MAX_DIST) && (distance != Sonar::getErrorDistance())) {
                carState = IN;
                MyLogger.debugln(getPrefix() + F("CAR IN"));
            } else if (millis() - timeElapsed >= enterTime) {
                pDisplay->off();
                pGateCloseTask = MyTasksFactory.createGateCloseTask();
                stop();
                pGateCloseTask->addListener(this);
                MyScheduler.periodicTaskReadyToAdd(pGateCloseTask);
            }
            break;
    }
}

void ExitTask::update(Task *pTask)
{
    resume();
    if (pTask == pGateOpenTask) {
        pGateOpenTask = NULL;
    } else if (pTask == pGateCloseTask) {
        pLight->switchOff();
        MyScheduler.periodicTaskReadyToDie(this);
        MyScheduler.aperiodicTaskAdd(MyTasksFactory.createSleepTask());
        pGateCloseTask = NULL;
    }
}

ExitTask::~ExitTask(void) { }
