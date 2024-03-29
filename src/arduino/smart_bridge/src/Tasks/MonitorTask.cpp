#include "Tasks/MonitorTask.h"
#include "MsgService.h"

static unsigned char numWashes = 0;

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
#ifdef __SIMULATE_MALFUNCTIONING__
    static char tmp = 0;
#endif
    const float actualT = pTSensor->getTemperature();
    if (actualT != lastT) {
        MyLogger.logln(String(F("temperature = ")) + actualT);
        lastT = actualT;
    } else {
        MyLogger.debugln(getPrefix() + F("temperature = ") + actualT);
    }
    switch (state)
    {
        case OK:
            if (actualT > MAX_T) {
                startErrorTime = millis();
                state = BEFORE_ERROR;
            }
            break;
        case BEFORE_ERROR:
            if (actualT <= MAX_T) {
                state = OK;
            } else if ((millis() - startErrorTime) > errorTime) {
#ifdef __SIMULATE_MALFUNCTIONING__
                if (!tmp) {
                    pDisplay->on();
                    pDisplay->write(F("Detected a Problem - Please Wait"));
                    pCountDownTask->stop();
                    pBlinkTask->stop();
                    MyLogger.logln(F("Maintenance Required"));
                    state = ERROR;
                }
#else
                pCountDownTask->stop();
                pBlinkTask->stop();
                pDisplay->on();
                MyLogger.logln(F("Maintenance Required"));
                pDisplay->write(F("Detected a Problem - Please Wait"));
                state = ERROR;
#endif
            }
            break;
        case ERROR:
            if (MyMsgService.isMsgAvailable()) {
                Msg* msg = MyMsgService.receiveMsg();    
                if (msg->getContent() == F("Maintenance done")) {
                    pDisplay->off();
                    pBlinkTask->resume();
                    pCountDownTask->resume();
                    state = OK;
#ifdef __SIMULATE_MALFUNCTIONING__
                    tmp = 1;
#endif
                }
                delete msg;
            }
            break;
    }
}

MonitorTask::~MonitorTask(void)
{
    numWashes++;
    MyLogger.logln(String(F("washes = ")) + numWashes);
}
