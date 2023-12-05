#include "config.h"
#include "TasksFactory.h"

#include "Tasks/BlinkTask.h"
#include "Tasks/SleepTask.h"
#include "Tasks/WelcomeTask.h"
#include "Tasks/EnterTask.h"
#include "Tasks/GateOpenTask.h"
#include "Tasks/GateCloseTask.h"
#include "Tasks/CountDownTask.h"
#include "Tasks/CarReadyTask.h"
#include "Tasks/MonitorTask.h"
#include "Tasks/ExitTask.h"

#include "Led.h"
#include "LcdI2C.h"
#include "SonarImpl.h"
#include "ServoMotorImpl.h"
#include "ButtonImpl.h"
#include "TemperatureSensorTMP32.h"

TasksFactory MyTasksFactory;

extern Led greenLed1;
extern Led redLed;
extern Led greenLed2;
extern LcdI2C lcd;
extern SonarImpl sonar;
extern ServoMotorImpl servoMotor;
extern ButtonImpl button;
extern TemperatureSensorTMP32 TSensor;

PeriodicTask *TasksFactory::createFastBlinkTask(void)
{
    PeriodicTask *pTask = new BlinkTask(&redLed);
    pTask->init(FAST_BLINK_PERIOD);
    return pTask;
}

PeriodicTask *TasksFactory::createSlowBlinkTask(void)
{
    PeriodicTask *pTask = new BlinkTask(&redLed);
    pTask->init(SLOW_BLINK_PERIOD);
    return pTask;
}

AperiodicTask *TasksFactory::createSleepTask(void)
{
    AperiodicTask *pTask = new SleepTask(PIN_PIR);
    pTask->init();
    return pTask;
}

PeriodicTask *TasksFactory::createWelcomeTask(void)
{
    PeriodicTask *pTask = new WelcomeTask(&greenLed1, &lcd, N1);
    pTask->init(ONE_SECOND_PERIOD);
    return pTask;
}

PeriodicTask *TasksFactory::createEnterTask(void)
{
    PeriodicTask *pTask = new EnterTask(&lcd, &sonar, N2);
    pTask->init(ONE_SECOND_PERIOD);
    return pTask;
}

PeriodicTask *TasksFactory::createGateOpenTask(void)
{
    GateOpenTask *pTask = new GateOpenTask(&servoMotor);
    pTask->init(BASE_PERIOD);
    return pTask;
}

PeriodicTask *TasksFactory::createGateCloseTask(void)
{
    GateCloseTask *pTask = new GateCloseTask(&servoMotor);
    pTask->init(BASE_PERIOD);
    return pTask;
}

PeriodicTask *TasksFactory::createCountDownTask(void)
{
    PeriodicTask *pTask = new CountDownTask(&lcd, N3);
    pTask->init(ONE_SECOND_PERIOD);
    return pTask;
}

PeriodicTask *TasksFactory::createCarReadyTask(void)
{
    PeriodicTask *pTask = new CarReadyTask(&lcd, &redLed, &button);
    pTask->init(BUTTON_SAMPLING_PERIOD);
    return pTask;
}

PeriodicTask *TasksFactory::createMonitorTask(PeriodicTask *pCountDownTask, PeriodicTask *pBlinkTask)
{
    PeriodicTask *pTask = new MonitorTask(pCountDownTask, pBlinkTask, &lcd, &TSensor, N4);
    pTask->init(ONE_SECOND_PERIOD);
    return pTask;
}

PeriodicTask *TasksFactory::createExitTask(void)
{
    PeriodicTask *pTask = new ExitTask(&greenLed2, &lcd, &sonar, N4);
    pTask->init(ONE_SECOND_PERIOD);
    return pTask;
}
