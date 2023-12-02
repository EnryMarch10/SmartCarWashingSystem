#include <Arduino.h>
#include "PrintTask.h"
#include "Logger.h"

PrintTask::PrintTask(void) {}
  
void PrintTask::init(const int period)
{
    Task::init(period);
    count = 0;
}

void PrintTask::tick(void)
{
    count++;
    Logger.debug("fire " + String(count) + " millis: " + String(millis()));
}
