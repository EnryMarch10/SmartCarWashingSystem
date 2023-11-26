#ifndef __SONAR_IMPL__
#define __SONAR_IMPL__

#include "Sonar.h"

class SonarImpl: public Sonar {

public:
    SonarImpl(const int trigPin, const int echoPin);
    SonarImpl(const int trigPin, const int echoPin, const float temperature);
    float getDistance(void);
    ~SonarImpl() {};

private:
    void ConfigPins(const int trigPin, const int echoPin);
    int trigPin;
    int echoPin;
    float temperature;
    float vs;

};

#endif