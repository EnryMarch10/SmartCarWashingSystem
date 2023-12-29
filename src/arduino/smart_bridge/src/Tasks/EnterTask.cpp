#include "Tasks/EnterTask.h"

EnterTask::EnterTask(Display *pDisplay, Sonar *pSonar, unsigned int enterTime)
{
    this->pDisplay = pDisplay;
    this->pSonar = pSonar;
    this->enterTime = enterTime;
    carState = OUT;
}

void EnterTask::laterInit(void)
{
    pDisplay->on();
    pDisplay->write(F("Proceed to the Washing Area"));
    pBlinkTask = MyTasksFactory.createFastBlinkTask();
    MyScheduler.periodicTaskReadyToAdd(pBlinkTask);
    PeriodicTask *pTask = MyTasksFactory.createGateOpenTask();
    pTask->addListener(this);
    stop();
    MyScheduler.periodicTaskReadyToAdd(pTask);
}

void EnterTask::tick(void)
{
    static long timeElapsed;
    const float distance = pSonar->getDistance();
    MyLogger.debugln(getPrefix() + F("car distance is ") + distance + F(" m"));
    switch (carState)
    {
        case IN:
            if ((distance >= MIN_DIST) || (distance == Sonar::getErrorDistance())) {
                carState = OUT;
                MyLogger.debugln(getPrefix() + F("car OUT"));
            } else if (millis() - timeElapsed >= enterTime) {
                pDisplay->off();
                MyScheduler.periodicTaskReadyToDie(this);
                MyScheduler.periodicTaskReadyToDie(pBlinkTask);
                MyScheduler.periodicTaskReadyToAdd(MyTasksFactory.createCarReadyTask());
            }
            break;
        case OUT:
            if ((distance < MIN_DIST) && (distance != Sonar::getErrorDistance())) {
                carState = IN;
                timeElapsed = millis();
                MyLogger.debugln(getPrefix() + F("car IN"));
            }
            break;
    }
}

void EnterTask::update(Task *pTask)
{
    resume();
}

EnterTask::~EnterTask(void) { }
