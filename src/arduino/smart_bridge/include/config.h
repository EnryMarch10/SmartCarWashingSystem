/**
 * General configuration file that defines run options and pins of the sensors in current circuit.
*/
#ifndef __CONFIG__
#define __CONFIG__

#include "utils.h"
#include "Logger.h"
#include "Scheduler.h"
#include "TasksFactory.h"

// PINS configuration

#define PIN_GREEN_LED_1 8
#define PIN_RED_LED 12
#define PIN_GREEN_LED_2 13

#define PIN_BUTTON 11

#define PIN_PIR 7

#define PIN_SONAR_TRIG 9
#define PIN_SONAR_ECHO 10

#define PIN_TMP36 A0

#define PIN_SERVO_MOTOR 6

#define LCD_ADDRESS 0x3F

// PERIODS configuration

// Other periods has to be multiples that this base period
#define BASE_PERIOD 100 // ms

#define FAST_BLINK_PERIOD 100 // ms
#define SLOW_BLINK_PERIOD 500 // ms

#define ONE_SECOND_PERIOD 1000 // ms

#define N1 2 // s
#define N2 3000 // ms
#define N3 10 // s
#define N4 N2 // ms
#define N5 5000 // ms

#define BUTTON_SAMPLING_PERIOD 150 // ms

#define MIN_DIST 0.10 // m
#define MAX_DIST 0.20 // m

#define MAX_T 40 // °C

/**
 * Initializes the sensors/actuators using the configured pins.
*/
void init_config(void);

// INTERRUPTS management

void enable_interrupt(unsigned char interruptDesignator, void (*handler)(void), unsigned char mode);
void disable_all_interrupts(void);

#endif