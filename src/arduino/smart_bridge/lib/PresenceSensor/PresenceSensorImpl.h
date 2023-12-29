#ifndef __PRESENCE_SENSOR_IMPL__
#define __PRESENCE_SENSOR_IMPL__

#include "PresenceSensor.h"

class PresenceSensorImpl: public PresenceSensor {

public:
    PresenceSensorImpl(const int pin);
    bool detected(void);
    ~PresenceSensorImpl(void) {};

private:
    int pin;
    int detectedStatus;

};

#endif
