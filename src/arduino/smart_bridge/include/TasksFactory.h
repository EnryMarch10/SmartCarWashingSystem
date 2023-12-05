#ifndef __TASKS_FACTORY__
#define __TASKS_FACTORY__

// #include "PeriodicTask.h"
// #include "AperiodicTask.h"

class TasksFactory {

public:
    PeriodicTask *createSlowBlinkTask(void);
    PeriodicTask *createFastBlinkTask(void);
    AperiodicTask *createSleepTask(void);
    PeriodicTask *createWelcomeTask(void);
    PeriodicTask *createEnterTask(void);
    PeriodicTask *createGateOpenTask(void);
    PeriodicTask *createGateCloseTask(void);
    PeriodicTask *createCountDownTask(void);
    PeriodicTask *createCarReadyTask(void);
    PeriodicTask *createMonitorTask(PeriodicTask *pCountDownTask, PeriodicTask *pBlinkTask);
    PeriodicTask *createExitTask(void);
    ~TasksFactory(void) { }

};

extern TasksFactory MyTasksFactory;

#endif
