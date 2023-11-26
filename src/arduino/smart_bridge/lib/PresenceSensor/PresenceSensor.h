#ifndef __PRESENCE_SENSOR__
#define __PRESENCE_SENSOR__

class PresenceSensor {

public:
    virtual bool detected(void) = 0;
    virtual ~PresenceSensor() {};

};

#endif