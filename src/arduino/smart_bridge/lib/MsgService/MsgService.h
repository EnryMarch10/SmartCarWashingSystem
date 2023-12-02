#ifndef __MSGSERVICE__
#define __MSGSERVICE__

class Msg {
    String content;

public:
    Msg(const String content)
    {
        this->content = content;
    }
    
    String getContent(void)
    {
        return content;
    }

};

class Pattern {

public:
    virtual boolean match(const Msg &m) = 0;

};

class MsgServiceClass {

public:
    Msg* currentMsg;
    bool msgAvailable;

    void init();
    bool isMsgAvailable();
    bool isMsgAvailable(Pattern &pattern);
    Msg *receiveMsg();
    Msg *receiveMsg(Pattern &pattern);
    void sendMsg(const String &msg);

};

extern MsgServiceClass MsgService;

#endif
