#ifndef __PRESENCE_SENSOR__
#define __PRESENCE_SENSOR__

#include "utils.h"

class PresenceSensor {

public:
    /**
     * Tells if movement detected.
    */
    virtual bool detected(void) = 0;
    virtual ~PresenceSensor(void) {};

};

#endif
