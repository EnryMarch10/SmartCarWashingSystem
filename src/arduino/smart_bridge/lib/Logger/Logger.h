#ifndef __LOGGER__
#define __LOGGER__

#include "utils.h"

class Logger {

public:
    void log(const String &msg);
    void debug(const String &msg);
    void flush(void);

};

extern Logger MyLogger;

#endif
