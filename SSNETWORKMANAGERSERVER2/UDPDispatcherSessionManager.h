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

////////////////////////////////////////////////////////////////////
static int threadFunctionSession23(void* ctx){
    UDPDispatcherSession *uDPDSes = (UDPDispatcherSession *)ctx;
    uDPDSes->processInfoSession(23);
    return 0;
};


static int threadFunctionSession24(void* ctx){
    UDPDispatcherSession *uDPDSes = (UDPDispatcherSession *)ctx;
    uDPDSes->processInfoSession(24);
    return 0;
};


static int threadFunctionSession25(void* ctx){
    UDPDispatcherSession *uDPDSes = (UDPDispatcherSession *)ctx;
    uDPDSes->processInfoSession(25);
    return 0;
};


static int threadFunctionSession26(void* ctx){
    UDPDispatcherSession *uDPDSes = (UDPDispatcherSession *)ctx;
    uDPDSes->processInfoSession(26);
    return 0;
};

////////////////////////////////////////////////////////////////////

static int threadFunctionMem(void* ctx){
    UDPDispatcherSession *uDPDSes = (UDPDispatcherSession *)ctx;
    uDPDSes->processPredictionEngine();
    return 0;
};


class UDPDispatcherSessionManager{

public:

    UDPDispatcherSessionManager(LogEngine *_logger, NetworkClientUDP *_nCUDP){
        logger = _logger;
        nCUDP = _nCUDP;
        //nCUDPQueue = _nCUDPQueue;

        cQ1 = new Concurrent_queue_UDP();
        cQ2_1 = new Concurrent_queue_UDP();
        cQ2_2 = new Concurrent_queue_UDP();
        cQ2_3 = new Concurrent_queue_UDP();
        cQ2_4 = new Concurrent_queue_UDP();

        session_1 = new UDPDispatcherSession(logger, 1,1, nCUDP, cQ1, cQ2_1, cQ2_2, cQ2_3, cQ2_4); //mapa 1 session 1
        session_2 = new UDPDispatcherSession(logger, 1,2, nCUDP, cQ1, cQ2_1, cQ2_2, cQ2_3, cQ2_4); //mapa 1 session 2

        clearInputClientsToServer();
        activeSessions();
    }

    void processingInputMsgsFromClients();
    void processingOutputMsgToClients();
    void processInputConnections(EventMsg *ackTrama);             //--> QRY_CONECTION; CONECTION
    EventMsg *processQueryActiveSessions(EventMsg *qryListTrama); //--> QRY_SESSION_LIST; GET_SESSION_LIST
    void processActivateSession(EventMsg *ackSession);            //--> QRY_SESSION; GET_SESSION

    void deleteInputClient(EventMsg *quitSession);

    void activeSessions();

    void gatherInputTimes();
    void broadcastOutputTimes();

    ~UDPDispatcherSessionManager(){

        SDL_WaitThread( hebra_1, NULL );
        SDL_WaitThread( hebra_2, NULL );

        SDL_WaitThread( session_t123, NULL );
        SDL_WaitThread( session_t124, NULL );
        SDL_WaitThread( session_t223, NULL );
        SDL_WaitThread( session_t224, NULL );

        SDL_WaitThread( mem_1, NULL);
        SDL_WaitThread( mem_2, NULL);


        delete session_1;
        delete session_2;

    };

    void clearInputClientsToServer(){
        for(int i=0;i<TOT_CLIENTS;i++){
            EventMsg *msg = new EventMsg();

            UDPpacket *pack = SDLNet_AllocPacket(BUFFER_SIZE);
            pack->address.host = 0;
            pack->address.port = 0;
            msg->setPacketUDPTrama(pack);

            clientPackets.push_back(msg);
            freeSocket[i] = true;
        }
    }

private:

LogEngine *logger;
MemManager *mem;

NetworkClientUDP *nCUDP;
//NetworkClientUDP *nCUDPQueue;

Concurrent_queue_UDP *cQ1;
Concurrent_queue_UDP *cQ2_1;
Concurrent_queue_UDP *cQ2_2;
Concurrent_queue_UDP *cQ2_3;
Concurrent_queue_UDP *cQ2_4;

SDL_Thread *hebra_1;
SDL_Thread *hebra_2;

SDL_Thread *mem_1;
SDL_Thread *mem_2;

SDL_Thread *session_t123;
SDL_Thread *session_t124;
SDL_Thread *session_t125;
SDL_Thread *session_t126;

SDL_Thread *session_t223;
SDL_Thread *session_t224;
SDL_Thread *session_t225;
SDL_Thread *session_t226;

UDPDispatcherSession *session_1;
UDPDispatcherSession *session_2;

//EventMsg *clientPackets[TOT_CLIENTS];
std::vector<EventMsg *>clientPackets;
bool freeSocket[TOT_CLIENTS];

void processingConnection(){};
EventMsg *generatingACKPackets(int tramaSend,
                               int tramaGet,
                               int _OK,
                               packetDataType packet);


//friend void* execute_RunTaskUDPSession(void* );
friend int threadFunction(void* ctx);

//evaluating if client is connected; if yes, assign a session.
bool isClientConnected(EventMsg *msg, int typeTrama);


};

#endif // UDPDISPATCHERSESSIONMANAGER_H_INCLUDED


