#include "Scheduler.h"
#include <TimerOne.h>
#include "Logger.h"

Scheduler MyScheduler;

volatile bool timerFlag;

static const __FlashStringHelper *const getName(void)
{
    return F("SCHEDULER");
}

static String getPrefix(void)
{
    return String(getName()) + F(": ");
}

static void _timer_handler(void)
{
    // MyLogger.debugln(getPrefix() + F("Scheduler time = ")) + millis());
    timerFlag = true;
}

static void _print_task_list(OrderedList<PeriodicTask *, unsigned> *& tasks)
{
#ifdef __DEBUG__
    static const __FlashStringHelper *start = F("---- START periodic tasks ----");
    static const __FlashStringHelper *end = F("---- END periodic tasks ------");
    MyLogger.debugln(start);
    MyLogger.debugln(getPrefix());
    for (int i = 0; i < tasks->length(); i++) {
        MyLogger.debugln(String(F("periodic[")) + i + F("] = (") + tasks->get(i)->getPeriod() + F(") ") + tasks->get(i)->getName());
    }
    MyLogger.debugln(end);
#endif
}

static unsigned func(PeriodicTask *& pTask) {
    return pTask->getPeriod();
}

Scheduler::Scheduler(void)
{
    MyLogger.debugln(getPrefix() + F("born"));
    aTasks = new Queue<AperiodicTask *>();
    pTasks = new OrderedList<PeriodicTask *, unsigned>(func);
    pTasksToAdd = new Queue<PeriodicTask *>();
    pTasksToRemove = new Queue<PeriodicTask *>();
}

void Scheduler::init(const int basePeriod)
{
    MyLogger.debugln(getPrefix() + F("init"));
    this->basePeriod = basePeriod;
    timerFlag = false;
    long period = 1000l * basePeriod;
    Timer1.initialize(period);
    Timer1.attachInterrupt(_timer_handler);
}

bool Scheduler::aperiodicTaskAdd(AperiodicTask *task)
{
    MyLogger.debugln(getPrefix() + F("add aperiodic ") + task->getName());
    aTasks->enqueue(task);
    return true;
}

bool Scheduler::periodicTaskReadyToAdd(PeriodicTask *task)
{
    assert(task->getPeriod() % basePeriod == 0);
    MyLogger.debugln(getPrefix() + F("asked to be added periodic ") + task->getName());
    pTasksToAdd->enqueue(task);
    return true;
}

void Scheduler::periodicTaskReadyToDie(PeriodicTask *task)
{
    task->stop();
    MyLogger.debugln(getPrefix() + F("stopped and put in die queue ") + task->getName());
    pTasksToRemove->enqueue(task);
}

bool Scheduler::addPeriodicTask(PeriodicTask *task)
{
    MyLogger.debugln(getPrefix() + F("add periodic ") + task->getName());
    pTasks->add(task);
    return true;
}

bool Scheduler::removePeriodicTask(PeriodicTask *task)
{
    MyLogger.debugln(getPrefix() + F("remove periodic ") + task->getName());
    const bool result = pTasks->remove(task);
    delete task;
    return result;
}

void Scheduler::runPeriodicTasks(void)
{
    for (unsigned char i = 0; i < pTasks->length(); i++) {
        if (pTasks->get(i)->updateAndCheckTime(basePeriod)) {
            if (pTasks->get(i)->isActive()) {
                // MyLogger.debugln(getPrefix() + F("executing periodic ")) + pTasks->get(i)->getName());
                pTasks->get(i)->tick();
            }
#ifdef __DEBUG__
            else {
                MyLogger.debugln(getPrefix() + F("skipped inactive periodic ") + pTasks->get(i)->getName());
            }
#endif
        }
    }

#ifdef __DEBUG__
    bool updateTasks = false;
#endif
    // Remove if asked to die
    while (pTasksToRemove->containsSomething()) {
        removePeriodicTask(pTasksToRemove->dequeue());
#ifdef __DEBUG__
        updateTasks = true;
#endif
    }
    // Add if asked to be added
    while (pTasksToAdd->containsSomething()) {
        addPeriodicTask(pTasksToAdd->dequeue());
#ifdef __DEBUG__
        updateTasks = true;
#endif
    }
#ifdef __DEBUG__
        if (updateTasks) {
            _print_task_list(pTasks);
        }
#endif
}

void Scheduler::runAperiodicTasks(void)
{
    while (aTasks->containsSomething()) {
        Task *const task = aTasks->dequeue();
        MyLogger.debugln(getPrefix() + F("executing aperiodic ") + task->getName());
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

Scheduler::~Scheduler(void)
{
    MyLogger.debugln(getPrefix() + F("die!"));
    while (pTasks->containsSomething()) {
        delete pTasks->getFirst();
        pTasks->removeAt(pTasks->getFirstPos());
    }
    delete pTasks;
    delete pTasksToRemove;
    while (pTasksToAdd->containsSomething()) {
        delete pTasksToAdd->dequeue();
    }
    delete pTasksToAdd;
}
