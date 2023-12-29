#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "utils.h"
#include "PeriodicTask.h"
#include "AperiodicTask.h"
#include "Queue.h"
#include "OrderedSet.h"

class Scheduler {

public:
    Scheduler(void);
    void init(const int basePeriod);
    bool aperiodicTaskAdd(AperiodicTask *task);
    bool periodicTaskReadyToAdd(PeriodicTask *task);
    void periodicTaskReadyToDie(PeriodicTask *task);
    void schedule(void);
    ~Scheduler(void);

private:
    int basePeriod;
    OrderedSet<PeriodicTask *, unsigned> *pTaskSet;
    Queue<PeriodicTask *> *pTaskAskedToBeAddedQueue;
    Queue<AperiodicTask *> *aTaskQueue;
    Queue<PeriodicTask *> *pTaskAskedToDieQueue;

    void runPeriodicTasks(void);
    void runAperiodicTasks(void);
    bool addPeriodicTask(PeriodicTask *task);
    bool removePeriodicTask(PeriodicTask *task);

};

extern Scheduler MyScheduler;

#endif
