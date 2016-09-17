#include "Stdafx.h"
#include "LogEngine.h"
#include "MemManager.h"
#include "QueueManager.h"
#include "NetworkClient.h"
#include "PredictionEngine.h"
#include "ClockEngine.h"

LogEngine *logger;
MemManager *mem;
QueueManager *qMem;
NetworkClient *nClient;
PredictionEngine *pEngine;
ClockEngine *nClock;

CollisionEntities *coll;
AnimationEntities *aEnt;
IAEntities *iAEnt;

int maxPlayers;
int numPlayers;


void processInputMsgFromClient(TCPsocket client, int index, EventMsg *event);
void sendServerDataToClient(TCPsocket client, EventMsg *inputMsg);
void processCommandsFromClient(TCPsocket client, EventMsg *inputMsg);
void createEnvirontment();
void destroyAll();
void getEventSDL();


/*
int main (int argc, char *argv[])
{
   logger = new LogEngine();
   logger->deleteLogFile();
   logger->startUp(1,0);
   logger->printLogFlag();
   logger->info("================ [SSNETWORKMANAGER-SERVER - INI] ================");

   createEnvirontment();

   nClient->initCommunication();
   nClient->establishCommunication();

   getEventSDL();

   nClient->endCommunication();

   destroyAll();
   logger->info("================ [SSNETWORKMANAGER-SERVER - END] ================");
   return 0;
}
*/

void createEnvirontment(){

    mem = new MemManager();
    nClient = new NetworkClient(logger);
    nClock = new ClockEngine(100);

    coll = new CollisionEntities(mem,logger);
    aEnt = new AnimationEntities(mem,logger);
    iAEnt = new IAEntities(mem,logger);

    pEngine = new PredictionEngine(logger,mem,coll,aEnt,iAEnt); //prediction Engine.

    maxPlayers = 4;
    numPlayers = 0;

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
    DynRemPlayer_2->setEnabled(false);
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

void destroyAll(){

   delete coll;
   delete aEnt;
   delete iAEnt;
   delete mem;
   delete qMem;
   delete logger;

};

void getEventSDL(){
    nClock->start();
    do{
      nClient->establishCommunication();
      nClock->evaluateFramerrate();

      TCPsocket *clients = nClient->getClientSockets();
      for (int i=0; i<MAX_CLIENT; i++){
           int clientSocketActivity = SDLNet_SocketReady(clients[i]);
           if (clientSocketActivity!=0){
                EventMsg *inputMsg = nClient->getMsgFromClient(clients[i]);
                processInputMsgFromClient(clients[i],i,inputMsg);
           }
      }
      pEngine->processPrediction();
    }while(TRUE);
    nClock->stop();
}

void processInputMsgFromClient(TCPsocket client, int index, EventMsg *inputMsg){

    EventMsg *msgOutput = new EventMsg();

    if (inputMsg->getTypeMsg() == TRAMA_QRY_SESSION_LIST){

        logger->debug("[SSNETWORKMANAGERSERVER::processInputMsgFromClient] return Available sessions for client [%d]",index);

        msgOutput->setTypeMsg(TRAMA_GET_SESSION_LIST);
        msgOutput->setTramaGet(inputMsg->getTramaSend());
        msgOutput->setTramaSend(inputMsg->getTramaGet());
        msgOutput->setMore(NOK);

        listSessionAvailableType lSAT;

        lSAT.listSessionsID = TYPE_LIST_SESSION_ID;
        lSAT.map_1_id = 1;
        lSAT.session_1_1 = 1;
        lSAT.num_player_ava_1_1 = numPlayers;
        lSAT.num_player_max_1_1 = maxPlayers;
        lSAT.session_1_2 = 2;
        lSAT.num_player_ava_1_2 = 0;
        lSAT.num_player_max_1_2 = 0;

        lSAT.map_2_id = 2;
        lSAT.session_2_1 = 3;
        lSAT.num_player_ava_2_1 = 0;
        lSAT.num_player_max_2_1 = 0;
        lSAT.session_2_2 = 4;
        lSAT.num_player_ava_2_2 = 0;
        lSAT.num_player_max_2_2 = 0;

        msgOutput->setListSessionAvaliableType(lSAT);
        nClient->sendMsgToClient(client,msgOutput);

    }else if (inputMsg->getTypeMsg() == TRAMA_SYNACK_SESSION){

        playerDataType pDT = inputMsg->getPlayerDataType();

        if (numPlayers < maxPlayers){

            logger->debug("[SSNETWORKMANAGERSERVER::processInputMsgFromClient] looking for client [%i] free player space in map [%d] session [%d] (numPlayersActives %d)",index,pDT.actMap,pDT.session,numPlayers);
            bool findNotUserPlayer = false;

            DynamicEntity *dEntity;
            int index = 0;
            std::map<int, DynamicEntity *> eLvl = mem->getRemPlayerMap();

            for(auto iterator = eLvl.begin(); (iterator != eLvl.end() && !findNotUserPlayer); iterator++){
                 index = iterator->first;
                 dEntity = iterator->second;                 if (!dEntity->isEnabled()){findNotUserPlayer = true;}
            }

            mem->getRemPlayerMapElem(index)->setEnabled(true);

            pDT.idPlayer =  mem->getRemPlayerMapElem(index)->getIDDE();
            pDT.lvl = mem->getRemPlayerMapElem(index)->getActLevel();
            pDT.typeID = mem->getRemPlayerMapElem(index)->getTypeId();
            pDT.x_pos = mem->getRemPlayerMapElem(index)->getX();
            pDT.y_pos = mem->getRemPlayerMapElem(index)->getY();
            pDT.width = mem->getRemPlayerMapElem(index)->getWidth();
            pDT.heigth = mem->getRemPlayerMapElem(index)->getHeight();

            logger->debug("[SSNETWORKMANAGERSERVER::processInputMsgFromClient] assigned to new client IDPlayer Type:[%d] ID:[%d] X_POS:[%f] Y_POS:[%f] WIDTH:[%d] HEIGHT:[%d]",
                          pDT.typeID,
                          pDT.idPlayer,
                          pDT.x_pos,
                          pDT.y_pos,
                          pDT.width,
                          pDT.heigth);

            msgOutput->setTypeMsg(TRAMA_ACK_SESSION);
            msgOutput->setTramaGet(inputMsg->getTramaSend());
            msgOutput->setTramaSend(inputMsg->getTramaGet());
            msgOutput->setMore(NOK);
            msgOutput->setPlayerDataType(pDT);

            nClient->sendMsgToClient(client, msgOutput);

           numPlayers++;
        }else{

            logger->debug("[SSNETWORKMANAGERSERVER::processInputMsgFromClient] no free player space in map [%d] session [%d] for client [%d]",pDT.actMap,pDT.session,index);

            msgOutput->setTypeMsg(TRAMA_NACK_SESSION);
            msgOutput->setTramaGet(inputMsg->getTramaSend());
            msgOutput->setTramaSend(inputMsg->getTramaGet());
            msgOutput->setMore(NOK);

            answerType aType;
            aType.type_trama = TYPE_MSG_ANSWER_CONNECTION;
            aType.trama =   inputMsg->getTramaGet();
            aType.command = TYPE_MSG_ANSWER_SESSION;
            aType.result = NOK;

            msgOutput->setAnswerType(aType);
            nClient->sendMsgToClient(client, msgOutput);
        }
    }else if (inputMsg->getTypeMsg() == TRAMA_QRY_DATASERVER){
        logger->debug("[SSNETWORKMANAGERSERVER::processInputMsgFromClient] send all the data to the client [%d]",index);
        sendServerDataToClient(client, inputMsg);

    }else if ((inputMsg->getTypeMsg() == TRAMA_COMMAND) || (inputMsg->getTypeMsg() == TRAMA_SND_ORDER_TO_SERVER)){
        logger->debug("[SSNETWORKMANAGERSERVER::processInputMsgFromClient] process input command from the client [%d]");
        processCommandsFromClient(client, inputMsg);
    }
}


void sendServerDataToClient(TCPsocket client, EventMsg *inputMsg){

    DynamicEntity *dEntity;

    //ENEMIES-LVL1
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::map<int, DynamicEntity *> eLvl = mem->getEnemy_Lvl_1_Map();
    for(auto iterator = eLvl.begin(); iterator != eLvl.end(); iterator++){
        int i = iterator->first;
        dEntity = iterator->second;

        EventMsg *outputMsg = new EventMsg(TRAMA_GET_DATASERVER,inputMsg->getTramaSend(),inputMsg->getTramaGet(),OK);
        outputMsg->setRemotePlayerType(dEntity->getDynamicEntityRPT());
        nClient->sendMsgToClient(client, outputMsg);
    }

    //ENEMIES-LVL2
    eLvl = mem->getEnemy_Lvl_2_Map();
    for(auto iterator = eLvl.begin(); iterator != eLvl.end(); iterator++){
        int i = iterator->first;
        dEntity = iterator->second;

        EventMsg *outputMsg = new EventMsg(TRAMA_GET_DATASERVER,inputMsg->getTramaSend(),inputMsg->getTramaGet(),OK);
        outputMsg->setRemotePlayerType(dEntity->getDynamicEntityRPT());
        nClient->sendMsgToClient(client, outputMsg);
    }

    //ENEMIES-LVL2
    eLvl = mem->getEnemy_Lvl_3_Map();
    for(auto iterator = eLvl.begin(); iterator != eLvl.end(); iterator++){
        int i = iterator->first;
        dEntity = iterator->second;

        EventMsg *outputMsg = new EventMsg(TRAMA_GET_DATASERVER,inputMsg->getTramaSend(),inputMsg->getTramaGet(),OK);
        outputMsg->setRemotePlayerType(dEntity->getDynamicEntityRPT());
        nClient->sendMsgToClient(client, outputMsg);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //DYNELEM-LVL1
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    eLvl = mem->getDynElem_Lvl_1_Map();
    for(auto iterator = eLvl.begin(); iterator != eLvl.end(); iterator++){
        int i = iterator->first;
        dEntity = iterator->second;

        EventMsg *outputMsg = new EventMsg(TRAMA_GET_DATASERVER,inputMsg->getTramaSend(),inputMsg->getTramaGet(),OK);
        outputMsg->setRemotePlayerType(dEntity->getDynamicEntityRPT());
        nClient->sendMsgToClient(client, outputMsg);
    }

    //DYNELEM-LVL2
    eLvl = mem->getDynElem_Lvl_2_Map();
    for(auto iterator = eLvl.begin(); iterator != eLvl.end(); iterator++){
        int i = iterator->first;
        dEntity = iterator->second;

        EventMsg *outputMsg = new EventMsg(TRAMA_GET_DATASERVER,inputMsg->getTramaSend(),inputMsg->getTramaGet(),OK);
        outputMsg->setRemotePlayerType(dEntity->getDynamicEntityRPT());
        nClient->sendMsgToClient(client, outputMsg);
    }

    //DYNELEM-LVL3
    eLvl = mem->getDynElem_Lvl_3_Map();
    for(auto iterator = eLvl.begin(); iterator != eLvl.end(); iterator++){
        int i = iterator->first;
        dEntity = iterator->second;

        EventMsg *outputMsg = new EventMsg(TRAMA_GET_DATASERVER,inputMsg->getTramaSend(),inputMsg->getTramaGet(),OK);
        outputMsg->setRemotePlayerType(dEntity->getDynamicEntityRPT());
        nClient->sendMsgToClient(client, outputMsg);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //REMOTEPLAYERS
    eLvl = mem->getRemPlayerMap();
    for(auto iterator = eLvl.begin(); iterator != eLvl.end(); iterator++){
        int i = iterator->first;
        dEntity = iterator->second;

        if (dEntity->isEnabled()){
            EventMsg *outputMsg = new EventMsg(TRAMA_GET_DATASERVER,inputMsg->getTramaSend(),inputMsg->getTramaGet(),OK);
            outputMsg->setRemotePlayerType(dEntity->getDynamicEntityRPT());
            nClient->sendMsgToClient(client, outputMsg);
        }
    }

    //SEND MSG SERVER TO CLIENT.

    //SEND END MSG SERVER TO CLIENT.
    EventMsg *finalMsg = new EventMsg(TRAMA_GET_DATASERVER,inputMsg->getTramaSend(),inputMsg->getTramaGet(),NOK);
    nClient->sendMsgToClient(client,finalMsg);
}


void processCommandsFromClient(TCPsocket client, EventMsg *inputMsg){

    if (inputMsg->getTypeMsg() == TRAMA_COMMAND){
        if (inputMsg->getMovementType().movementID == TYPE_COMMAND_MOVEMENT){
            logger->debug("[SSNETWORKMANAGERSERVER::processCommandsFromClient] PROCESS REMOTE INPUT COMMAND MOVEMENT set IDCLIENT [%d] (lvl:%d,x:%f,y:%f)",
                          inputMsg->getMovementType().idPlayer,
                          inputMsg->getMovementType().lvl,
                          inputMsg->getMovementType().x,
                          inputMsg->getMovementType().y
                          );
            mem->getRemPlayerMapElem(inputMsg->getMovementType().idPlayer)->setRemoteMovement(inputMsg->getMovementType());

        }else if (inputMsg->getShotType().shotID == TYPE_COMMAND_SHOOT){

        }else if (inputMsg->getChangeWeaponType().changeWeaponID == TYPE_COMMAND_CHGWPN){

        }else if (inputMsg->getExitType().exitID == TYPE_COMMAND_EXIT){

        }
    }else if (inputMsg->getTypeMsg() == TRAMA_SND_ORDER_TO_SERVER){


    }
}
