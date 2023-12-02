#include "Logger.h"
#include "MsgService.h"
#include "utils.h"

void LoggerService::log(const String& msg)
{
    MsgService.sendMsg("log: " + msg);
}

void LoggerService::debug(const String& msg)
{
#ifdef __DEBUG__
    MsgService.sendMsg("debug: " + msg);
#endif
}
