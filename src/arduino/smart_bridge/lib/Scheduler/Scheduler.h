#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 50

class Scheduler {

public:
    void init(const int basePeriod);  
    bool addTask(Task *task);  
    void schedule(void);

private:
    int basePeriod;
    int nTasks;
    Task *taskList[MAX_TASKS];

};

#endif
