#include <Arduino.h>
#include "PresenceSensorImpl.h"

PresenceSensorImpl::PresenceSensorImpl(const int pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
    detectedStatus = LOW;
}

// TODO: review this kind of implementation, could not be optiomal
bool PresenceSensorImpl::detected(void) {
    return digitalRead(pin) == HIGH;
}