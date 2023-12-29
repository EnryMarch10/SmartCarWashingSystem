#ifndef __TEMPERATURE_SENSOR__
#define __TEMPERATURE_SENSOR__

#include "utils.h"

class TemperatureSensor {

public:
    /**
     * Retrieves temperature in degrees Celsius.
    */
    virtual float getTemperature(void) = 0;
    virtual ~TemperatureSensor(void) { }

};

#endif
