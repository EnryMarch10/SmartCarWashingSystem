#include <Arduino.h>
#include "SonarImpl.h"

#define DEFAULT_TEMP 20 // ° C

static void _init_vs(float *vs, float *tempOld, float tempNew) {
    *tempOld = tempNew;
    *vs = 331.45 + 0.62 * (*tempOld);
}

void SonarImpl::ConfigPins(const int trigPin, const int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

SonarImpl::SonarImpl(const int trigPin, const int echoPin) {
    _init_vs(&vs, &(this->temperature), DEFAULT_TEMP);
    ConfigPins(trigPin, echoPin);
}

SonarImpl::SonarImpl(const int trigPin, const int echoPin, const float temperature) {
    _init_vs(&vs, &(this->temperature), temperature);
    ConfigPins(trigPin, echoPin);
}

float SonarImpl::getDistance(void) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);

    /* Receiving the echo */
    float tUS = pulseIn(echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t * vs;
    return d;
}