#include <Arduino.h>
#include "config.h"
#include "PresenceSensorImpl.h"

#include <unity.h>

#define N 400

PresenceSensor *pir;
bool state;

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void empty(void)
{
    TEST_ASSERT_TRUE(true);
}

void setup()
{
    UNITY_BEGIN();
    pir = new PresenceSensorImpl(PIN_PIR);
}

void loop()
{
    static int i = 0;
    i++;
    delay(100);
    const bool precState = state;
    state = pir->detected();
    if (state != precState) {
        TEST_MESSAGE(state ? "OK" : "NO");
    }
    RUN_TEST(empty);
    if (i >= N) {
        delete pir;
        UNITY_END();
    }
}