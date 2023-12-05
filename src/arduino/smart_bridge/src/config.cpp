#include "config.h"

#include "MsgService.h"

#include "Led.h"
#include "LcdI2C.h"
#include "SonarImpl.h"
#include "ServoMotorImpl.h"
#include "ButtonImpl.h"
#include "TemperatureSensorTMP32.h"

#include <Arduino.h>
#include <EnableInterrupt.h>

Led greenLed1 = Led(PIN_GREEN_LED_1);
Led redLed = Led(PIN_RED_LED);
Led greenLed2 = Led(PIN_GREEN_LED_2);
LcdI2C lcd = LcdI2C(LCD_ADDRESS);
SonarImpl sonar = SonarImpl(PIN_SONAR_TRIG, PIN_SONAR_ECHO);
ServoMotorImpl servoMotor = ServoMotorImpl(PIN_SERVO_MOTOR);
ButtonImpl button = ButtonImpl(PIN_BUTTON);
TemperatureSensorTMP32 TSensor = TemperatureSensorTMP32(PIN_TMP36);

static Queue<unsigned char> interrupts = Queue<unsigned char>();

void init_config(void)
{
    MyMsgService.init();
    lcd.init();
}

void enable_interrupt(unsigned char interruptDesignator, void (*handler)(void), unsigned char mode)
{
    enableInterrupt(interruptDesignator, handler, mode);
    interrupts.enqueue(interruptDesignator);
}

void disable_all_interrupts(void)
{
    while (!interrupts.isEmpty()) {
        uint8_t interruptDesignator = interrupts.dequeue();
        disableInterrupt(interruptDesignator);
    }
}
