#ifndef QUEUEMANAGER_H_INCLUDED
#define QUEUEMANAGER_H_INCLUDED

#include "EventMsg.h"
#include "LogEngine.h"

#include <queue>

class QueueManager{

public:

QueueManager(LogEngine *_log){
    log = _log;
}

~QueueManager(){
}

/////////////////////////////////////////////////////
//--> GET MSG QUEUE MANAGER

EventMsg *getMessageOutput(){
     if (!messageOutput.empty()){
        EventMsg *msg = messageOutput.front();
        return msg;
    }else{
        EventMsg *data = new EventMsg();
        return data;
    }
};

//--> IS EMPTY QUEUE MANAGER
bool isEmptyMessageOutput(){
    return messageOutput.empty();
};


void popMessageOutputQueue(){
    if (!messageOutput.empty()){
        messageOutput.pop();
    }
};

//--> SEND MSG QUEUE MANAGER
void setMessageOutput(EventMsg *msg){
    messageOutput.push(msg);
};

////////////////////////////////////////////////////////

private:
    LogEngine *log;
    std::queue<EventMsg *> messageOutput;
};

#endif // QUEUEMANAGER_H_INCLUDED
