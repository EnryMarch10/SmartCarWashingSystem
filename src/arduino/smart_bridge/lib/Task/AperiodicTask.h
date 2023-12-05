#ifndef __APERIODIC_TASK__
#define __APERIODIC_TASK__

#include "utils.h"
#include "Task.h"
#include "Logger.h"

class AperiodicTask: public Task {

public:
    virtual void init(void) = 0;
    virtual ~AperiodicTask(void) { }

};

#endif
