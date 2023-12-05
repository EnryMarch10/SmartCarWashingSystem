#ifndef __PRINT_TASK__
#define __PRINT_TASK__

#include "config.h"
#include "TasksFactory.h"
#include "PeriodicTask.h"

class PrintTask: public PeriodicTask {

public:
    PrintTask(void);
    const __FlashStringHelper *const getName(void) { return F("T_PRINT"); }
    void laterInit(void);
    void tick(void);
    void update(Task *pTask) { }
    ~PrintTask() { }

private:
    int count;

};

#endif
