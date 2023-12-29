#include "PresenceSensorImpl.h"

PresenceSensorImpl::PresenceSensorImpl(const int pin)
{
    this->pin = pin;
    pinMode(pin, INPUT);
    detectedStatus = LOW;
}

bool PresenceSensorImpl::detected(void)
{
    return digitalRead(pin) == HIGH;
}
