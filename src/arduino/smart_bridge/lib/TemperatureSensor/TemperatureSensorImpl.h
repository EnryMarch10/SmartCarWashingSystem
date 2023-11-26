#ifndef __TEMPERATURE_SENSOR_IMPL__
#define __TEMPERATURE_SENSOR_IMPL__

#include "TemperatureSensor.h"

class TemperatureSensorImpl: public TemperatureSensor {

public:
    TemperatureSensorImpl(const int pin);
    float getTemperature(void);
    ~TemperatureSensorImpl() {};

private:
    int pin;

};

#endif