#include "Tasks/SleepTask.h"
#include <avr/sleep.h>

static void _wakeup_handler(void)
{
    MyLogger.debugln(F("PIR detected something!"));
    disable_all_interrupts();
}

SleepTask::SleepTask(const int pirPin)
{
    this->pirPin = pirPin;
}

void SleepTask::init(void) { }

void SleepTask::tick(void)
{
    MyLogger.debugln(getPrefix() + F("Going to sleep..."));
    MyLogger.flush();
    enable_interrupt(pirPin, _wakeup_handler, RISING);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
    MyLogger.debugln(getPrefix() + F("Waking up..."));
    MyScheduler.periodicTaskReadyToAdd(MyTasksFactory.createWelcomeTask());
}

SleepTask::~SleepTask(void) { }
