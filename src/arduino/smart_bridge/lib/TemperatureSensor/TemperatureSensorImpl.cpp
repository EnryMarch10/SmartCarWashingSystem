#include <Arduino.h>
#include "TemperatureSensorImpl.h"

#define VOLTAGE 5.0

TemperatureSensorImpl::TemperatureSensorImpl(const int pin) {
    this->pin = pin;
    // unnecessary for analog pins
    // pinMode(pin, INPUT);
}

float TemperatureSensorImpl::getTemperature(void) {
    return (((analogRead(pin) * VOLTAGE / 1024.0) - 0.5) * 100);
}