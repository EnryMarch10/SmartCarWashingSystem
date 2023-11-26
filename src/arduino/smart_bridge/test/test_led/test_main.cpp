#include <Arduino.h>
#include "config.h"
#include "Led.h"

#include <unity.h>

#define N 10

Light *led;
int state = LOW;

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void led_state(void) {
    TEST_ASSERT_EQUAL(state, digitalRead(PIN_RED_LED));
}

void setup()
{
    UNITY_BEGIN();
    led = new Led(PIN_RED_LED);
}

void loop()
{
    static int i = 0;
    i++;
    delay(500);
    led->toggle();
    state = !state;
    RUN_TEST(led_state);
    if (i >= N) {
        delete led;
        UNITY_END();
    }
}