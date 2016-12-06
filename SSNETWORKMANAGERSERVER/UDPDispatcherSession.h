#ifndef UDPDISPATCHERSESSION_H_INCLUDED
#define UDPDISPATCHERSESSION_H_INCLUDED

#include "UDPSession.h"
#include "NetworkClientUDP.h"
#include "PredictionEngine.h"
#include "Concurrent_queue_UDP.h"

#define MAX_CLIENT 4
#define MAX_SIZE_QUEUE 20
#define SESSION_PORT 63000

/*
Gestion de una sesion
*/

static int threadFunctionMem(void* ctx){
    PredictionEngine *pEngine = (PredictionEngine *)ctx;
    //uDPDSes->Run();
    pEngine->processPrediction();
    return 0;
};


class UDPDispatcherSession{

public:

    UDPDispatcherSession(LogEngine *_logger, int _mapId, int _sessionId, NetworkClientUDP *_nCUDP, Concurrent_queue_UDP *_cq_input,
                         Concurrent_queue_UDP *_cq_output_1,
                         Concurrent_queue_UDP *_cq_output_2,
                         Concurrent_queue_UDP *_cq_output_3,
                         Concurrent_queue_UDP *_cq_output_4
                         ){
        logger = _logger;

        mem = new MemManager();

        coll = new CollisionEntities(mem,logger);
        aEnt = new AnimationEntities(mem,logger);
        iAEnt = new IAEntities(mem,logger);
        pEngine = new PredictionEngine(logger,mem,coll,aEnt,iAEnt);

        mapId = _mapId;
        sessionId = _sessionId;

        maxClients = MAX_CLIENT;
        numClients = 0;

        cQInput = _cq_input;
        cQOutput_1 = _cq_output_1;
        cQOutput_2 = _cq_output_2;
        cQOutput_3 = _cq_output_3;
        cQOutput_4 = _cq_output_4;

        nCUDP = _nCUDP;

        createEnvirontmentNew();

        hebra_Mem = SDL_CreateThread(threadFunctionMem,"Session_Mem",pEngine);
        logger->info("[UDPDispatcherSessionManager::activeSession map[%d] session[%d]] --> THREAD FOR MEM MANAGEMENT SESSION CREATED", mapId, sessionId);

    };

     ~UDPDispatcherSession(){
        SDL_WaitThread( hebra_Mem, NULL );
        delete hebra_Mem;
     };

    int getMapId(){return mapId;}
    void setMapId(int _mapId){mapId = _mapId;}

    int getSessionId(){return sessionId;}
    void setSessionId(int _sessionId){sessionId = _sessionId;}

    int getMaxClients(){return maxClients;}

    int getNumClients(){return numClients;}
    void setNumClients(int _numClients){numClients = _numClients;}

    //processInputMsgs:
    void processInputMsg();

    //ACK MSGS
    ///////////////////////////////////////////////////
    EventMsg *setClientForSession(EventMsg *msg);
    DynamicEntity *getRemotePlayer();
    EventMsg *sendAckMsg(DynamicEntity *dEntity, EventMsg *msg, bool result);
    ///////////////////////////////////////////////////

    //SEND MESSAGE FROM SERVER TO CLIENT
    void sendNotificationServerToDiffClients(const char *msg, int userDest);
    EventMsg *sendEventMsg(const char *iMsg, UDPSession *session);

    //PROCESS MSGS
    void processSessions(EventMsg *msg);

    //SEND INFO DATA FROM MEMORY
    void sendInfoDataSession(int playerID, EventMsg *msg);
    EventMsg *sendWorldStateToClient(EventMsg *msg, int more, int indexServData, DynamicEntity *dEntity);

    void Run();

    void sendMsgToOutput(EventMsg *msg);

private:

int mapId;
int sessionId;

int maxClients;
int numClients;

std::vector<UDPSession *> clientes;

LogEngine *logger;
MemManager *mem;
NetworkClientUDP *nCUDP;

Concurrent_queue_UDP *cQInput;
Concurrent_queue_UDP *cQOutput_1;
Concurrent_queue_UDP *cQOutput_2;
Concurrent_queue_UDP *cQOutput_3;
Concurrent_queue_UDP *cQOutput_4;

CollisionEntities *coll;
AnimationEntities *aEnt;
IAEntities *iAEnt;
PredictionEngine *pEngine;

SDL_Thread *hebra_Mem;

void createEnvirontmentNew(); //--> crea un espacio de memoria x session.



};


#endif // UDPDISPATCHERSESSION_H_INCLUDED
