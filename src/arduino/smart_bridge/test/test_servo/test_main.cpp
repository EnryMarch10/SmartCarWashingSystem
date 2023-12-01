#include <Arduino.h>
#include <stdio.h>
#include "config.h"
#include "ServoMotorImpl.h"

#include <unity.h>

#define N 10

ServoMotor *pMotor;
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
    pMotor = new ServoMotorImpl(PIN_SERVO_MOTOR);
}

void loop()
{
    static int i = 0;
    i++;
    pMotor->on();
    int j = pMotor->readPosition();
    for (; j < 180; j++) {
        pMotor->setPosition(j);
        const int readPos = pMotor->readPosition();
        sprintf(buf, "%d", readPos);
        TEST_MESSAGE(buf);
        delay(10);
    }
    for (; j > 0; j--) {
        pMotor->setPosition(j);
        const int readPos = pMotor->readPosition();
        sprintf(buf, "%d", readPos);
        TEST_MESSAGE(buf);
        delay(10);
    }
    pMotor->off();
    delay(1000);
    if (i % 100 == 0) {
        RUN_TEST(empty);
    }
    if (i >= N) {
        delete pMotor;
        UNITY_END();
    }
}