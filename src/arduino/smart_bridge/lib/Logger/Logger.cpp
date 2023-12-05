#include "Logger.h"
#include "utils.h"
#include "MsgService.h"

Logger MyLogger;

void Logger::log(const String &msg)
{
    MsgService.sendMsg("log: " + msg);
}

void Logger::debug(const String &msg)
{
#ifdef __DEBUG__
    MsgService.sendMsg("debug: " + msg);
#endif
}

void Logger::flush(void)
{
    MsgService.flush();
}
