#include "PrintTask.h"
#include "Arduino.h"

PrintTask::PrintTask(void) {

}
  
void PrintTask::init(const int period) {
    Task::init(period);
    count = 0;
}
  
void PrintTask::tick(void) {
    count++;
    Serial.println("fire " + String(count) + " millis: " + String(millis()));
}
