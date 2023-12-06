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
    MyScheduler.addPeriodicTask(pGateOpenTask);
}

void ExitTask::tick(void)
{
    static long timeElapsed;
    MyLogger.debug(getPrefix() + F("car distance = ") + pSonar->getDistance() + F(" m"));
    switch (carState)
    {
        case IN:
            if (pSonar->getDistance() >= MAX_DIST) {
                carState = OUT;
                timeElapsed = millis();
                MyLogger.debug(getPrefix() + F("CAR OUT"));
            }
            break;
        case OUT:
            if (pSonar->getDistance() < MAX_DIST) {
                carState = IN;
                MyLogger.debug(getPrefix() + F("CAR IN"));
            } else if (millis() - timeElapsed >= enterTime) {
                pDisplay->off();
                pGateCloseTask = MyTasksFactory.createGateCloseTask();
                stop();
                pGateCloseTask->addListener(this);
                MyScheduler.addPeriodicTask(pGateCloseTask);
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
        MyScheduler.taskReadyToDie(this);
        MyScheduler.addAperiodicTask(MyTasksFactory.createSleepTask());
        pGateCloseTask = NULL;
    }
}

ExitTask::~ExitTask(void) { }
