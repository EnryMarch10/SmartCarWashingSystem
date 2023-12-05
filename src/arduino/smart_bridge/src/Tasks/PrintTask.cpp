#include "Tasks/PrintTask.h"

PrintTask::PrintTask(void)
{
}

void PrintTask::laterInit(void)
{
    count = 0;
}

void PrintTask::tick(void)
{
    count++;
    MyLogger.debug(String(F("fire ")) + count + F(" millis: ") + millis() + F(" ms"));
}
