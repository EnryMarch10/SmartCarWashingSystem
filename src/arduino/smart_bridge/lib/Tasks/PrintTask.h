#ifndef __PRINTTASK__
#define __PRINTTASK__

#include "Task.h"

class PrintTask: public Task {

public:
    PrintTask(void);  
    void init(const int period);  
    void tick(void);

private:
    int count;

};

#endif
