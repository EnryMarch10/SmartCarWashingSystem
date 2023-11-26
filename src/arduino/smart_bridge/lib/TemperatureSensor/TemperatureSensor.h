#ifndef __TEMPERATURE_SENSOR__
#define __TEMPERATURE_SENSOR__

class TemperatureSensor {

public:
    virtual float getTemperature(void) = 0;
    virtual ~TemperatureSensor() {};

};

#endif