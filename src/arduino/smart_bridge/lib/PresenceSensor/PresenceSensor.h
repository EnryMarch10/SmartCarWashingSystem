#ifndef __PRESENCE_SENSOR__
#define __PRESENCE_SENSOR__

#include "run.h"

class PresenceSensor {

public:
    /**
     * Tells if movement detected.
    */
    virtual bool detected(void) = 0;
    virtual ~PresenceSensor() {};

};

#endif