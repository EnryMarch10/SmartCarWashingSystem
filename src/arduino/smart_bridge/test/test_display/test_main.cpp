#include <Arduino.h>
#include "config.h"

#include <LiquidCrystal_I2C.h>

#include <unity.h>

#define WAIT 2000

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(LCD_ADDRESS, 16, 2);

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

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0); // Set the cursor on the third column and first row.
    lcd.print("Hello World!");
    delay(WAIT);
    lcd.clear();

    RUN_TEST(empty);
    UNITY_END();
}

void loop()
{

}