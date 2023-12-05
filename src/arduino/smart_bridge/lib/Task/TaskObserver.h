#ifndef __TASK_OBSERVER__
#define __TASK_OBSERVER__

#include "utils.h"
#include "Task.h"

class TaskObserver {

public:
    virtual void update(Task *pCaller) = 0;
    virtual ~TaskObserver(void) { }

};

#endif
