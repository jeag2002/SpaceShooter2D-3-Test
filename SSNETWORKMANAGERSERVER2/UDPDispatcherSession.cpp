#include "UDPDispatcherSession.h"

//CREATE ENVIRONMENT
void UDPDispatcherSession::createEnvirontmentNew(){

    //enemigos
    ///////////////////////////////
    DynamicEntity *enemy_1_1 = new DynamicEntity(logger); enemy_1_1->setActLevel(1); enemy_1_1->setIDDE(4); enemy_1_1->setEnabled(true); enemy_1_1->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_1_1->setActMap(this->mapId); enemy_1_1->setActSession(this->sessionId); enemy_1_1->setX(128); enemy_1_1->setY(128);
    DynamicEntity *enemy_2_1 = new DynamicEntity(logger); enemy_2_1->setActLevel(1); enemy_2_1->setIDDE(5); enemy_2_1->setEnabled(true); enemy_2_1->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_2_1->setActMap(this->mapId); enemy_2_1->setActSession(this->sessionId); enemy_2_1->setX(64); enemy_2_1->setY(64);
    DynamicEntity *enemy_3_1 = new DynamicEntity(logger); enemy_3_1->setActLevel(1); enemy_3_1->setIDDE(6); enemy_3_1->setEnabled(true); enemy_3_1->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_3_1->setActMap(this->mapId); enemy_3_1->setActSession(this->sessionId); enemy_3_1->setX(128); enemy_3_1->setY(64);

    mem->addEnemiesMap_lvl_1(4,enemy_1_1);
    mem->addEnemiesMap_lvl_1(5,enemy_2_1);
    mem->addEnemiesMap_lvl_1(6,enemy_3_1);

    DynamicEntity *enemy_1_2 = new DynamicEntity(logger); enemy_1_2->setActLevel(2); enemy_1_2->setIDDE(7); enemy_1_2->setEnabled(true); enemy_1_2->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_1_2->setActMap(this->mapId); enemy_1_2->setActSession(this->sessionId); enemy_1_2->setX(128); enemy_1_2->setY(128);
    DynamicEntity *enemy_2_2 = new DynamicEntity(logger); enemy_2_2->setActLevel(2); enemy_2_2->setIDDE(8); enemy_2_2->setEnabled(true); enemy_2_2->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_2_2->setActMap(this->mapId); enemy_2_2->setActSession(this->sessionId); enemy_2_2->setX(64); enemy_2_2->setY(64);
    DynamicEntity *enemy_3_2 = new DynamicEntity(logger); enemy_3_2->setActLevel(2); enemy_3_2->setIDDE(9); enemy_3_2->setEnabled(true); enemy_3_2->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_3_2->setActMap(this->mapId); enemy_3_2->setActSession(this->sessionId); enemy_3_2->setX(128); enemy_3_2->setY(64);

    mem->addEnemiesMap_lvl_2(7,enemy_1_2);
    mem->addEnemiesMap_lvl_2(8,enemy_2_2);
    mem->addEnemiesMap_lvl_2(9,enemy_3_2);

    DynamicEntity *enemy_1_3 = new DynamicEntity(logger); enemy_1_3->setActLevel(3); enemy_1_3->setIDDE(10); enemy_1_3->setEnabled(true); enemy_1_3->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_1_3->setActMap(this->mapId); enemy_1_3->setActSession(this->sessionId); enemy_1_3->setX(128); enemy_1_3->setY(128);
    DynamicEntity *enemy_2_3 = new DynamicEntity(logger); enemy_2_3->setActLevel(3); enemy_2_3->setIDDE(11); enemy_2_3->setEnabled(true); enemy_2_3->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_2_3->setActMap(this->mapId); enemy_2_3->setActSession(this->sessionId); enemy_2_3->setX(64); enemy_2_3->setY(64);
    DynamicEntity *enemy_3_3 = new DynamicEntity(logger); enemy_3_3->setActLevel(3); enemy_3_3->setIDDE(12); enemy_3_3->setEnabled(true); enemy_3_3->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_3_3->setActMap(this->mapId); enemy_3_3->setActSession(this->sessionId); enemy_3_3->setX(128); enemy_3_3->setY(64);

    mem->addEnemiesMap_lvl_3(10,enemy_1_3);
    mem->addEnemiesMap_lvl_3(11,enemy_2_3);
    mem->addEnemiesMap_lvl_3(12,enemy_3_3);
    ///////////////////////////////

    //elementos dinamicos
    ///////////////////////////////
    DynamicEntity *DynElem_1_1 = new DynamicEntity(logger); DynElem_1_1->setActLevel(1); DynElem_1_1->setIDDE(14); DynElem_1_1->setEnabled(true); DynElem_1_1->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_1_1->setActMap(this->mapId); DynElem_1_1->setActSession(this->sessionId); DynElem_1_1->setX(256); DynElem_1_1->setY(256); DynElem_1_1->setWidth(16); DynElem_1_1->setHeight(16);
    DynamicEntity *DynElem_2_1 = new DynamicEntity(logger); DynElem_2_1->setActLevel(1); DynElem_2_1->setIDDE(15); DynElem_2_1->setEnabled(true); DynElem_2_1->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_2_1->setActMap(this->mapId); DynElem_2_1->setActSession(this->sessionId); DynElem_2_1->setX(256); DynElem_2_1->setY(64); DynElem_2_1->setWidth(16); DynElem_2_1->setHeight(16);
    DynamicEntity *DynElem_3_1 = new DynamicEntity(logger); DynElem_3_1->setActLevel(1); DynElem_3_1->setIDDE(16); DynElem_3_1->setEnabled(true); DynElem_3_1->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_3_1->setActMap(this->mapId); DynElem_3_1->setActSession(this->sessionId); DynElem_3_1->setX(64); DynElem_3_1->setY(256); DynElem_3_1->setWidth(16); DynElem_3_1->setHeight(16);

    mem->addDynElemMap_lvl_1(14,DynElem_1_1);
    mem->addDynElemMap_lvl_1(15,DynElem_2_1);
    mem->addDynElemMap_lvl_1(16,DynElem_3_1);

    DynamicEntity *DynElem_1_2 = new DynamicEntity(logger); DynElem_1_2->setActLevel(2); DynElem_1_2->setIDDE(17); DynElem_1_2->setEnabled(true); DynElem_1_2->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_1_2->setActMap(this->mapId); DynElem_1_2->setActSession(this->sessionId); DynElem_1_2->setX(256); DynElem_1_2->setY(256); DynElem_1_2->setWidth(16); DynElem_1_2->setHeight(16);
    DynamicEntity *DynElem_2_2 = new DynamicEntity(logger); DynElem_2_2->setActLevel(2); DynElem_2_2->setIDDE(18); DynElem_2_2->setEnabled(true); DynElem_2_2->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_2_2->setActMap(this->mapId); DynElem_2_2->setActSession(this->sessionId); DynElem_2_2->setX(256); DynElem_2_2->setY(64); DynElem_2_2->setWidth(16); DynElem_2_2->setHeight(16);
    DynamicEntity *DynElem_3_2 = new DynamicEntity(logger); DynElem_3_2->setActLevel(2); DynElem_3_2->setIDDE(19); DynElem_3_2->setEnabled(true); DynElem_3_2->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_3_2->setActMap(this->mapId); DynElem_3_2->setActSession(this->sessionId); DynElem_3_2->setX(64); DynElem_2_2->setY(256); DynElem_3_2->setWidth(16); DynElem_3_2->setHeight(16);

    mem->addDynElemMap_lvl_2(17,DynElem_1_2);
    mem->addDynElemMap_lvl_2(18,DynElem_2_2);
    mem->addDynElemMap_lvl_2(19,DynElem_3_2);

    DynamicEntity *DynElem_1_3 = new DynamicEntity(logger); DynElem_1_3->setActLevel(3); DynElem_1_3->setIDDE(20); DynElem_1_3->setEnabled(true); DynElem_1_3->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_1_3->setActMap(this->mapId); DynElem_1_3->setActSession(this->sessionId); DynElem_1_3->setX(256); DynElem_1_3->setY(256); DynElem_1_3->setWidth(16); DynElem_1_3->setHeight(16);
    DynamicEntity *DynElem_2_3 = new DynamicEntity(logger); DynElem_2_3->setActLevel(3); DynElem_2_3->setIDDE(21); DynElem_2_3->setEnabled(true); DynElem_2_3->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_2_3->setActMap(this->mapId); DynElem_2_3->setActSession(this->sessionId); DynElem_2_3->setX(256); DynElem_2_3->setY(64); DynElem_2_3->setWidth(16); DynElem_2_3->setHeight(16);
    DynamicEntity *DynElem_3_3 = new DynamicEntity(logger); DynElem_3_3->setActLevel(3); DynElem_3_3->setIDDE(22); DynElem_3_3->setEnabled(true); DynElem_3_3->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_3_3->setActMap(this->mapId); DynElem_3_3->setActSession(this->sessionId); DynElem_3_3->setX(64); DynElem_3_3->setY(256); DynElem_3_3->setWidth(16); DynElem_3_3->setHeight(16);

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
    DynRemPlayer_3->setActLevel(2);
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
    DynRemPlayer_4->setActLevel(2);
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

//SEND ACK MSG
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


//ENABLE AND ASOCIATE AVAILABLE CLIENT TO THE SESSION
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


//SEND MSGS TO THE SESSION-CLIENT
EventMsg *UDPDispatcherSession::sendEventMsg(const char *iMsg, UDPSession *session){

    EventMsg *msg = new EventMsg();
    msgType mType;

    mType.actMap = this->mapId;
    mType.session = this->sessionId;
    mType.msgTypeID = TYPE_MSG_FROM_SERVER;
    mType.originMsg = ID_SERVER;
    mType.endMsg = session->getPlayerId();

    for(int i=0; i<SIZE_MSG; i++){
        mType.msg[i] = '\0';
        mType.msg[i] = iMsg[i];
    }

    msg->setMsgType(mType);
    msg->setTypeMsg(TRAMA_SND_ORDER_TO_SERVER);
    msg->setTramaSend(session->getIndexDataSend());
    msg->setTramaGet(session->getIndexDataGet());
    msg->setMore(0);
    msg->setNumTrazas(1);

    packetDataType pDT;
    pDT.address.host = session->getHost();
    //pDT.address.port = session->getPort();
    pDT.address.port = SDL_SwapBE16(SDL_SwapBE16(session->getPort())+1);
    pDT.len = SIZE_MSG;
    pDT.maxlen = SIZE_MSG;
    pDT.status = 0;

    msg->setPacketUDP(pDT);
    return msg;
}


//BROADCAST MSGS FOR ALL CLIENTS OF THE SESSION
void UDPDispatcherSession::sendNotificationServerToDiffClients(const char *msg, int userDest){


    for(int i=0; i<clientes.size(); i++){
        UDPSession *session = clientes[i];
        if (userDest==0){
            EventMsg *eMsg = sendEventMsg(msg,session);
            //cQOutput->push(eMsg);
            sendMsgToOutput(eMsg);
        }else if (userDest == session->getPlayerId()){
            EventMsg *eMsg = sendEventMsg(msg,session);
            //cQOutput->push(eMsg);
            sendMsgToOutput(eMsg);
        }
    }
}


//PROCESSING INPUT MSGS FOR ACTUAL SESSION
EventMsg *UDPDispatcherSession::setClientForSession(EventMsg *msg){

    EventMsg *msgOutput = new EventMsg();
    msgOutput->setPacketUDP(msg->getPacketUPD());
    msgOutput->setTypeMsg(TRAMA_NULL);

    remoteHostData rHD = UtilsProtocol::parseRemoteHostData(msg->getPacketUPD());


    if (clientes.size()==0){
        DynamicEntity *dEntity = getRemotePlayer();
        if (dEntity != NULL){
            UDPSession *sessionUDP = new UDPSession(dEntity->getIDDE(),logger,mem,msg->getPacketUPD().address.host,msg->getPacketUPD().address.port);
            sessionUDP->setIndexDataGet(msg->getTramaGet());
            sessionUDP->setIndexDataSend(msg->getTramaSend());

            clientes.push_back(sessionUDP);
            numClients++;

            logger->debug("[UDPDispatcherSession::setClientForSession Map[%d] Session[%d]] JOIN PLAYER [%d] TRAMASEND [%d] TRAMAGET [%d] FROM REMOTE HOST ([%d]:[%d]) NUM_CLIENT [%d]",
                          this->mapId,
                          this->sessionId,
                          sessionUDP->getPlayerId(),
                          sessionUDP->getIndexDataSend(),
                          sessionUDP->getIndexDataGet(),
                          sessionUDP->getHost(),
                          sessionUDP->getPort(),
                          numClients
                          );


            msgOutput->setMsg(sendAckMsg(dEntity,msg,true));

            char msg[100];
            for(int i=0; i<100; i++){msg[i]='\0';}
            sprintf(msg,"activate client [%d] map [%d] session [%d]",dEntity->getIDDE(),this->mapId,this->sessionId);
            sendNotificationServerToDiffClients((const char *)msg,0);


        }
    }else{
        if (numClients <= MAX_CLIENT){
            bool find_it = false;
            int res = 0;
            for(int i=0; ((i<clientes.size()) && (!find_it)); i++){
                UDPSession *session = clientes[i];

                find_it = ((session->getHost() == msg->getPacketUPD().address.host) && (session->getPort() == msg->getPacketUPD().address.port));

                if (!find_it){res = 0;}
                else{res = 1;}


                logger->debug("[UDPDispatcherSession::setClientForSession Map[%d] Session[%d]] EXIST SESSION? [%d] URL (%d:%d) <> input CLIENT URL (%d:%d) ::= RES[%d]",
                      this->mapId,
                      this->sessionId,
                      i,
                      session->getHost(),
                      session->getPort(),
                      msg->getPacketUPD().address.host,
                      msg->getPacketUPD().address.port,
                      res);
            }

            if (!find_it){
                DynamicEntity *dEntity = getRemotePlayer();
                if (dEntity != NULL){
                    UDPSession *sessionUDP = new UDPSession(dEntity->getIDDE(),logger,mem,msg->getPacketUPD().address.host,msg->getPacketUPD().address.port);
                    sessionUDP->setIndexDataGet(msg->getTramaGet());
                    sessionUDP->setIndexDataSend(msg->getTramaSend());
                    clientes.push_back(sessionUDP);
                    numClients++;
                    msgOutput->setMsg(sendAckMsg(dEntity,msg,true));
                    logger->debug("[UDPDispatcherSession::setClientForSession Map[%d] Session[%d]] IDPLAYER:[%d] JOINED TO SESSION INC NUM_CLIENTS:[%d]",this->mapId,this->sessionId, msgOutput->getPlayerDataType().idPlayer,numClients);

                    char msg[100];
                    for(int i=0; i<100; i++){msg[i]='\0';}
                    sprintf(msg,"activate client [%d] map [%d] session [%d]",dEntity->getIDDE(),this->mapId,this->sessionId);
                    sendNotificationServerToDiffClients((const char *)msg,0);

                }else{
                    logger->warn("[UDPDispatcherSession::setClientForSession Map[%d] Session[%d]] USER [%s]:[%d] NOT ID AVAILABLE, DISCARD PACKET",this->mapId,this->sessionId,rHD.host,rHD.port);
                }
            }else{
                logger->warn("[UDPDispatcherSession::setClientForSession Map[%d] Session[%d]] USER [%s]:[%d] ALREADY JOIN TO SESSION, DISCARD PACKET",this->mapId,this->sessionId,rHD.host,rHD.port);
                msgOutput->setMsg(sendAckMsg(NULL,msg,false));
            }
        }else{
            logger->warn("[UDPDispatcherSession::setClientForSession Map[%d] Session[%d]] USER [%s]:[%d] NO FREE SPACE DISCARD PACKET",this->mapId,this->sessionId,rHD.host,rHD.port);
            msgOutput->setMsg(sendAckMsg(NULL,msg,false));
        }
    }

    return msgOutput;
}


//PROCESS PING MSG TO CLIENT
void UDPDispatcherSession::sendPingToClient(EventMsg *msg, int indexServData){

     if (indexServData < clientes.size()){
        UDPSession *session = clientes[indexServData];
        session->setTimeQOS(SDL_GetTicks());
        session->setReady(true);
        clientes[indexServData] = session;

        EventMsg *msg = new EventMsg();
        msg->setTypeMsg(TRAMA_PING);
        msg->setTramaSend(session->getIndexDataSend());
        msg->setTramaGet(session->getIndexDataGet());
        msg->setMore(0);
        msg->setNumTrazas(1);

        packetDataType pDT;
        pDT.address.host = session->getHost();
        pDT.address.port = session->getPort();
        pDT.len = SIZE_MSG;
        pDT.maxlen = SIZE_MSG;
        pDT.status = 0;

        msg->setPacketUDP(pDT);
        sendMsgToOutput(msg);
     }
}

//PROCESS PONG MSG TO CLIENT
void UDPDispatcherSession::sendTimeQOSToClients(EventMsg *msg, int indexServData){

    long timestamp = 0;
    long limInf = 0;

    for(int i=0;i<clientes.size();i++){

        UDPSession *session = clientes[i];
        limInf = session->getTimeQOS();

        if (i==indexServData){
           limInf = SDL_GetTicks() - limInf;
           session->setTimeQOS(limInf);
           clientes[indexServData] = session;
        }
        timestamp =  timestamp + limInf;
    }

    //margen medio respuesta cliente-servidor
    timestamp = timestamp / clientes.size();
    mem->setSizeTimeServer(timestamp);

    logger->info("[UDPDispatcherSession::processSessions Map[%d] Session[%d]] Average Timestamp QOS[%d]",
                 this->mapId,
                 this->sessionId,
                 mem->getSizeTimeServer());

    bool isNewClient = false;

    for(int j=0; j<clientes.size(); j++){
        UDPSession *session = clientes[j];
        isNewClient = (j == indexServData);
        processingMsgQOSToOutput(mem->getSizeTimeServer(),mem->getTimeStampServer(),session,isNewClient);
        //session->setReady(true);
        clientes[j] = session;
    }

}

//SEND TIME MEDIA BETWEEN CLIENT & SERVER
void UDPDispatcherSession::processingMsgQOSToOutput(long timeServer, long timeStamp, UDPSession *session, bool isNewClient){
    EventMsg *msg = new EventMsg();

    msg->setTypeMsg(TRAMA_RESULT_TEST);
    msg->setTramaSend(session->getIndexDataSend());
    msg->setTramaGet(session->getIndexDataGet());
    msg->setMore(0);
    msg->setNumTrazas(1);

    resultPingType rPingType;
    rPingType.millisping = timeServer;
    rPingType.indexAuthServer = timeStamp;

    msg->setResultPingType(rPingType);

    packetDataType pDT;
    pDT.address.host = session->getHost();
    if (isNewClient){
        pDT.address.port = session->getPort();
    }else{
        pDT.address.port = SDL_SwapBE16(SDL_SwapBE16(session->getPort())+1);
    }
    pDT.len = SIZE_MSG;
    pDT.maxlen = SIZE_MSG;
    pDT.status = 0;
    msg->setPacketUDP(pDT);

    sendMsgToOutput(msg);
}




void UDPDispatcherSession::restablishIniDataRemoteClient(int idPlayer){

    if (idPlayer == 23){

        mem->getRemPlayerMapElem(idPlayer)->setTypeId(TYPE_REM_PLAYER_ELEMENT);
        mem->getRemPlayerMapElem(idPlayer)->setTypeEntityId(200);
        mem->getRemPlayerMapElem(idPlayer)->setActLevel(1);
        mem->getRemPlayerMapElem(idPlayer)->setActMap(this->getMapId());
        mem->getRemPlayerMapElem(idPlayer)->setActSession(this->getSessionId());
        mem->getRemPlayerMapElem(idPlayer)->setX(0.00f);
        mem->getRemPlayerMapElem(idPlayer)->setY(0.00f);

    }else if (idPlayer == 24){

        mem->getRemPlayerMapElem(idPlayer)->setTypeId(TYPE_REM_PLAYER_ELEMENT);
        mem->getRemPlayerMapElem(idPlayer)->setTypeEntityId(200);
        mem->getRemPlayerMapElem(idPlayer)->setActLevel(1);
        mem->getRemPlayerMapElem(idPlayer)->setActMap(this->getMapId());
        mem->getRemPlayerMapElem(idPlayer)->setActSession(this->getSessionId());
        mem->getRemPlayerMapElem(idPlayer)->setX(960.00f);
        mem->getRemPlayerMapElem(idPlayer)->setY(0.00f);


    }else if (idPlayer == 25){

        mem->getRemPlayerMapElem(idPlayer)->setTypeId(TYPE_REM_PLAYER_ELEMENT);
        mem->getRemPlayerMapElem(idPlayer)->setTypeEntityId(200);
        mem->getRemPlayerMapElem(idPlayer)->setActLevel(2);
        mem->getRemPlayerMapElem(idPlayer)->setActMap(this->getMapId());
        mem->getRemPlayerMapElem(idPlayer)->setActSession(this->getSessionId());
        mem->getRemPlayerMapElem(idPlayer)->setX(960.00f);
        mem->getRemPlayerMapElem(idPlayer)->setY(704.00f);


    }else if (idPlayer == 26){

        mem->getRemPlayerMapElem(idPlayer)->setTypeId(TYPE_REM_PLAYER_ELEMENT);
        mem->getRemPlayerMapElem(idPlayer)->setTypeEntityId(200);
        mem->getRemPlayerMapElem(idPlayer)->setActLevel(2);
        mem->getRemPlayerMapElem(idPlayer)->setActMap(this->getMapId());
        mem->getRemPlayerMapElem(idPlayer)->setActSession(this->getSessionId());
        mem->getRemPlayerMapElem(idPlayer)->setX(0.00f);
        mem->getRemPlayerMapElem(idPlayer)->setY(704.00f);

    }

    mem->getRemPlayerMapElem(idPlayer)->setEnabled(false);
}


void UDPDispatcherSession::deleteClientToSession(EventMsg *msg){

    exitType eType = msg->getExitType();

    //DISABLE REMOTEPLAYER
    ///////////////////////////////////////////////////////////////
    if (mem->getRemPlayerMapElem(eType.idPlayer)!=NULL){
       restablishIniDataRemoteClient(eType.idPlayer);
    }
    ///////////////////////////////////////////////////////////////

    //DELETE USER OF SESSIONS
    ///////////////////////////////////////////////////////////////
    int i=0;
    for(i=0; i<clientes.size(); i++){
        UDPSession *session = clientes[i];
        if (session->getPlayerId() == eType.idPlayer){
            break;
        }
    }

    //if (i>0){i=i-1;}
    clientes.erase(clientes.begin()+i);
    ///////////////////////////////////////////////////////////////

    //NOTIFICATION TO THE REST OF USERS
    ///////////////////////////////////////////////////////////////
    char msgText[100];
    for(int i=0;i<100; i++){msgText[i]='\0';}
    sprintf(msgText,"user ID [%d] leave of session",eType.idPlayer);

    logger->debug("[UDPDispatcherSession::processSessions Map[%d] Session[%d]] delete active user[%d]::=[%d] MSG::[%s]",
                  this->mapId,
                  this->sessionId,
                  i,
                  eType.idPlayer,
                  msgText
                  );


    sendNotificationServerToDiffClients(msgText,0);
    ///////////////////////////////////////////////////////////////
}

void UDPDispatcherSession::createNewActiveElement(EventMsg *msg){

    shotType sT = msg->getShotType();
    int playerId = sT.idPlayer;
    DynamicEntity *dEntity = mem->getRemPlayerMapElem(playerId);

    int index = (playerId*100)+newIDActiveElem;

    DynamicEntity *DynElem_aux = new DynamicEntity(logger);
    DynElem_aux->setActLevel(dEntity->getActLevel());
    DynElem_aux->setIDDE(index);
    DynElem_aux->setEnabled(true);
    DynElem_aux->setTypeId(TYPE_ACTIVEOTHER_ELEMENT);
    DynElem_aux->setActMap(this->mapId);
    DynElem_aux->setActSession(this->sessionId);
    DynElem_aux->setX(dEntity->getX()+dEntity->getWidth()+2);
    DynElem_aux->setY(dEntity->getY()+(dEntity->getHeight()/2));
    DynElem_aux->setWidth(16);
    DynElem_aux->setHeight(16);

    if (sT.actMap == 1){
        mem->addDynElemMap_lvl_1(index,DynElem_aux);
    }else if (sT.actMap == 2){
        mem->addDynElemMap_lvl_2(index,DynElem_aux);
    }else{
        mem->addDynElemMap_lvl_3(index,DynElem_aux);
    }

    logger->debug("[UDPDispatcherSession::processSessions Map[%d] Session[%d]] created new element ID [%d] at (lvl:%d,x:%f,y:%f)",
                    this->mapId,
                    this->sessionId,
                    DynElem_aux->getIDDE(),
                    DynElem_aux->getActLevel(),
                    DynElem_aux->getX(),
                    DynElem_aux->getY());

    newIDActiveElem = newIDActiveElem + 1;
}


//ACT CLIENT INFORMATION
void UDPDispatcherSession::actClientInformation(bool data){
    for (int i=0; i<clientes.size(); i++){
        ((UDPSession *)clientes[i])->setStateFlag(data);
    }
}

//PROCESS INPUT SESSION MSGS
void UDPDispatcherSession::processSessions(EventMsg *msg){


    logger->info("[UDPDispatcherSession::processSessions Map[%d] Session[%d]] active client x MAP[%d]::SESSION[%d] session [%d]",
                 this->mapId,
                 this->sessionId,
                 this->mapId,
                 this->sessionId,
                 clientes.size());

    bool find_it = false;
    int res = 0;
    int index = 0;

    UDPSession *session = NULL;

    for(int i=0; ((i<clientes.size()) && (!find_it)); i++){

        session = clientes[i];
        find_it = ((session->getHost() == msg->getPacketUPD().address.host) &&
                   (session->getPort() == msg->getPacketUPD().address.port));

        if (find_it){res = 1; index = i;}
        else{res = 0;}


        logger->info("[UDPDispatcherSession::processSessions Map[%d] Session[%d]] dir active session[%d]==>([%d]:[%d]) remote dir client==>([%d]:[%d]) ::= res[%d]",
                     this->mapId,
                     this->sessionId,
                     i,
                     session->getHost(),
                     session->getPort(),
                     msg->getPacketUPD().address.host,
                     msg->getPacketUPD().address.port,
                     res);
    }

    if (find_it){
            if (msg->getTypeMsg() == TRAMA_QRY_DATASERVER){
                sendInfoDataSession(session->getPlayerId(), msg);
            }else if (msg->getTypeMsg() == TRAMA_SND_ORDER_TO_SERVER){
                msgType mType = msg->getMsgType();
                logger->info("[UDPDispatcherSession::procesSessions Map [%d] Session [%d]] Send Msg [%s] from client [%d] to client [%d]",
                             this->mapId,
                             this->sessionId,
                             mType.msg,
                             mType.originMsg,
                             mType.endMsg
                             );
                sendNotificationServerToDiffClients((const char *)mType.msg,mType.endMsg);
            }else if (msg->getTypeMsg() == TRAMA_TEST){
                sendPingToClient(msg, index);
            }else if (msg->getTypeMsg() == TRAMA_PONG){
                sendTimeQOSToClients(msg, index);
            }else if ((msg->getTypeMsg() == TRAMA_COMMAND) && (msg->getExitType().exitID == TYPE_COMMAND_EXIT)){
                logger->info("[UDPDispatcherSession::procesSessions Map [%d] Session [%d]] DELETING ACTIVE USER [%d]",
                             this->mapId,
                             this->sessionId,
                             msg->getExitType().idPlayer);
                deleteClientToSession(msg);
                actClientInformation(true);
            }else if ((msg->getTypeMsg() == TRAMA_COMMAND) && (msg->getShotType().shotID == TYPE_COMMAND_SHOOT)){
                logger->info("[UDPDispatcherSession::procesSessions Map [%d] Session [%d]] SHOOT ACTIVE USER [%d]",
                             this->mapId,
                             this->sessionId,
                             msg->getShotType().idPlayer);

                createNewActiveElement(msg);
                session->Run(msg);
                clientes[index]->setUDPSession(session);
                actClientInformation(true);

            }else{
                session->Run(msg);
                clientes[index]->setUDPSession(session);

                if ((msg->getTypeMsg() == TRAMA_COMMAND) && (msg->getMovementType().movementID == TYPE_COMMAND_MOVEMENT)){
                    checkActClientForMovement++;
                    if (checkActClientForMovement > 2){
                        actClientInformation(true);
                        checkActClientForMovement = 0;
                    }
                }
            }
    }

}

//MSG OF ELEMENT OF THE WORLD
EventMsg *UDPDispatcherSession::sendWorldStateToClient(EventMsg *msg, int more, int indexServData, DynamicEntity *dEntity){
        EventMsg *outputData = new EventMsg();
        outputData->setTypeMsg(TRAMA_GET_DATASERVER);
        outputData->setTramaSend(mem->getTimeStampServer());
        outputData->setTramaGet(indexServData);
        outputData->setMore(more);
        outputData->setNumTrazas(1);
        outputData->setPacketUDP(msg->getPacketUPD());
        outputData->setCRC16((uint16_t)0);
        outputData->setRemotePlayerType(dEntity->getDynamicEntityRPT());
        return outputData;
}

//MSG OF ELEMENT OF THE WORLD (1)
EventMsg *UDPDispatcherSession::sendWorldStateToClientSession(UDPSession *session, int more, int indexServData, DynamicEntity *dEntity){
        EventMsg *outputData = new EventMsg();
        outputData->setTypeMsg(TRAMA_GET_DATASERVER);
        outputData->setTramaSend(mem->getTimeStampServer());
        outputData->setTramaGet(indexServData);
        outputData->setMore(more);
        outputData->setNumTrazas(1);

        packetDataType pDT;
        pDT.address.host = session->getHost();
        pDT.address.port = SDL_SwapBE16(SDL_SwapBE16(session->getPort())+1);
        pDT.len = SIZE_MSG;
        pDT.maxlen = SIZE_MSG;
        pDT.status = 0;
        outputData->setPacketUDP(pDT);

        outputData->setCRC16((uint16_t)0);
        outputData->setRemotePlayerType(dEntity->getDynamicEntityRPT());
        return outputData;
}

//ACT DATA TO DIFF SESSION CLIENTS
void UDPDispatcherSession::processInfoSession(int index){
      bool DONE = true;

      try{

          long serverTimeStamp = 0;
          while(DONE){
             long data = SDL_GetTicks();
             long limit = mem->getSizeTimeServer() * SIZE_REMOTE_ELEMS * clientes.size();
             logger->debug("[UDPDispatcherSession::processInfoSession map [%d] session [%d]] TIME LIMIT FOR SENDING STATE OF [%d] ELEMENTS AND [%d] USERS is [%d]",
                           this->mapId,
                           this->sessionId,
                           SIZE_REMOTE_ELEMS,
                           clientes.size(),
                           limit);

            UDPSession *session = nullptr;

            for(int i=0; i<clientes.size(); i++){
                session = clientes[i];
                if (session != nullptr){
                    if (session->getPlayerId() == index){
                        if (session->ready()){
                            if (session->stateFlag()){
                                sendInfoDataSession(session);
                                ((UDPSession *)clientes[i])->setStateFlag(false);
                            }
                        }
                    }
                }
            }

        }
      }catch(...){
        logger->debug("[UDPDispatcherSession::processInputMsg] get exception");
      }
}

//SEND ACT. STATE OF THE WORLD
void UDPDispatcherSession::sendInfoDataSession(UDPSession *session){



    int SIZE_WORLD = mem->getEnemy_Lvl_1_Map().size() +
                    mem->getEnemy_Lvl_2_Map().size() +
                    mem->getEnemy_Lvl_3_Map().size() +
                    mem->getDynElem_Lvl_1_Map().size() +
                    mem->getDynElem_Lvl_2_Map().size() +
                    mem->getDynElem_Lvl_3_Map().size() +
                    mem->getRemPlayerMap().size() + 20; //tamanyo del mundo + overhead 20


    EventMsg **msgs = new EventMsg *[SIZE_WORLD];

    for(int i=0; i<SIZE_WORLD; i++){
        msgs[i] = new EventMsg();
    }

    int indexMsg = 0;

    std::map<int, DynamicEntity *>enemyOfLevel1 = mem->getEnemy_Lvl_1_Map();

    for(auto iterator = enemyOfLevel1.begin(); iterator != enemyOfLevel1.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClientSession(session, 1, indexMsg, dEntity));
        indexMsg++;
    }


    std::map<int, DynamicEntity *>enemyOfLevel2 = mem->getEnemy_Lvl_2_Map();

    for(auto iterator = enemyOfLevel2.begin(); iterator != enemyOfLevel2.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClientSession(session, 1, indexMsg, dEntity));
        indexMsg++;
    }

    std::map<int, DynamicEntity *>enemyOfLevel3 = mem->getEnemy_Lvl_3_Map();

    for(auto iterator = enemyOfLevel3.begin(); iterator != enemyOfLevel3.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClientSession(session, 1, indexMsg, dEntity));
        indexMsg++;
    }


    std::map<int, DynamicEntity *>DynOfLevel1 = mem->getDynElem_Lvl_1_Map();

    for(auto iterator = DynOfLevel1.begin(); iterator != DynOfLevel1.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClientSession(session, 1, indexMsg, dEntity));
        indexMsg++;
    }


    std::map<int, DynamicEntity *>DynOfLevel2 = mem->getDynElem_Lvl_2_Map();

    for(auto iterator = DynOfLevel2.begin(); iterator != DynOfLevel2.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClientSession(session, 1, indexMsg, dEntity));
        indexMsg++;
    }

    std::map<int, DynamicEntity *>DynOfLevel3 = mem->getDynElem_Lvl_3_Map();

    for(auto iterator = DynOfLevel3.begin(); iterator != DynOfLevel3.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClientSession(session, 1, indexMsg, dEntity));
        indexMsg++;
    }

    std::map<int, DynamicEntity *>RemPlayers = mem->getRemPlayerMap();


    for(auto iterator = RemPlayers.begin(); iterator != RemPlayers.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;

        msgs[indexMsg]->setMsg(sendWorldStateToClientSession(session, 1, indexMsg, dEntity));
        indexMsg++;
    }

    for(int data = 0; data < indexMsg; data++){
        sendMsgToOutputQueue(msgs[data]);
    }
}

//SEND ACT. STATE OF THE WORLD
void UDPDispatcherSession::sendInfoDataSession(int playerID, EventMsg *msg){

    int SIZE_WORLD = mem->getEnemy_Lvl_1_Map().size() +
                    mem->getEnemy_Lvl_2_Map().size() +
                    mem->getEnemy_Lvl_3_Map().size() +
                    mem->getDynElem_Lvl_1_Map().size() +
                    mem->getDynElem_Lvl_2_Map().size() +
                    mem->getDynElem_Lvl_3_Map().size() +
                    mem->getRemPlayerMap().size() + 20; //tamanyo del mundo + overhead 20



    EventMsg **msgs = new EventMsg *[SIZE_WORLD];

    for(int i=0; i<SIZE_WORLD; i++){
        msgs[i] = new EventMsg();
        msgs[i]->setPacketUDP(msg->getPacketUPD());
    }

    int indexMsg = 0;

    std::map<int, DynamicEntity *>enemyOfLevel1 = mem->getEnemy_Lvl_1_Map();

    for(auto iterator = enemyOfLevel1.begin(); iterator != enemyOfLevel1.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClient(msg, 1, (SIZE_WORLD - indexMsg), dEntity));
        indexMsg++;
    }


    std::map<int, DynamicEntity *>enemyOfLevel2 = mem->getEnemy_Lvl_2_Map();

    for(auto iterator = enemyOfLevel2.begin(); iterator != enemyOfLevel2.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClient(msg, 1, (SIZE_WORLD - indexMsg), dEntity));
        indexMsg++;
    }

    std::map<int, DynamicEntity *>enemyOfLevel3 = mem->getEnemy_Lvl_3_Map();

    for(auto iterator = enemyOfLevel3.begin(); iterator != enemyOfLevel3.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClient(msg, 1, (SIZE_WORLD - indexMsg), dEntity));
        indexMsg++;
    }


    std::map<int, DynamicEntity *>DynOfLevel1 = mem->getDynElem_Lvl_1_Map();

    for(auto iterator = DynOfLevel1.begin(); iterator != DynOfLevel1.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClient(msg, 1, (SIZE_WORLD - indexMsg), dEntity));
        indexMsg++;
    }


    std::map<int, DynamicEntity *>DynOfLevel2 = mem->getDynElem_Lvl_2_Map();

    for(auto iterator = DynOfLevel2.begin(); iterator != DynOfLevel2.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClient(msg, 1, (SIZE_WORLD - indexMsg), dEntity));
        indexMsg++;
    }

    std::map<int, DynamicEntity *>DynOfLevel3 = mem->getDynElem_Lvl_3_Map();

    for(auto iterator = DynOfLevel3.begin(); iterator != DynOfLevel3.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClient(msg, 1, (SIZE_WORLD - indexMsg), dEntity));
        indexMsg++;
    }

    std::map<int, DynamicEntity *>RemPlayers = mem->getRemPlayerMap();

    int indexRemotePlayer=3;

    for(auto iterator = RemPlayers.begin(); iterator != RemPlayers.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        msgs[indexMsg]->setMsg(sendWorldStateToClient(msg, 1, indexRemotePlayer, dEntity));
        indexMsg++;
        indexRemotePlayer--;
    }

    for(int data = 0; data < indexMsg; data++){
        sendMsgToOutputQueue(msgs[data]);
    }
}


void UDPDispatcherSession::processInputMsg(){

    try{
        while (!cQInput->isEmpty()){
            EventMsg *msg = cQInput->front();
            if (msg != nullptr){
                if (msg->getTypeMsg() != TRAMA_NULL){

                    remoteHostData rHD_1 = UtilsProtocol::parseRemoteHostData(msg->getPacketUPD());

                    //PROCESSING INPUT CLIENTS
                    if (msg->getTypeMsg() == TRAMA_SYNACK_SESSION){
                        playerDataType pDT = msg->getPlayerDataType();
                        if ((pDT.actMap == this->mapId) && (pDT.session == this->sessionId)){

                            logger->debug("[UDPDispatcherSession::processInputMsg Map[%d] Session[%d]] TRAMA_ID[%d] TRAMASEND[%d] TRAMAGET[%d] MSG_MAP [%d] MSG_SESSION[%d] REMOTE HOST (%s:%d)",
                                  this->mapId,
                                  this->sessionId,
                                  msg->getTypeMsg(),
                                  msg->getTramaSend(),
                                  msg->getTramaGet(),
                                  pDT.actMap,
                                  pDT.session,
                                  rHD_1.host,
                                  rHD_1.port
                                  );
                            EventMsg *response = setClientForSession(msg);
                            cQInput->pop();
                            sendMsgToOutput(response);
                            actClientInformation(true);
                            //cQOutput->push(response);

                        }

                    //PROCESSING INPUT COMMAND
                    }else if (msg->getTypeMsg() == TRAMA_COMMAND){
                        movementType mType = msg->getMovementType();
                        if ((mType.actMap == this->mapId) && (mType.session == this->sessionId)){
                            logger->debug("[UDPDispatcherSession::processInputMsg Map[%d] Session[%d]] MOVEMENT TRAMA_ID[%d] TRAMASEND[%d] TRAMAGET[%d] MSG_MAP [%d] MSG_SESSION[%d] REMOTE HOST (%s:%d)",
                                  this->mapId,
                                  this->sessionId,
                                  msg->getTypeMsg(),
                                  msg->getTramaSend(),
                                  msg->getTramaGet(),
                                  mType.actMap,
                                  mType.session,
                                  rHD_1.host,
                                  rHD_1.port
                                  );
                            processSessions(msg);
                            cQInput->pop();
                        }

                        exitType eType = msg->getExitType();
                        if ((eType.actMap == this->mapId) && (eType.session == this->sessionId)){
                            logger->debug("[UDPDispatcherSession::processInputMsg Map[%d] Session[%d]] QUIT TRAMA_ID[%d] TRAMASEND[%d] TRAMAGET[%d] MSG_MAP [%d] MSG_SESSION[%d] REMOTE HOST (%s:%d)",
                                  this->mapId,
                                  this->sessionId,
                                  msg->getTypeMsg(),
                                  msg->getTramaSend(),
                                  msg->getTramaGet(),
                                  eType.actMap,
                                  eType.session,
                                  rHD_1.host,
                                  rHD_1.port
                                  );
                            processSessions(msg);
                            cQInput->pop();
                        }

                        shotType sType = msg->getShotType();
                        if ((sType.actMap == this->mapId) && (sType.session == this->sessionId)){
                            logger->debug("[UDPDispatcherSession::processInputMsg Map[%d] Session[%d]] SHOT TRAMA_ID[%d] TRAMASEND[%d] TRAMAGET[%d] MSG_MAP [%d] MSG_SESSION[%d] REMOTE HOST (%s:%d)",
                                  this->mapId,
                                  this->sessionId,
                                  msg->getTypeMsg(),
                                  msg->getTramaSend(),
                                  msg->getTramaGet(),
                                  sType.actMap,
                                  sType.session,
                                  rHD_1.host,
                                  rHD_1.port
                                  );
                            processSessions(msg);
                            cQInput->pop();
                        }

                    //GET STATE OF SERVER
                    }else if (msg->getTypeMsg() == TRAMA_QRY_DATASERVER){
                        playerDataType pDT = msg->getPlayerDataType();
                        if ((pDT.actMap == this->mapId) && (pDT.session == this->sessionId)){
                            logger->debug("[UDPDispatcherSession::processInputMsg Map[%d] Session[%d]] TRAMA_ID[%d] TRAMASEND[%d] TRAMAGET[%d] MSG_MAP [%d] MSG_SESSION[%d] REMOTE HOST (%s:%d)",
                                  this->mapId,
                                  this->sessionId,
                                  msg->getTypeMsg(),
                                  msg->getTramaSend(),
                                  msg->getTramaGet(),
                                  pDT.actMap,
                                  pDT.session,
                                  rHD_1.host,
                                  rHD_1.port
                                  );
                            processSessions(msg);
                            cQInput->pop();
                        }

                    //MSG CLIENT TO CLIENT
                    }else if (msg->getTypeMsg() == TRAMA_SND_ORDER_TO_SERVER){
                        msgType mType = msg->getMsgType();
                        if ((mType.actMap == this->mapId) && (mType.session == this->sessionId)){
                           logger->debug("[UDPDispatcherSession::processInputMsg Map[%d] Session[%d]] MSG [%s] from CLIENT [%d] to CLIENT [%d]",
                                         this->mapId,
                                         this->sessionId,
                                         mType.msg,
                                         mType.originMsg,
                                         mType.endMsg
                                         );
                            processSessions(msg);
                            cQInput->pop();
                        }

                    //EVALUATE QOS OF CLIENT (SYNCHRONIZE SERVER-CLIENT)
                    }else if ((msg->getTypeMsg() == TRAMA_TEST) || (msg->getTypeMsg() == TRAMA_PONG)){
                        OrderType oType = msg->getOrderType();
                        if ((oType.actMap == this->mapId) && (oType.session == this->sessionId)){
                           logger->debug("[UDPDispatcherSession::processInputMsg Map[%d] Session[%d]] MSG [%d]",
                                         this->mapId,
                                         this->sessionId,
                                         msg->getTypeMsg()
                                         );
                           processSessions(msg);
                           cQInput->pop();
                        }
                    }
                }
            }
        }
    }catch(...){
        logger->debug("[UDPDispatcherSession::processInputMsg] get exception");
    }
}


void UDPDispatcherSession::sendMsgToOutput(EventMsg *msg){
    cQOutput_1->push(msg);
}

void UDPDispatcherSession::sendMsgToOutputQueue(EventMsg *msg){

    if (cQOutput_2->sizeQueue() <= MAX_SIZE_QUEUE){
        cQOutput_2->push(msg);
    }else if (cQOutput_3->sizeQueue() <= MAX_SIZE_QUEUE){
        cQOutput_3->push(msg);
    }else{
        cQOutput_4->push(msg);
    }
}




 void UDPDispatcherSession::Run(){
     try{
        while(true){
            pthread_t iThread = pthread_self();
            //logger->debug("[UDPDispatcherSession::Run Map[%d] Session[%d]] [%08x] **** INI",this->mapId,this->sessionId,iThread);
            processInputMsg();
            //SDL_Delay(100);
            //logger->debug("[UDPDispatcherSession::Run Map[%d] Session[%d]] [%08x] **** END",this->mapId,this->sessionId,iThread);
        }
     }catch(...){
         logger->debug("[UDPDispatcherSession::Run] get exception");
     }
 };


