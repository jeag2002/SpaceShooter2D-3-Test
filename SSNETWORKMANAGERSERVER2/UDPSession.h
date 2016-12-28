#ifndef UDPSESSION_H_INCLUDED
#define UDPSESSION_H_INCLUDED

#include "LogEngine.h"
#include "MemManager.h"
#include "EventMsg.h"
#include "Concurrent_queue_UDP.h"

/*
Gestion de un cliente de una sesion.
*/


class UDPSession{

public:

    UDPSession(int _playerID, LogEngine *_logger, MemManager *_mem, int _host, int _port){

        logger = _logger;
        mem = _mem;
        host = _host;
        port = _port;
        indexDataGet = 0;
        indexDataSend = 0;
        timeQOS = 0;
        playerID = _playerID;
        isReady = false;
        actStateFlag = true;

    };

    void setUDPSession(UDPSession *session){
        this->indexDataGet = session->getIndexDataGet();
        this->indexDataSend = session->getIndexDataSend();
        this->playerID = session->getPlayerId();
        this->host = session->getHost();
        this->port = session->getPort();
    }


    int getIndexDataGet(){return indexDataGet;}
    void setIndexDataGet(int _indexDataGet){indexDataGet = _indexDataGet;}

    int getIndexDataSend(){return indexDataSend;}
    void setIndexDataSend(int _indexDataSend){indexDataSend = _indexDataSend;}

    void setPlayerId(int _playerID){playerID = _playerID;}
    int getPlayerId(){return playerID;}

    void setHost(int _host){host = _host;}
    int getHost(){return host;}

    void setPort(int _port){port = _port;}
    int getPort(){return port;}

    void setTimeQOS(long _timeQOS){timeQOS = _timeQOS;}
    long getTimeQOS(){return timeQOS;}

    bool ready(){return isReady;}
    void setReady(bool _isReady){isReady = _isReady;}

    bool stateFlag(){return actStateFlag;}
    void setStateFlag(bool _actStateFlag){actStateFlag = _actStateFlag;}

    void Run(EventMsg *msg);

    ~UDPSession(){
        indexDataGet = 0;
        indexDataSend  = 0;
        playerID = 0;
        host = 0;
        port = 0;
        timeQOS = 0;
        isReady = false;
        actStateFlag = true;
    };



private:

int indexDataGet;
int indexDataSend;
int playerID;
int host;
int port;

long timeQOS;
bool isReady;
bool actStateFlag;

LogEngine *logger;
MemManager *mem;


};

#endif // UDPSESSION_H_INCLUDED
