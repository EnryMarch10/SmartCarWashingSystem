#include "Led.h"
#include "Arduino.h"

Led::Led(const int pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    on = false;
}

bool Led::isOn(void)
{
    return on;
}

bool Led::isOff(void) {
    return !(this->isOn());
}

void Led::switchOn(void) {
    digitalWrite(pin, HIGH);
    on = true;
}

void Led::switchOff(void) {
    digitalWrite(pin, LOW);
    on = false;
};

void Led::toggle(void) {
    digitalWrite(pin, on ? LOW: HIGH);
    on = !on;
};
