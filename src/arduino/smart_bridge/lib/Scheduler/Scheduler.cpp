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

static void _print_task_list(OrderedSet<PeriodicTask *, unsigned> *& tasks)
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
    pTaskSet = new OrderedSet<PeriodicTask *, unsigned>(func);
    aTaskQueue = new Queue<AperiodicTask *>();
    pTaskAskedToBeAddedQueue = new Queue<PeriodicTask *>();
    pTaskAskedToDieQueue = new Queue<PeriodicTask *>();
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
    aTaskQueue->enqueue(task);
    return true;
}

bool Scheduler::periodicTaskReadyToAdd(PeriodicTask *task)
{
    assert(task->getPeriod() % basePeriod == 0);
    MyLogger.debugln(getPrefix() + F("asked to be added periodic ") + task->getName());
    pTaskAskedToBeAddedQueue->enqueue(task);
    return true;
}

void Scheduler::periodicTaskReadyToDie(PeriodicTask *task)
{
    task->stop();
    MyLogger.debugln(getPrefix() + F("stopped and put in die queue ") + task->getName());
    pTaskAskedToDieQueue->enqueue(task);
}

bool Scheduler::addPeriodicTask(PeriodicTask *task)
{
    MyLogger.debugln(getPrefix() + F("add periodic ") + task->getName());
    const int result = pTaskSet->add(task);
    _print_task_list(pTaskSet);
    return result != BaseOrderedSet::getErrorIndex();
}

bool Scheduler::removePeriodicTask(PeriodicTask *task)
{
    MyLogger.debugln(getPrefix() + F("remove periodic ") + task->getName());
    const bool result = pTaskSet->remove(task);
    delete task;
    _print_task_list(pTaskSet);
    return result;
}

void Scheduler::runPeriodicTasks(void)
{
    for (unsigned char i = 0; i < pTaskSet->length(); i++) {
        if (pTaskSet->get(i)->updateAndCheckTime(basePeriod)) {
            if (pTaskSet->get(i)->isActive()) {
                // MyLogger.debugln(getPrefix() + F("executing periodic ")) + pTaskSet->get(i)->getName());
                pTaskSet->get(i)->tick();
            }
#ifdef __DEBUG__
            else {
                MyLogger.debugln(getPrefix() + F("skipped inactive periodic ") + pTaskSet->get(i)->getName());
            }
#endif
        }
    }

    // Remove if asked to die
    while (pTaskAskedToDieQueue->containsSomething()) {
        removePeriodicTask(pTaskAskedToDieQueue->dequeue());
    }
    // Add if asked to be added
    while (pTaskAskedToBeAddedQueue->containsSomething()) {
        addPeriodicTask(pTaskAskedToBeAddedQueue->dequeue());
    }
}

void Scheduler::runAperiodicTasks(void)
{
    while (aTaskQueue->containsSomething()) {
        Task *const task = aTaskQueue->dequeue();
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
    while (pTaskSet->containsSomething()) {
        delete pTaskSet->getFirst();
        pTaskSet->removeAt(pTaskSet->getFirstPos());
    }
    delete pTaskSet;
    delete pTaskAskedToDieQueue;
    while (pTaskAskedToBeAddedQueue->containsSomething()) {
        delete pTaskAskedToBeAddedQueue->dequeue();
    }
    delete pTaskAskedToBeAddedQueue;
}
