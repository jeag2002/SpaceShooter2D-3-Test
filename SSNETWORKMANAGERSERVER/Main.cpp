#include "Stdafx.h"
#include "LogEngine.h"
#include "NetworkClientUDP.h"
#include "UDPDispatcherSessionManager.h"

LogEngine *logger;
NetworkClientUDP *nClientUDP;
UDPDispatcherSessionManager *uDSM;

UDPDispatcherSession *session_1;
UDPDispatcherSession *session_2;

Concurrent_queue_UDP *cQ1;
Concurrent_queue_UDP *cQ2;

pthread_t hebra_1;
pthread_t hebra_2;
pthread_t hebra_3;

int maxPlayers;
int numPlayers;

void createEnvirontmentNew();
void destroyAllNew();


int main (int argc, char *argv[])
{
   logger = new LogEngine();
   logger->deleteLogFile();
   logger->startUp(1,0);
   logger->printLogFlag();
   logger->info("================ [SSNETWORKMANAGER-SERVER - INI] ================");

   try{
       createEnvirontmentNew();

       while(true){
        uDSM->processingInputMsgsFromClients();
        uDSM->processingOutputMsgToClients();
       }

   }catch(...){
      logger->info("exception caught!");
   }

   destroyAllNew();
   logger->info("================ [SSNETWORKMANAGER-SERVER - END] ================");
   return 0;
}

//UTIL UDPConn
void createEnvirontmentNew(){

    nClientUDP = new NetworkClientUDP(logger);
    nClientUDP->initCommunicationUDP();

    cQ1 = new Concurrent_queue_UDP();
    cQ2 = new Concurrent_queue_UDP();

    uDSM = new UDPDispatcherSessionManager(logger, nClientUDP, cQ1, cQ2);
}


void destroyAllNew(){
   delete uDSM;
   delete nClientUDP;
   delete logger;

};

//UTIL FOR TCPConn.
/*
void processServerLogicNew();

EventMsg *dataUDP = nClientUDP->evaluatingIncomingPackets();
processServerLogicNew();

pthread_t hebra_1;
pthread_t hebra_2;
static void* execute_RunTaskTCPSession11(void* ctx);

void createEnvirontmentNew(){

    mem = new MemManager();
    cQ = new Concurrent_queue();

    nClient = new NetworkClient(logger);
    nClientUDP = new NetworkClientUDP(logger);

    nClock = new ClockEngine(100);


    coll = new CollisionEntities(mem,logger);
    aEnt = new AnimationEntities(mem,logger);
    iAEnt = new IAEntities(mem,logger);

    pEngine = new PredictionEngine(logger,mem,coll,aEnt,iAEnt); //prediction Engine.
    tcpSession = new TCPSession(logger,mem,nClient,cQ);

    //maxPlayers = 4;
    //numPlayers = 0;

    //enemigos
    ///////////////////////////////
    DynamicEntity *enemy_1_1 = new DynamicEntity(logger); enemy_1_1->setActLevel(1); enemy_1_1->setIDDE(4); enemy_1_1->setEnabled(true); enemy_1_1->setTypeId(TYPE_ACTIVE_ELEMENT);
    DynamicEntity *enemy_2_1 = new DynamicEntity(logger); enemy_2_1->setActLevel(1); enemy_2_1->setIDDE(5); enemy_2_1->setEnabled(true); enemy_2_1->setTypeId(TYPE_ACTIVE_ELEMENT);
    DynamicEntity *enemy_3_1 = new DynamicEntity(logger); enemy_3_1->setActLevel(1); enemy_3_1->setIDDE(6); enemy_3_1->setEnabled(true); enemy_3_1->setTypeId(TYPE_ACTIVE_ELEMENT);

    mem->addEnemiesMap_lvl_1(4,enemy_1_1);
    mem->addEnemiesMap_lvl_1(5,enemy_2_1);
    mem->addEnemiesMap_lvl_1(6,enemy_3_1);

    DynamicEntity *enemy_1_2 = new DynamicEntity(logger); enemy_1_2->setActLevel(2); enemy_1_2->setIDDE(7); enemy_1_2->setEnabled(true); enemy_1_2->setTypeId(TYPE_ACTIVE_ELEMENT);
    DynamicEntity *enemy_2_2 = new DynamicEntity(logger); enemy_2_2->setActLevel(2); enemy_2_2->setIDDE(8); enemy_2_2->setEnabled(true); enemy_2_2->setTypeId(TYPE_ACTIVE_ELEMENT);
    DynamicEntity *enemy_3_2 = new DynamicEntity(logger); enemy_3_2->setActLevel(2); enemy_3_2->setIDDE(9); enemy_3_2->setEnabled(true); enemy_3_2->setTypeId(TYPE_ACTIVE_ELEMENT);

    mem->addEnemiesMap_lvl_2(7,enemy_1_2);
    mem->addEnemiesMap_lvl_2(8,enemy_2_2);
    mem->addEnemiesMap_lvl_2(9,enemy_3_2);

    DynamicEntity *enemy_1_3 = new DynamicEntity(logger); enemy_1_3->setActLevel(3); enemy_1_3->setIDDE(10); enemy_1_3->setEnabled(true); enemy_1_3->setTypeId(TYPE_ACTIVE_ELEMENT);
    DynamicEntity *enemy_2_3 = new DynamicEntity(logger); enemy_2_3->setActLevel(3); enemy_2_3->setIDDE(11); enemy_2_3->setEnabled(true); enemy_2_3->setTypeId(TYPE_ACTIVE_ELEMENT);
    DynamicEntity *enemy_3_3 = new DynamicEntity(logger); enemy_3_3->setActLevel(3); enemy_3_3->setIDDE(12); enemy_3_3->setEnabled(true); enemy_3_3->setTypeId(TYPE_ACTIVE_ELEMENT);

    mem->addEnemiesMap_lvl_3(10,enemy_1_3);
    mem->addEnemiesMap_lvl_3(11,enemy_2_3);
    mem->addEnemiesMap_lvl_3(12,enemy_3_3);
    ///////////////////////////////

    //elementos dinamicos
    ///////////////////////////////
    DynamicEntity *DynElem_1_1 = new DynamicEntity(logger); DynElem_1_1->setActLevel(1); DynElem_1_1->setIDDE(14); DynElem_1_1->setEnabled(true); DynElem_1_1->setTypeId(TYPE_ACTIVEOTHER_ELEMENT);
    DynamicEntity *DynElem_2_1 = new DynamicEntity(logger); DynElem_2_1->setActLevel(1); DynElem_2_1->setIDDE(15); DynElem_2_1->setEnabled(true); DynElem_2_1->setTypeId(TYPE_ACTIVEOTHER_ELEMENT);
    DynamicEntity *DynElem_3_1 = new DynamicEntity(logger); DynElem_3_1->setActLevel(1); DynElem_3_1->setIDDE(16); DynElem_3_1->setEnabled(true); DynElem_3_1->setTypeId(TYPE_ACTIVEOTHER_ELEMENT);

    mem->addDynElemMap_lvl_1(14,DynElem_1_1);
    mem->addDynElemMap_lvl_1(15,DynElem_2_1);
    mem->addDynElemMap_lvl_1(16,DynElem_3_1);

    DynamicEntity *DynElem_1_2 = new DynamicEntity(logger); DynElem_1_2->setActLevel(2); DynElem_1_2->setIDDE(17); DynElem_1_2->setEnabled(true); DynElem_1_2->setTypeId(TYPE_ACTIVEOTHER_ELEMENT);
    DynamicEntity *DynElem_2_2 = new DynamicEntity(logger); DynElem_2_2->setActLevel(2); DynElem_2_2->setIDDE(18); DynElem_2_2->setEnabled(true); DynElem_2_2->setTypeId(TYPE_ACTIVEOTHER_ELEMENT);
    DynamicEntity *DynElem_3_2 = new DynamicEntity(logger); DynElem_3_2->setActLevel(2); DynElem_3_2->setIDDE(19); DynElem_3_2->setEnabled(true); DynElem_3_2->setTypeId(TYPE_ACTIVEOTHER_ELEMENT);

    mem->addDynElemMap_lvl_2(17,DynElem_1_2);
    mem->addDynElemMap_lvl_2(18,DynElem_2_2);
    mem->addDynElemMap_lvl_2(19,DynElem_3_2);

    DynamicEntity *DynElem_1_3 = new DynamicEntity(logger); DynElem_1_3->setActLevel(3); DynElem_1_3->setIDDE(20); DynElem_1_3->setEnabled(true); DynElem_1_3->setTypeId(TYPE_ACTIVEOTHER_ELEMENT);
    DynamicEntity *DynElem_2_3 = new DynamicEntity(logger); DynElem_2_3->setActLevel(3); DynElem_2_3->setIDDE(21); DynElem_2_3->setEnabled(true); DynElem_2_3->setTypeId(TYPE_ACTIVEOTHER_ELEMENT);
    DynamicEntity *DynElem_3_3 = new DynamicEntity(logger); DynElem_3_3->setActLevel(3); DynElem_3_3->setIDDE(22); DynElem_3_3->setEnabled(true); DynElem_3_3->setTypeId(TYPE_ACTIVEOTHER_ELEMENT);

    mem->addDynElemMap_lvl_3(20,DynElem_1_3);
    mem->addDynElemMap_lvl_3(21,DynElem_2_3);
    mem->addDynElemMap_lvl_3(22,DynElem_3_3);

    ///////////////////////////////
    //remote player
    ///////////////////////////////

    DynamicEntity *DynRemPlayer_1 = new DynamicEntity(logger);
    DynRemPlayer_1->setIDDE(23);
    DynRemPlayer_1->setTypeId(TYPE_REM_PLAYER_ELEMENT);
    DynRemPlayer_1->setTypeEntityId(200);
    DynRemPlayer_1->setActLevel(1);
    DynRemPlayer_1->setX(0.00f);
    DynRemPlayer_1->setY(0.00f);
    DynRemPlayer_1->setWidth(64);
    DynRemPlayer_1->setHeight(64);
    DynRemPlayer_1->setEnabled(false);
    mem->addRemPlayerMap(23,DynRemPlayer_1);

    DynamicEntity *DynRemPlayer_2 = new DynamicEntity(logger);
    DynRemPlayer_2->setIDDE(24);
    DynRemPlayer_2->setTypeId(TYPE_REM_PLAYER_ELEMENT);
    DynRemPlayer_2->setTypeEntityId(200);
    DynRemPlayer_2->setActLevel(1);
    DynRemPlayer_2->setX(960.00f);
    DynRemPlayer_2->setY(0.00f);
    DynRemPlayer_2->setWidth(64);
    DynRemPlayer_2->setHeight(64);
    DynRemPlayer_2->setEnabled(true);
    mem->addRemPlayerMap(24,DynRemPlayer_2);

    DynamicEntity *DynRemPlayer_3 = new DynamicEntity(logger);
    DynRemPlayer_3->setIDDE(25);
    DynRemPlayer_3->setTypeId(TYPE_REM_PLAYER_ELEMENT);
    DynRemPlayer_3->setTypeEntityId(200);
    DynRemPlayer_3->setActLevel(1);
    DynRemPlayer_3->setX(960.00f);
    DynRemPlayer_3->setY(704.00f);
    DynRemPlayer_3->setWidth(64);
    DynRemPlayer_3->setHeight(64);
    DynRemPlayer_3->setEnabled(false);
    mem->addRemPlayerMap(25,DynRemPlayer_3);

    DynamicEntity *DynRemPlayer_4 = new DynamicEntity(logger);
    DynRemPlayer_4->setIDDE(26);
    DynRemPlayer_4->setTypeId(TYPE_REM_PLAYER_ELEMENT);
    DynRemPlayer_4->setTypeEntityId(200);
    DynRemPlayer_4->setActLevel(1);
    DynRemPlayer_4->setX(960.00f);
    DynRemPlayer_4->setY(704.00f);
    DynRemPlayer_4->setWidth(64);
    DynRemPlayer_4->setHeight(64);
    DynRemPlayer_4->setEnabled(false);
    mem->addRemPlayerMap(26,DynRemPlayer_4);


    ///////////////////////////////
    logger->debug("[SSNETWORKMANAGERSERVER::createEnvirontment] -- SET UP PARAMETERS ON");
};



static void* execute_RunTaskTCPSession11(void* ctx){
    TCPSession *tcpSes = (TCPSession *)ctx;
    tcpSes->Run();
};

void processServerLogicNew(){
    nClock->start();

    pthread_create(&hebra_1,NULL,execute_RunTaskTCPSession11,tcpSession);
    pthread_create(&hebra_2,NULL,execute_RunTaskTCPSession11,tcpSession);

    do{
      nClient->establishCommunication();
      TCPsocket *clients = nClient->getClientSockets();
      for (int i=0; i<MAX_CLIENT; i++){
          int clientSocketActivity = SDLNet_SocketReady(clients[i]);
          if (clientSocketActivity!=0){
            cQ->push(&clients[i]);
            nClient->setClientSocketFree(i);
          }
      }
      pEngine->processPrediction();
      nClock->evaluateFramerrate();
    }while(TRUE);

    pthread_join(hebra_1,0);
    pthread_join(hebra_2,0);

    nClock->stop();
};

*/
