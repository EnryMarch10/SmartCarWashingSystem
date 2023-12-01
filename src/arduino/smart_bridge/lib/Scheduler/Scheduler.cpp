#include "Scheduler.h"
#include <TimerOne.h>

volatile bool timerFlag;

void timer_handler(void)
{
  timerFlag = true;
}

void Scheduler::init(const int basePeriod)
{
    this->basePeriod = basePeriod;
    timerFlag = false;
    long period = 1000l * basePeriod;
    Timer1.initialize(period);
    Timer1.attachInterrupt(timer_handler);
    nTasks = 0;
}

bool Scheduler::addTask(Task *task)
{
    if (nTasks >= MAX_TASKS - 1) {
        return false;
    }

    bool found = false;
    int limit = nTasks;
    Task *prev;
    for (int i = 0; i < limit; i++) {
        if (found) {
            Task *tmp;
            TMP_SWAP(tmp, prev, taskList[i]);
        } else if (task->getPeriod() < taskList[i]->getPeriod()) {
            prev = taskList[i];
            taskList[i] = task;
            limit++;
            found = true;
        }
    }
    if (!found) {
        taskList[nTasks] = task;
    }
    nTasks++;
    
    return true;
}

bool Scheduler::removeTask(Task *task)
{
    bool found = false;
    for (int i = 0; i < nTasks; i++) {
        if (found) {
            taskList[i - 1] = taskList[i];
        }
        else if (taskList[i] == task) {
            delete taskList[i];
            found = true;
        }
    }
    if (found) {
        nTasks--;
    }
    return found;
}

void Scheduler::schedule(void)
{   
    while (!timerFlag) {}
    timerFlag = false;

    for (int i = 0; i < nTasks; i++) {
        if (taskList[i]->updateAndCheckTime(basePeriod)) {
            taskList[i]->tick();
        }
    }
}
