#ifndef __SONAR__
#define __SONAR__

#include "utils.h"

class Sonar {

public:
    /**
     * Retrieves distance in meters or DETECTION_ERROR if something has gone wrong.
    */
    virtual float getDistance(void) = 0;
    virtual ~Sonar() {};

};

#endif