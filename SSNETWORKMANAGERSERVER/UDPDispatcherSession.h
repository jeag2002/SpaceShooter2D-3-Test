#ifndef UDPDISPATCHERSESSION_H_INCLUDED
#define UDPDISPATCHERSESSION_H_INCLUDED

#include "UDPSession.h"
#include "NetworkClientUDP.h"
#include "PredictionEngine.h"
#include "Concurrent_queue_UDP.h"

#define MAX_CLIENT 4
#define SESSION_PORT 63000

/*
Gestion de una sesion
*/

class UDPDispatcherSession{

public:

    UDPDispatcherSession(LogEngine *_logger, int _mapId, int _sessionId, NetworkClientUDP *_nCUDP, Concurrent_queue_UDP *_cq_input, Concurrent_queue_UDP *_cq_output){
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
        cQOutput = _cq_output;

        nCUDP = _nCUDP;

        createEnvirontmentNew();

    };

     ~UDPDispatcherSession(){};

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

    //PROCESS MSGS
    void processSessions(EventMsg *msg);

    //SEND INFO DATA FROM MEMORY
    void sendInfoDataSession(int playerID, EventMsg *msg);
    EventMsg *sendWorldStateToClient(EventMsg *msg, int more, int indexServData, DynamicEntity *dEntity);

    void Run();

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
Concurrent_queue_UDP *cQOutput;

CollisionEntities *coll;
AnimationEntities *aEnt;
IAEntities *iAEnt;
PredictionEngine *pEngine;

void createEnvirontmentNew(); //--> crea un espacio de memoria x session.



};


#endif // UDPDISPATCHERSESSION_H_INCLUDED
