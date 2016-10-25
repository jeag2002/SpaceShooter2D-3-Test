#include "UDPDispatcherSession.h"


void UDPDispatcherSession::createEnvirontmentNew(){

    //enemigos
    ///////////////////////////////
    DynamicEntity *enemy_1_1 = new DynamicEntity(logger); enemy_1_1->setActLevel(1); enemy_1_1->setIDDE(4); enemy_1_1->setEnabled(true); enemy_1_1->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_1_1->setActMap(this->mapId); enemy_1_1->setActSession(this->sessionId);
    DynamicEntity *enemy_2_1 = new DynamicEntity(logger); enemy_2_1->setActLevel(1); enemy_2_1->setIDDE(5); enemy_2_1->setEnabled(true); enemy_2_1->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_2_1->setActMap(this->mapId); enemy_2_1->setActSession(this->sessionId);
    DynamicEntity *enemy_3_1 = new DynamicEntity(logger); enemy_3_1->setActLevel(1); enemy_3_1->setIDDE(6); enemy_3_1->setEnabled(true); enemy_3_1->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_3_1->setActMap(this->mapId); enemy_3_1->setActSession(this->sessionId);

    mem->addEnemiesMap_lvl_1(4,enemy_1_1);
    mem->addEnemiesMap_lvl_1(5,enemy_2_1);
    mem->addEnemiesMap_lvl_1(6,enemy_3_1);

    DynamicEntity *enemy_1_2 = new DynamicEntity(logger); enemy_1_2->setActLevel(2); enemy_1_2->setIDDE(7); enemy_1_2->setEnabled(true); enemy_1_2->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_1_2->setActMap(this->mapId); enemy_1_2->setActSession(this->sessionId);
    DynamicEntity *enemy_2_2 = new DynamicEntity(logger); enemy_2_2->setActLevel(2); enemy_2_2->setIDDE(8); enemy_2_2->setEnabled(true); enemy_2_2->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_2_2->setActMap(this->mapId); enemy_2_2->setActSession(this->sessionId);
    DynamicEntity *enemy_3_2 = new DynamicEntity(logger); enemy_3_2->setActLevel(2); enemy_3_2->setIDDE(9); enemy_3_2->setEnabled(true); enemy_3_2->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_3_2->setActMap(this->mapId); enemy_3_2->setActSession(this->sessionId);

    mem->addEnemiesMap_lvl_2(7,enemy_1_2);
    mem->addEnemiesMap_lvl_2(8,enemy_2_2);
    mem->addEnemiesMap_lvl_2(9,enemy_3_2);

    DynamicEntity *enemy_1_3 = new DynamicEntity(logger); enemy_1_3->setActLevel(3); enemy_1_3->setIDDE(10); enemy_1_3->setEnabled(true); enemy_1_3->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_1_3->setActMap(this->mapId); enemy_1_3->setActSession(this->sessionId);
    DynamicEntity *enemy_2_3 = new DynamicEntity(logger); enemy_2_3->setActLevel(3); enemy_2_3->setIDDE(11); enemy_2_3->setEnabled(true); enemy_2_3->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_2_3->setActMap(this->mapId); enemy_2_3->setActSession(this->sessionId);
    DynamicEntity *enemy_3_3 = new DynamicEntity(logger); enemy_3_3->setActLevel(3); enemy_3_3->setIDDE(12); enemy_3_3->setEnabled(true); enemy_3_3->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_3_3->setActMap(this->mapId); enemy_3_3->setActSession(this->sessionId);

    mem->addEnemiesMap_lvl_3(10,enemy_1_3);
    mem->addEnemiesMap_lvl_3(11,enemy_2_3);
    mem->addEnemiesMap_lvl_3(12,enemy_3_3);
    ///////////////////////////////

    //elementos dinamicos
    ///////////////////////////////
    DynamicEntity *DynElem_1_1 = new DynamicEntity(logger); DynElem_1_1->setActLevel(1); DynElem_1_1->setIDDE(14); DynElem_1_1->setEnabled(true); DynElem_1_1->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_1_1->setActMap(this->mapId); DynElem_1_1->setActSession(this->sessionId);
    DynamicEntity *DynElem_2_1 = new DynamicEntity(logger); DynElem_2_1->setActLevel(1); DynElem_2_1->setIDDE(15); DynElem_2_1->setEnabled(true); DynElem_2_1->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_2_1->setActMap(this->mapId); DynElem_2_1->setActSession(this->sessionId);
    DynamicEntity *DynElem_3_1 = new DynamicEntity(logger); DynElem_3_1->setActLevel(1); DynElem_3_1->setIDDE(16); DynElem_3_1->setEnabled(true); DynElem_3_1->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_3_1->setActMap(this->mapId); DynElem_3_1->setActSession(this->sessionId);

    mem->addDynElemMap_lvl_1(14,DynElem_1_1);
    mem->addDynElemMap_lvl_1(15,DynElem_2_1);
    mem->addDynElemMap_lvl_1(16,DynElem_3_1);

    DynamicEntity *DynElem_1_2 = new DynamicEntity(logger); DynElem_1_2->setActLevel(2); DynElem_1_2->setIDDE(17); DynElem_1_2->setEnabled(true); DynElem_1_2->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_1_2->setActMap(this->mapId); DynElem_1_2->setActSession(this->sessionId);
    DynamicEntity *DynElem_2_2 = new DynamicEntity(logger); DynElem_2_2->setActLevel(2); DynElem_2_2->setIDDE(18); DynElem_2_2->setEnabled(true); DynElem_2_2->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_2_2->setActMap(this->mapId); DynElem_2_2->setActSession(this->sessionId);
    DynamicEntity *DynElem_3_2 = new DynamicEntity(logger); DynElem_3_2->setActLevel(2); DynElem_3_2->setIDDE(19); DynElem_3_2->setEnabled(true); DynElem_3_2->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_3_2->setActMap(this->mapId); DynElem_3_2->setActSession(this->sessionId);

    mem->addDynElemMap_lvl_2(17,DynElem_1_2);
    mem->addDynElemMap_lvl_2(18,DynElem_2_2);
    mem->addDynElemMap_lvl_2(19,DynElem_3_2);

    DynamicEntity *DynElem_1_3 = new DynamicEntity(logger); DynElem_1_3->setActLevel(3); DynElem_1_3->setIDDE(20); DynElem_1_3->setEnabled(true); DynElem_1_3->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_1_3->setActMap(this->mapId); DynElem_1_3->setActSession(this->sessionId);
    DynamicEntity *DynElem_2_3 = new DynamicEntity(logger); DynElem_2_3->setActLevel(3); DynElem_2_3->setIDDE(21); DynElem_2_3->setEnabled(true); DynElem_2_3->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_2_3->setActMap(this->mapId); DynElem_2_3->setActSession(this->sessionId);
    DynamicEntity *DynElem_3_3 = new DynamicEntity(logger); DynElem_3_3->setActLevel(3); DynElem_3_3->setIDDE(22); DynElem_3_3->setEnabled(true); DynElem_3_3->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_3_3->setActMap(this->mapId); DynElem_3_3->setActSession(this->sessionId);

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
    DynRemPlayer_1->setActMap(this->getMapId());
    DynRemPlayer_1->setActSession(this->getSessionId());
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
    DynRemPlayer_2->setActMap(this->getMapId());
    DynRemPlayer_2->setActSession(this->getSessionId());
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
    DynRemPlayer_3->setActMap(this->getMapId());
    DynRemPlayer_3->setActSession(this->getSessionId());
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
    DynRemPlayer_4->setActMap(this->getMapId());
    DynRemPlayer_4->setActSession(this->getSessionId());
    DynRemPlayer_4->setX(960.00f);
    DynRemPlayer_4->setY(704.00f);
    DynRemPlayer_4->setWidth(64);
    DynRemPlayer_4->setHeight(64);
    DynRemPlayer_4->setEnabled(false);
    mem->addRemPlayerMap(26,DynRemPlayer_4);


    ///////////////////////////////
    logger->debug("[UDPDispatcherSession::createEnvirontment] -- SET UP PARAMETERS FOR MAP [%d] SESSION [%d]",this->mapId,this->sessionId);

}

EventMsg *UDPDispatcherSession::sendAckMsg(DynamicEntity *dEntity, EventMsg *msg, bool result){

    msg->setTramaGet(msg->getTramaGet()+1);

    if (result){
        msg->setTypeMsg(TRAMA_ACK_SESSION);

        playerDataType pDT;
        pDT.playerDataID = 0;
        pDT.actMap = this->mapId;
        pDT.session = this->sessionId;
        pDT.idPlayer =  dEntity->getIDDE();
        pDT.lvl = dEntity->getActLevel();
        pDT.typeID = dEntity->getTypeId();
        pDT.x_pos = dEntity->getX();
        pDT.y_pos = dEntity->getY();
        pDT.width = dEntity->getWidth();
        pDT.heigth = dEntity->getHeight();

        logger->debug("[UDPDispatcherSession::sendAckMsg Map[%d] Session[%d]] SERVER SESSION PLAYER Map:%d Session:%d IdPlayer:%d lvl:%d pos:(%f,%f) width:%d, height:%d",
                      this->mapId,
                      this->sessionId,
                      pDT.actMap,
                      pDT.session,
                      pDT.idPlayer,
                      pDT.lvl,
                      pDT.x_pos,
                      pDT.y_pos,
                      pDT.width,
                      pDT.heigth);


        msg->setPlayerDataType(pDT);
        msg->setMore(NOK);
        msg->setNumTrazas(1);

    }else{
        msg->setTypeMsg(TRAMA_NACK_SESSION);
        msg->setMore(NOK);
        msg->setNumTrazas(1);

        answerType aType;
        aType.type_trama = TYPE_MSG_ANSWER_CONNECTION;
        aType.trama =   msg->getTramaGet()+1;
        aType.command = TYPE_MSG_ANSWER_SESSION;
        aType.result = NOK;
        msg->setAnswerType(aType);


    }

    return msg;
}

DynamicEntity *UDPDispatcherSession::getRemotePlayer(){
   std::map<int, DynamicEntity *> eLvl = mem->getRemPlayerMap();
   DynamicEntity *dEntity;
   int index = 0;
   bool findNotUserPlayer = false;
   for(auto iterator = eLvl.begin(); (iterator != eLvl.end() && !findNotUserPlayer); iterator++){
        index = iterator->first;
        dEntity = iterator->second;        if (!dEntity->isEnabled()){findNotUserPlayer = true;}
    }
    mem->getRemPlayerMapElem(index)->setEnabled(true);
    return dEntity;

}


EventMsg *UDPDispatcherSession::setClientForSession(EventMsg *msg){

    EventMsg *msgOutput = new EventMsg();
    msgOutput->setPacketUPD(msg->getPacketUPD());
    msgOutput->setTypeMsg(TRAMA_NULL);

    if (clientes.size()==0){
        DynamicEntity *dEntity = getRemotePlayer();
        if (dEntity != NULL){
            UDPSession *sessionUDP = new UDPSession(dEntity->getIDDE(),logger,mem,msg->getPacketUPD());
            sessionUDP->setIndexDataGet(msg->getTramaGet());
            sessionUDP->setIndexDataSend(msg->getTramaSend());
            clientes.push_back(sessionUDP);
            numClients++;
            msgOutput->setMsg(sendAckMsg(dEntity,msg,true));
        }
    }else{
        if (numClients <= MAX_CLIENT){
            bool find_it = false;
            for(int i=0; ((i<clientes.size()) && (!find_it)); i++){
                UDPSession *session = clientes[i];
                find_it = ((session->getPacket()->address.host == msg->getPacketUPD()->address.host) && (session->getPacket()->address.port == msg->getPacketUPD()->address.port));
            }

            if (!find_it){
                DynamicEntity *dEntity = getRemotePlayer();
                if (dEntity != NULL){
                    UDPSession *sessionUDP = new UDPSession(dEntity->getIDDE(),logger,mem,msg->getPacketUPD());
                    sessionUDP->setIndexDataGet(msg->getTramaGet());
                    sessionUDP->setIndexDataSend(msg->getTramaSend());
                    clientes.push_back(sessionUDP);
                    numClients++;
                    msgOutput->setMsg(sendAckMsg(dEntity,msg,true));
                }else{
                    logger->warn("[UDPDispatcherSession::setClientForSession Map[%d] Session[%d]] USER [%d]:[%d] NOT ID AVAILABLE, DISCARD PACKET",this->mapId,this->sessionId,msg->getPacketUPD()->address.host,msg->getPacketUPD()->address.port);
                }
            }else{
                logger->warn("[UDPDispatcherSession::setClientForSession Map[%d] Session[%d]] USER [%d]:[%d] ALREADY JOIN TO SESSION, DISCARD PACKET",this->mapId,this->sessionId,msg->getPacketUPD()->address.host,msg->getPacketUPD()->address.port);
                msgOutput->setMsg(sendAckMsg(NULL,msg,false));
            }
        }else{
            logger->warn("[UDPDispatcherSession::setClientForSession Map[%d] Session[%d]] USER [%d]:[%d] NO FREE SPACE DISCARD PACKET",this->mapId,this->sessionId, msg->getPacketUPD()->address.host,msg->getPacketUPD()->address.port);
            msgOutput->setMsg(sendAckMsg(NULL,msg,false));
        }
    }

    return msgOutput;
}


void UDPDispatcherSession::processSessions(EventMsg *msg){


    logger->info("[UDPDispatcherSession::processSessions Map[%d] Session[%d]] active client x MAP[%d]::SESSION[%d] session [%d]",
                 this->mapId,
                 this->sessionId,
                 this->mapId,
                 this->sessionId,
                 clientes.size());

    bool find_it = false;
    for(int i=0; ((i<clientes.size()) && (!find_it)); i++){
        UDPSession *session = clientes[i];

        find_it = ((session->getPacket()->address.host == msg->getPacketUPD()->address.host) &&
                       (session->getPacket()->address.port == msg->getPacketUPD()->address.port));

        logger->debug("[UDPDispatcherSession::processSessions] eval find it [%i] client",i);

        logger->info("[UDPDispatcherSession::processSessions Map[%d] Session[%d]] dir active session [%d]:[%d] remote dir client [%d]:[%d]",
                     this->mapId,
                     this->sessionId,
                     session->getPacket()->address.host,
                     session->getPacket()->address.port,
                     msg->getPacketUPD()->address.host,
                     msg->getPacketUPD()->address.port);

        if (find_it){
            logger->debug("[UDPDispatcherSession::processSessions] PROCESS_INFO_DATA client",i);

            logger->info("[UDPDispatcherSession::processSessions Map[%d] Session[%d]] PROCESSING PLAYER [%d] MAP[%d] SESSION[%d] INPUT_PACKET_[%02d] TRAMASEND [%d] TRAMAGET [%d]",
                         this->mapId,
                         this->sessionId,
                         session->getPlayerId(),
                         this->mapId,
                         this->sessionId,
                         msg->getTypeMsg(),
                         msg->getTramaSend(),
                         msg->getTramaGet());

            if (msg->getTypeMsg() == TRAMA_QRY_DATASERVER){
                sendInfoDataSession(session->getPlayerId(), msg);
            }else{
                session->Run(msg);
                clientes[i]->setUDPSession(session);
            }
            cQInput->pop();

        }

        else{
             /*
             find_it = (
                      (session->getPacket()->address.host == msg->getPacketUPD()->address.host) &&
                      (session->getPacket()->address.port == SESSION_PORT) &&
                      (msg->getTypeMsg() == TRAMA_QRY_DATASERVER) &&
                      (msg->getPlayerDataType().actMap == this->mapId) &&
                      (msg->getPlayerDataType().session == this->sessionId));

             if (find_it){
                 sendInfoDataSession(session->getPlayerId(), msg);
                 cQInput->pop();
             }
             */
        }
    }
}

EventMsg *UDPDispatcherSession::sendWorldStateToClient(EventMsg *msg, int more, int indexServData, DynamicEntity *dEntity){
        EventMsg *outputData = new EventMsg();
        outputData->setTypeMsg(TRAMA_GET_DATASERVER);
        outputData->setTramaSend(msg->getTramaSend());
        outputData->setTramaGet(msg->getTramaGet());
        outputData->setMore(more);
        outputData->setNumTrazas(indexServData);
        outputData->setPacketUPD(msg->getPacketUPD());
        outputData->setCRC16((uint16_t)0);
        outputData->setRemotePlayerType(dEntity->getDynamicEntityRPT());
        return outputData;
}




void UDPDispatcherSession::sendInfoDataSession(int playerID, EventMsg *msg){
    EventMsg **msgs = new EventMsg *[SIZE_REMOTE_ELEMS];

    for(int i=0; i<SIZE_REMOTE_ELEMS; i++){
        msgs[i] = new EventMsg();
        msgs[i]->setPacketUPD(msg->getPacketUPD());
    }

    int indexMsg = 0;

    std::map<int, DynamicEntity *>enemyOfLevel1 = mem->getEnemy_Lvl_1_Map();

    for(auto iterator = enemyOfLevel1.begin(); iterator != enemyOfLevel1.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClient(msg, 1, (SIZE_REMOTE_ELEMS - indexMsg), dEntity));
        indexMsg++;
    }


    std::map<int, DynamicEntity *>enemyOfLevel2 = mem->getEnemy_Lvl_2_Map();

    for(auto iterator = enemyOfLevel2.begin(); iterator != enemyOfLevel2.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClient(msg, 1, (SIZE_REMOTE_ELEMS - indexMsg), dEntity));
        indexMsg++;
    }

    std::map<int, DynamicEntity *>enemyOfLevel3 = mem->getEnemy_Lvl_3_Map();

    for(auto iterator = enemyOfLevel3.begin(); iterator != enemyOfLevel3.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClient(msg, 1, (SIZE_REMOTE_ELEMS - indexMsg), dEntity));
        indexMsg++;
    }


    std::map<int, DynamicEntity *>DynOfLevel1 = mem->getDynElem_Lvl_1_Map();

    for(auto iterator = DynOfLevel1.begin(); iterator != DynOfLevel1.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClient(msg, 1, (SIZE_REMOTE_ELEMS - indexMsg), dEntity));
        indexMsg++;
    }


    std::map<int, DynamicEntity *>DynOfLevel2 = mem->getDynElem_Lvl_2_Map();

    for(auto iterator = DynOfLevel2.begin(); iterator != DynOfLevel2.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClient(msg, 1, (SIZE_REMOTE_ELEMS - indexMsg), dEntity));
        indexMsg++;
    }

    std::map<int, DynamicEntity *>DynOfLevel3 = mem->getDynElem_Lvl_3_Map();

    for(auto iterator = DynOfLevel3.begin(); iterator != DynOfLevel3.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClient(msg, 1, (SIZE_REMOTE_ELEMS - indexMsg), dEntity));
        indexMsg++;
    }

    std::map<int, DynamicEntity *>RemPlayers = mem->getRemPlayerMap();

    for(auto iterator = RemPlayers.begin(); iterator != RemPlayers.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClient(msg, 1, (SIZE_REMOTE_ELEMS - indexMsg), dEntity));
        indexMsg++;
    }

    nCUDP->sendMsgVectorToClientUDP(msgs);
}


void UDPDispatcherSession::processInputMsg(){

    try{
        while (!cQInput->isEmpty()){
            EventMsg *msg = cQInput->front();
            if (msg != NULL){

                logger->debug("[UDPDispatcherSession::processInputMsg Map[%d] Session[%d]] INPUT_PACKET_[%02d] tramaSend [%d] tramaGet [%d]",
                              this->mapId,
                              this->sessionId,
                              msg->getTypeMsg(),
                              msg->getTramaSend(),
                              msg->getTramaGet());

                if (msg->getTypeMsg() == TRAMA_SYNACK_SESSION){
                    playerDataType pDT = msg->getPlayerDataType();
                    logger->debug("[UDPDispatcherSession::processInputMsg Map[%d] Session[%d]] MAP_PLAYER (%d,%d) MAP_SESSION (%d,%d)",
                                  this->mapId,
                                  this->sessionId,
                                  pDT.actMap,
                                  pDT.session,
                                  this->mapId,
                                  this->sessionId);

                    if ((pDT.actMap == this->mapId) && (pDT.session == this->sessionId)){
                        EventMsg *response = setClientForSession(msg);
                        cQOutput->push(response);
                        cQInput->pop();
                        delete response;
                    }
                }else if (msg->getTypeMsg() <= TRAMA_NULL) {
                    processSessions(msg);
                }
            }
        }
    }catch(...){
        logger->debug("[UDPDispatcherSession::processInputMsg] get exception");
    }
}


 void UDPDispatcherSession::Run(){
    while(true){
        pthread_t iThread = pthread_self();
        logger->debug("[UDPDispatcherSession::Run Map[%d] Session[%d]] [%08x] **** INI",this->mapId,this->sessionId,iThread);
        pEngine->processPrediction();
        processInputMsg();
        SDL_Delay(100);
        logger->debug("[UDPDispatcherSession::Run Map[%d] Session[%d]] [%08x] **** END",this->mapId,this->sessionId,iThread);
    }
 };


