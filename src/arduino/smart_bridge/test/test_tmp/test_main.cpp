#include <Arduino.h>
#include "config.h"
#include "TemperatureSensorImpl.h"

#include <unity.h>

#define N 20

TemperatureSensor *temperature;
char buf[10];

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void empty(void) {
    TEST_ASSERT_TRUE(true);
}

void setup()
{
    UNITY_BEGIN();
    temperature = new TemperatureSensorImpl(PIN_TMP36);
}

void loop()
{
    static int i = 0;
    i++;
    delay(1000);
    sprintf(buf, "%d", (int) temperature->getTemperature());
    strcat(buf, " C");
    TEST_MESSAGE(buf);
    RUN_TEST(empty);
    if (i >= N) {
        delete temperature;
        UNITY_END();
    }
}