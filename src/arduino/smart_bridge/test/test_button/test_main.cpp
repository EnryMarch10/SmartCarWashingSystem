#include <Arduino.h>
#include "config.h"
#include "ButtonImpl.h"

#include <unity.h>
#include <string.h>

#define N 30

ButtonImpl *btn;
char message[100];

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_empty(void) {
    TEST_ASSERT_TRUE(true);
}

void setup()
{
    UNITY_BEGIN();
    btn = new ButtonImpl(PIN_BUTTON);
}

void loop()
{
    static int i = 0;
    i++;
    delay(300);
    const bool state = btn->isPressed();
    strcpy(message, "Button is ");
    strcat(message, state ? "": "not ");
    strcat(message, "pressed");
    TEST_MESSAGE(message);
    RUN_TEST(test_empty);
    if (i >= N) {
        delete btn;
        UNITY_END();
    }
}