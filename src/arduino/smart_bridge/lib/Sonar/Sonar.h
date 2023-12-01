#ifndef __SONAR__
#define __SONAR__

class Sonar {

public:
    /**
     * Retrieves distance in meters.
    */
    virtual float getDistance(void) = 0;
    virtual ~Sonar() {};

};

#endif