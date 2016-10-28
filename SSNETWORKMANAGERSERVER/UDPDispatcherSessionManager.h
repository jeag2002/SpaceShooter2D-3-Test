#ifndef UDPDISPATCHERSESSIONMANAGER_H_INCLUDED
#define UDPDISPATCHERSESSIONMANAGER_H_INCLUDED

#include "Stdafx.h"
#include "UDPDispatcherSession.h"
#define TOT_CLIENTS 8


/*
static void* execute_RunTaskUDPSession(void* ctx){
    UDPDispatcherSession *uDPDSes = (UDPDispatcherSession *)ctx;
    uDPDSes->Run();
};
*/

static int threadFunction(void* ctx){
    UDPDispatcherSession *uDPDSes = (UDPDispatcherSession *)ctx;
    uDPDSes->Run();
    return 0;
};


class UDPDispatcherSessionManager{

public:

    UDPDispatcherSessionManager(LogEngine *_logger, NetworkClientUDP *_nCUDP, Concurrent_queue_UDP *cQ11, Concurrent_queue_UDP *cQ22){
        logger = _logger;
        nCUDP = _nCUDP;


        cQ1 = new Concurrent_queue_UDP();
        cQ2 = new Concurrent_queue_UDP();


        session_1 = new UDPDispatcherSession(logger, 1,1, nCUDP, cQ1, cQ2); //mapa 1 session 1
        //session_2 = new UDPDispatcherSession(logger, 1,2, nCUDP, cQ1, cQ2); //mapa 1 session 1

        clearInputClientsToServer();
        activeSessions();
    }

    void processingInputMsgsFromClients();
    void processInputConnections(EventMsg *ackTrama);             //--> QRY_CONECTION; CONECTION
    EventMsg *processQueryActiveSessions(EventMsg *qryListTrama); //--> QRY_SESSION_LIST; GET_SESSION_LIST
    EventMsg *processActivateSession(EventMsg *ackSession);       //--> QRY_SESSION; GET_SESSION
    void processInputMsgs(){};                                    //--> OTHER INFORMATIONS.

    void activeSessions();

    ~UDPDispatcherSessionManager(){
        SDL_WaitThread( hebra_1, NULL );
        //SDL_WaitThread( hebra_2, NULL );
        delete session_1;
        //delete session_2;

    };

    void clearInputClientsToServer(){
        for(int i=0;i<TOT_CLIENTS;i++){
            clientPackets[i] = new EventMsg();
            UDPpacket *pack = SDLNet_AllocPacket(BUFFER_SIZE);
            pack->address.host = 0;
            pack->address.port = 0;
            clientPackets[i]->setPacketUPD(pack);
            freeSocket[i] = true;
        }
    }

private:

LogEngine *logger;
MemManager *mem;
NetworkClientUDP *nCUDP;
Concurrent_queue_UDP *cQ1;
Concurrent_queue_UDP *cQ2;

SDL_Thread *hebra_1;
//SDL_Thread *hebra_2;

UDPDispatcherSession *session_1;
//UDPDispatcherSession *session_2;

EventMsg *clientPackets[TOT_CLIENTS];
bool freeSocket[TOT_CLIENTS];


void processingConnection(){};
EventMsg *generatingACKPackets(int tramaSend,
                               int tramaGet,
                               int _OK,
                               UDPpacket *packet);


//friend void* execute_RunTaskUDPSession(void* );
friend int threadFunction(void* ctx);


};

#endif // UDPDISPATCHERSESSIONMANAGER_H_INCLUDED


