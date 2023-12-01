#include <Arduino.h>
#include "config.h"
#include "SonarImpl.h"

#include <unity.h>

#define N 50

Sonar *sonar;
char buf[10];
char tmp_buf[5];

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
    sonar = new SonarImpl(PIN_SONAR_TRIG, PIN_SONAR_ECHO);
}

void loop()
{
    static int i = 0;
    i++;
    delay(300);
    const float value = sonar->getDistance();
    const int before_comma = (int) value;
    const int after_comma = (int) ((value - before_comma) * 100);
    sprintf(buf, "%d", before_comma);
    strcat(buf, ".");
    sprintf(tmp_buf, "%d", after_comma);
    if (strlen(tmp_buf) == sizeof(char)) {
        strcat(buf, "0");
    }
    strcat(buf, tmp_buf);
    strcat(buf, " m");
    TEST_MESSAGE(buf);
    RUN_TEST(empty);
    if (i >= N) {
        delete sonar;
        UNITY_END();
    }
}