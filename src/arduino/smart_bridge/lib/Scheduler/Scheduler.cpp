#include "Scheduler.h"
#include <TimerOne.h>
#include "Logger.h"

Scheduler MyScheduler;

volatile bool timerFlag;

static void _timer_handler(void)
{
    // MyLogger.debug(String(F("Scheduler time = ")) + millis());
    timerFlag = true;
}

static void _print_task_list(PeriodicTask **task, const unsigned char size)
{
#ifdef __DEBUG__
    const __FlashStringHelper *separator = F("-------------------------------------------");
    MyLogger.debug(F("Periodic tasks:"));
    MyLogger.debug(separator);
    for (int i = 0; i < size; i++) {
        MyLogger.debug(String(F("periodic[")) + i + F("] = ") + task[i]->getName());
    }
    MyLogger.debug(separator);
#endif
}

Scheduler::Scheduler(void)
{
    MyLogger.debug(String(getName()) + F(": born"));
    askedToDieQueue = new Queue<PeriodicTask *>();
    aTaskQueue = new Queue<AperiodicTask *>();
}

const __FlashStringHelper *const Scheduler::getName(void)
{
    return F("SCHEDULER");
}

void Scheduler::init(const int basePeriod)
{
    MyLogger.debug(String(getName()) + F(": init"));
    this->basePeriod = basePeriod;
    timerFlag = false;
    long period = 1000l * basePeriod;
    Timer1.initialize(period);
    Timer1.attachInterrupt(_timer_handler);
    pNTasks = 0;
}

bool Scheduler::addAperiodicTask(AperiodicTask *task)
{
    MyLogger.debug(String(getName()) + F(": add aperiodic ") + task->getName());
    aTaskQueue->enqueue(task);
    return true;
}

bool Scheduler::addPeriodicTask(PeriodicTask *task)
{
    MyLogger.debug(String(getName()) + F(": add periodic ") + task->getName());
    if (pNTasks >= MAX_PERIODIC_TASKS - 1) {
        return false;
    }

    bool found = false;
    int limit = pNTasks;
    PeriodicTask *prev;
    for (int i = 0; i < limit; i++) {
        if (found) {
            swap<>(prev, pTaskList[i]);
        } else if (task->getPeriod() < pTaskList[i]->getPeriod()) {
            prev = pTaskList[i];
            pTaskList[i] = task;
            limit++;
            found = true;
        }
    }
    if (!found) {
        pTaskList[pNTasks] = task;
    }
    pNTasks++;

    _print_task_list(pTaskList, pNTasks);
    
    return true;
}

bool Scheduler::removePeriodicTask(PeriodicTask *task)
{
    MyLogger.debug(String(getName()) + F(": removing ") + task->getName());
    bool found = false;
    for (int i = 0; i < pNTasks; i++) {
        if (found) {
            pTaskList[i - 1] = pTaskList[i];
        }
        else if (pTaskList[i] == task) {
            delete pTaskList[i];
            found = true;
        }
    }
    if (found) {
        pNTasks--;
    }

    _print_task_list(pTaskList, pNTasks);

    return found;
}

void Scheduler::runPeriodicTasks(void)
{
    // Execute if their turn
    for (int i = 0; i < pNTasks; i++) {
        if (pTaskList[i]->updateAndCheckTime(basePeriod)) {
            if (pTaskList[i]->isActive()) {
                // MyLogger.debug(String(getName()) + F(": executing periodic ")) + pTaskList[i]->getName());
                pTaskList[i]->tick();
            } else {
                MyLogger.debug(String(getName()) + F(": skipped inactive periodic ") + pTaskList[i]->getName());
            }
        }
    }

    // Remove if  asked to die
    while (!askedToDieQueue->isEmpty()) {
        PeriodicTask *pTask = askedToDieQueue->dequeue();
        MyLogger.debug(String(getName()) + F(": removing periodic ") + pTask->getName());
        removePeriodicTask(pTask);
    }
}

void Scheduler::runAperiodicTasks(void)
{
    while (!aTaskQueue->isEmpty()) {
        Task *task = aTaskQueue->dequeue();
        MyLogger.debug(String(getName()) + F(": executing aperiodic ") + task->getName());
        task->tick();
        delete task;
    }
}

void Scheduler::schedule(void)
{
    do {
        runAperiodicTasks();
    } while (!timerFlag);
    timerFlag = false;

    runPeriodicTasks();
}

void Scheduler::taskReadyToDie(PeriodicTask *finished)
{
    finished->stop();
    MyLogger.debug(String(getName()) + F(": stopped and put in die queue ") + finished->getName());
    askedToDieQueue->enqueue(finished);
}

Scheduler::~Scheduler(void)
{
    MyLogger.debug(String(getName()) + F(": die!"));
    for (int i = 0; i < pNTasks; i++) {
        delete pTaskList[i];
    }
    delete askedToDieQueue;
}
