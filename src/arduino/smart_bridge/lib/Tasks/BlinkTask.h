#ifndef __BLINKTASK__
#define __BLINKTASK__

#include "Task.h"
#include "Led.h"

class BlinkTask: public Task {

public:
    BlinkTask(const int pin);  
    void init(const int period);  
    void tick(void);

private:
    int pin;
    Light *led;
    enum { ON, OFF } state;

};

#endif

