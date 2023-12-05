#include "TemperatureSensorTMP32.h"

#define VOLTAGE 5.0

TemperatureSensorTMP32::TemperatureSensorTMP32(const int pin)
{
    this->pin = pin;
}

float TemperatureSensorTMP32::getTemperature(void)
{
    return (((analogRead(pin) * VOLTAGE / 1024.0) - 0.5) * 100);
}