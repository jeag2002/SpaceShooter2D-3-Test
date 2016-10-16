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

    UDPSession(int _playerID, LogEngine *_logger, MemManager *_mem, UDPpacket *_packet){

        logger = _logger;
        mem = _mem;
        packet = _packet;

        indexDataGet = 0;
        indexDataSend = 0;

        playerID = _playerID;

    };

    void setUDPSession(UDPSession *session){
        this->indexDataGet = session->getIndexDataGet();
        this->indexDataSend = session->getIndexDataSend();
        this->playerID = session->getPlayerId();
    }


    UDPpacket *getPacket(){return packet;}
    void setPacket(UDPpacket *_packet){packet = _packet;}

    int getIndexDataGet(){return indexDataGet;}
    void setIndexDataGet(int _indexDataGet){indexDataGet = _indexDataGet;}

    int getIndexDataSend(){return indexDataSend;}
    void setIndexDataSend(int _indexDataSend){indexDataSend = _indexDataSend;}

    void setPlayerId(int _playerID){playerID = _playerID;}
    int getPlayerId(){return playerID;}

    void Run(EventMsg *msg);

    ~UDPSession(){};



private:

int indexDataGet;
int indexDataSend;
int playerID;

LogEngine *logger;
MemManager *mem;
UDPpacket *packet;

};

#endif // UDPSESSION_H_INCLUDED
