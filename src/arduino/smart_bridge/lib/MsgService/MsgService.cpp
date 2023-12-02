#include <Arduino.h>
#include "MsgService.h"
#include "utils.h"

#define BUFFER_SIZE 256

static String content;

MsgServiceClass MsgService;

bool MsgServiceClass::isMsgAvailable(void)
{
    return msgAvailable;
}

Msg* MsgServiceClass::receiveMsg(void)
{
    if (msgAvailable){
        Msg* msg = currentMsg;
        msgAvailable = false;
        currentMsg = NULL;
        content = "";
        return msg;  
    } else {
        return NULL; 
    }
}

void MsgServiceClass::init(void)
{
    Serial.begin(BAUD_RATE);
    content.reserve(BUFFER_SIZE);
    content = "";
    currentMsg = NULL;
    msgAvailable = false;  
}

void MsgServiceClass::sendMsg(const String &msg)
{
    Serial.println(msg);
}

void serialEvent(void)
{
    while (Serial.available()) {
        char c = (char) Serial.read();
        if (c == '\n') {
            MsgService.currentMsg = new Msg(content);
            MsgService.msgAvailable = true;     
        } else {
            content += c; 
        }
    }
}

bool MsgServiceClass::isMsgAvailable(Pattern &pattern)
{
    return (msgAvailable && pattern.match(*currentMsg));
}

Msg *MsgServiceClass::receiveMsg(Pattern &pattern)
{
    if (msgAvailable && pattern.match(*currentMsg)) {
        Msg *msg = currentMsg;
        msgAvailable = false;
        currentMsg = NULL;
        content = "";
        return msg;
    } else {
        return NULL;
    }
}
