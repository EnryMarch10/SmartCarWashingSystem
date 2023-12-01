#include "Scheduler.h"
#include <TimerOne.h>

volatile bool timerFlag;

void timer_handler(void) {
  timerFlag = true;
}

void Scheduler::init(const int basePeriod) {
    this->basePeriod = basePeriod;
    timerFlag = false;
    long period = 1000l * basePeriod;
    Timer1.initialize(period);
    Timer1.attachInterrupt(timer_handler);
    nTasks = 0;
}

bool Scheduler::addTask(Task *task) {
    if (nTasks < MAX_TASKS - 1){
        taskList[nTasks] = task;
        nTasks++;
        return true;
    } else {
        return false; 
    }
}
  
void Scheduler::schedule(void) {   
    while (!timerFlag) {}
    timerFlag = false;

    for (int i = 0; i < nTasks; i++) {
        if (taskList[i]->updateAndCheckTime(basePeriod)) {
            taskList[i]->tick();
        }
    }
}
