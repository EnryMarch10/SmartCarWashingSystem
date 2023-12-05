#ifndef __SLEEP_TASK__
#define __SLEEP_TASK__

#include "config.h"
#include "AperiodicTask.h"

class SleepTask: public AperiodicTask {

public:
    SleepTask(const int pirPin);
    const __FlashStringHelper *const getName(void) { return F("T_SLEEP"); }
    void init(void);
    void tick(void);
    ~SleepTask(void);

private:
    int pirPin;

};

#endif
