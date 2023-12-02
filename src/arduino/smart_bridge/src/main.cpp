#include <Arduino.h>
#include "config.h"
#include "MsgService.h"
#include "Logger.h"

#include "Scheduler.h"
#include "BlinkTask.h"
#include "PrintTask.h"

#include "Queue.h"

Scheduler sched;
Task *t3 = NULL;
Task *t2 = NULL;
Queue<void (*)(void)> *queue;

void test1(void)
{
    Logger.debug("CIAO1");
}

void test2(void)
{
    Logger.debug("CIAO2");
}

void test3(void)
{
    Logger.debug("CIAO3");
}

void setup()
{
    MsgService.init();

    queue = new Queue<void (*)(void)>();

    queue->enqueue(test1);
    queue->enqueue(test2);
    queue->enqueue(test3);
    void (*func)(void) = queue->dequeue();
    func();
    func = queue->dequeue();
    func();
    delete queue;
    
    // queue = new Queue<void (*)(void)>();
    sched.init(50);

    Task *t0 = new PrintTask();
    t0->init(500);
    
    Task *t1 = new BlinkTask(PIN_RED_LED);
    t1->init(300);

    Logger.debug("Adding print");
    sched.addTask(t0);
    Logger.debug("Adding blink 1");
    sched.addTask(t1);

    t2 = new BlinkTask(PIN_GREEN_LED_1);
    t2->init(150);
    t3 = new BlinkTask(PIN_GREEN_LED_2);
    t3->init(150);

    Logger.debug("Adding blink 3");
    sched.addTask(t3);
}

void loop()
{
    sched.schedule();
    static long start_time = millis();
    static bool state = true;
    if (state && millis() - start_time > 4000) {
        if (digitalRead(PIN_GREEN_LED_2) == HIGH) {
            Logger.debug("Deleting t3");
            sched.removeTask(t3);
            state = false;
            Logger.debug("Adding blink 2");
            sched.addTask(t2);
        }
    }
}