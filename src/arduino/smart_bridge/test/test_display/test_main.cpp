#include <Arduino.h>
#include "config.h"
#include "LcdI2C.h"

#include <unity.h>

#define WAIT 4000

Display *pLcd = new LcdI2C(LCD_ADDRESS);

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

    pLcd->init();
    pLcd->on();
    pLcd->write("Hello World!");
    delay(WAIT);
    pLcd->off();
    delete pLcd;

    RUN_TEST(empty);
    UNITY_END();
}

void loop()
{

}