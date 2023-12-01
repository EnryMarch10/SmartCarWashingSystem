#include <Arduino.h>
#include "config.h"

#include "Scheduler.h"
#include "BlinkTask.h"
#include "PrintTask.h"

Scheduler sched;
Task *t3 = NULL;
Task *t2 = NULL;

void setup()
{
    Serial.begin(9600);

    sched.init(50);

    Task *t0 = new PrintTask();
    t0->init(500);
    
    Task *t1 = new BlinkTask(PIN_RED_LED);
    t1->init(300);

    Serial.println("Adding print");
    sched.addTask(t0);
    Serial.println("Adding blink 1");
    sched.addTask(t1);

    t2 = new BlinkTask(PIN_GREEN_LED_1);
    t2->init(150);
    t3 = new BlinkTask(PIN_GREEN_LED_2);
    t3->init(150);

    Serial.println("Adding blink 3");
    sched.addTask(t3);
}

void loop()
{
    sched.schedule();
    static long start_time = millis();
    static bool state = true;
    if (state && millis() - start_time > 4000) {
        if (digitalRead(PIN_GREEN_LED_2) == HIGH) {
            Serial.println("Deleting t3");
            sched.removeTask(t3);
            state = false;
            Serial.println("Adding blink 2");
            sched.addTask(t2);
        }
    }
}