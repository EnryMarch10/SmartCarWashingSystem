#ifndef __TEMPERATURE_SENSOR_IMPL__
#define __TEMPERATURE_SENSOR_IMPL__

#include "TemperatureSensor.h"

class TemperatureSensorTMP32: public TemperatureSensor {

public:
    TemperatureSensorTMP32(const int pin);
    float getTemperature(void);
    ~TemperatureSensorTMP32() {};

private:
    int pin;

};

#endif