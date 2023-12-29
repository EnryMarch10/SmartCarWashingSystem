#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "utils.h"
#include "PeriodicTask.h"
#include "AperiodicTask.h"
#include "Queue.h"
#include "OrderedList.h"

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
    Queue<AperiodicTask *> *aTasks;
    OrderedList<PeriodicTask *, unsigned> *pTasks;
    Queue<PeriodicTask *> *pTasksToAdd;
    Queue<PeriodicTask *> *pTasksToRemove;

    void runPeriodicTasks(void);
    void runAperiodicTasks(void);
    bool addPeriodicTask(PeriodicTask *task);
    bool removePeriodicTask(PeriodicTask *task);

};

extern Scheduler MyScheduler;

#endif
