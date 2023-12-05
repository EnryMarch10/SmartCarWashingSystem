#include "Tasks/MonitorTask.h"

MonitorTask::MonitorTask(PeriodicTask *pCountDownTask,
                         PeriodicTask *pBlinkTask,
                         Display *pDisplay,
                         TemperatureSensor *pTSensor,
                         unsigned int errorTime)
{
    this->pTSensor = pTSensor;
    this->pDisplay = pDisplay;
    this->pCountDownTask = pCountDownTask;
    this->pBlinkTask = pBlinkTask;
    this->errorTime = errorTime;
    state = OK;
    lastT = -1;
}

void MonitorTask::laterInit(void) { }

void MonitorTask::tick(void)
{
    static long start_high_T_time;
    const float actualT = pTSensor->getTemperature();
    if (actualT != lastT) {
        // TODO: Send T to pc
        MyLogger.log(String(getName()) + F(": temperature = ") + actualT);
        lastT = actualT;
    } else {
        MyLogger.debug(String(getName()) + F(": temperature = ") + actualT);
    }
    switch (state)
    {
        case OK:
            if (actualT > MAX_T) {
                start_high_T_time = millis();
                state = BEFORE_ERROR;
            }
            break;
        case BEFORE_ERROR:
            if (actualT <= MAX_T) {
                state = OK;
            } else if ((millis() - start_high_T_time) > errorTime) {
                pDisplay->on();
                pDisplay->write(F("Detected a Problem - Please Wait"));
                pCountDownTask->stop();
                pBlinkTask->stop();
                // TODO: send error to pc
                MyLogger.log(F("Maintenance Required"));
                state = ERROR;
            }
            break;
        case ERROR:
            // TODO: listen if pc sends "Maintenance done"
            if (actualT <= MAX_T) {
                state = OK;
                pDisplay->off();
            }
            break;
    }
}

MonitorTask::~MonitorTask(void) { }
