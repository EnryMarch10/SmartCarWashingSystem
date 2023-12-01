#ifndef __TEMPERATURE_SENSOR__
#define __TEMPERATURE_SENSOR__

#include "run.h"

class TemperatureSensor {

public:
    /**
     * Retrieves temperature in degrees Celsius.
    */
    virtual float getTemperature(void) = 0;
    virtual ~TemperatureSensor() {};

};

#endif