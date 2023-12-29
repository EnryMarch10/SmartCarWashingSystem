#include "config.h"

void setup()
{
    init_config();
    MyScheduler.init(BASE_PERIOD);
    MyScheduler.aperiodicTaskAdd(MyTasksFactory.createSleepTask());
}

void loop()
{
    MyScheduler.schedule();
}
