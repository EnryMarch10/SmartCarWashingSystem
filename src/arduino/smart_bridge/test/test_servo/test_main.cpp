#include <Arduino.h>
#include <stdio.h>
#include "config.h"
#include "ServoMotorImpl.h"

#include <unity.h>

#define N 10

ServoMotor *pMotor;
int pos = 0;   
int delta = 1;
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
    for (int i = 0; i <= 180; i++) {
        sprintf(buf, "%d", pos);
        TEST_MESSAGE(buf);
        pMotor->setPosition(pos);         
        // delay(2);            
        pos += delta;
    }
    pMotor->off();
    pos -= delta;
    delta = -delta;
    delay(1000);
    if (i % 100 == 0) {
        RUN_TEST(empty);
    }
    if (i >= N) {
        delete pMotor;
        UNITY_END();
    }
}