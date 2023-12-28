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
    MyScheduler.addPeriodicTask(pBlinkTask);
    PeriodicTask *pTask = MyTasksFactory.createGateOpenTask();
    pTask->addListener(this);
    stop();
    MyScheduler.addPeriodicTask(pTask);
}

void EnterTask::tick(void)
{
    static long timeElapsed;
    MyLogger.debugln(getPrefix() + F("car distance = ") + pSonar->getDistance() + F(" m"));
    switch (carState)
    {
        case IN:
            if (pSonar->getDistance() >= MIN_DIST) {
                carState = OUT;
                MyLogger.debugln(getPrefix() + F("CAR OUT"));
            } else if (millis() - timeElapsed >= enterTime) {
                pDisplay->off();
                MyScheduler.taskReadyToDie(this);
                MyScheduler.taskReadyToDie(pBlinkTask);
                MyScheduler.addPeriodicTask(MyTasksFactory.createCarReadyTask());
            }
            break;
        case OUT:
            if (pSonar->getDistance() < MIN_DIST) {
                carState = IN;
                timeElapsed = millis();
                MyLogger.debugln(getPrefix() + F("CAR IN"));
            }
            break;
    }
}

void EnterTask::update(Task *pTask)
{
    resume();
}

EnterTask::~EnterTask(void) { }
