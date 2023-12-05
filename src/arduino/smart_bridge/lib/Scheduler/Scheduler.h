#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "utils.h"
#include "PeriodicTask.h"
#include "AperiodicTask.h"
#include "Queue.h"

#define MAX_PERIODIC_TASKS 50

class Scheduler {

public:
    Scheduler(void);
    void init(const int basePeriod);
    bool addAperiodicTask(AperiodicTask *task);
    bool addPeriodicTask(PeriodicTask *task);
    void taskReadyToDie(PeriodicTask *finished);
    void schedule(void);
    ~Scheduler(void);

private:
    int basePeriod;
    int pNTasks;
    PeriodicTask *pTaskList[MAX_PERIODIC_TASKS];
    Queue<AperiodicTask *> *aTaskQueue;
    Queue<PeriodicTask *> *askedToDieQueue;

    void runPeriodicTasks(void);
    void runAperiodicTasks(void);
    bool removePeriodicTask(PeriodicTask *task);
    const __FlashStringHelper *const getName(void);

};

extern Scheduler MyScheduler;

#endif
