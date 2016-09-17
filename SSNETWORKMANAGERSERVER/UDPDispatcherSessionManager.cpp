#include "UDPDispatcherSessionManager.h"


void UDPDispatcherSessionManager::activeSessions(){
    pthread_t hebra_1;
    pthread_t hebra_2;

    logger->info("[UDPDispatcherSessionManager::activeSession] --> SESSIONS CREATED");

    pthread_create(&hebra_1,NULL,execute_RunTaskUDPSession,session_1);
    pthread_create(&hebra_2,NULL,execute_RunTaskUDPSession,session_2);

    pthread_join(hebra_1,0);
    pthread_join(hebra_2,0);
}

void UDPDispatcherSessionManager::processingInputMsgsFromClients(){

    int numActiveSockets = SDLNet_CheckSockets(nCUDP->getSocketSet(),0);
    if (numActiveSockets != 0){
    }

    int serverSocketActivity = SDLNet_SocketReady(nCUDP->getUDPSocket());
    if (serverSocketActivity > 0){

       EventMsg *msgUDP = nCUDP->getMsgFromClientUDP();
       if (msgUDP->getTypeMsg() != TRAMA_NULL){

           if (msgUDP->getTypeMsg() == TRAMA_QRY_CONECTION){
               processInputConnections(msgUDP);
           }else if (msgUDP->getTypeMsg() == TRAMA_QRY_SESSION_LIST){
               nCUDP->sendMsgToClientUDP(processQueryActiveSessions(msgUDP));
           }else if (msgUDP->getTypeMsg() == TRAMA_SYNACK_SESSION){
                EventMsg *output = processActivateSession(msgUDP);
                if (output->getTypeMsg() != TRAMA_NULL){
                    nCUDP->sendMsgToClientUDP(output);
                }
           }else{

           }
       }
    }
};

EventMsg *UDPDispatcherSessionManager::processActivateSession(EventMsg *ackSession){

    EventMsg *msgOutput = new EventMsg();
    logger->debug("[UDPDispatcherSessionManager::processActivateSession] activate session for input client [%d]:[%d]",ackSession->getPacketUPD()->address.host,ackSession->getPacketUPD()->address.port);

    bool found_it = false;
    int loop_1=0;

    for(loop_1=0; ((loop_1<MAX_CLIENT) && (!found_it)); loop_1++){
        if (clientPackets[loop_1]!=NULL){
            found_it = (clientPackets[loop_1]->getPacketUPD()->address.host == ackSession->getPacketUPD()->address.host);
        }
    }

    if (found_it){
       EventMsg *inputMsg = clientPackets[loop_1];

       if (inputMsg->getTypeMsg() == TRAMA_QRY_CONECTION){
           if ((ackSession->getTypeMsg() == TRAMA_SYNACK_CONECTION) &&
              (inputMsg->getTramaSend() <= ackSession->getTramaSend()) &&
              (inputMsg->getTramaGet() <= ackSession->getTramaGet())){
                clientPackets[loop_1]->setMsg(ackSession);
                cQ1->push(ackSession);

                bool getAnswer = false;

                while(!getAnswer){
                      if (!cQ2->isEmpty()){
                          msgOutput->setMsg(cQ2->front());
                          if ((msgOutput->getTypeMsg() == TRAMA_ACK_SESSION) &&
                              (msgOutput->getPacketUPD()->address.host == ackSession->getPacketUPD()->address.host) &&
                              (msgOutput->getPacketUPD()->address.port == ackSession->getPacketUPD()->address.port)){
                                  cQ2->pop();
                                  getAnswer = true;
                                  clientPackets[loop_1]->setMsg(ackSession);
                              }
                      }
                }
           }
       }
    }else{
        logger->warn("[UDPDispatcherSessionManager::processActivateSession] discard input packet not connect [%d]:[%d]",ackSession->getPacketUPD()->address.host,ackSession->getPacketUPD()->address.port);
    }
    return msgOutput;

}


//INDEPENDIENTEMENTE SI SE HA CONECTADO O NO, DEBEMOS DE DAR LA POSIBLIDAD DE CONSULTAR LAS SESIONES Y LOS MAPAS ACTIVOS.
EventMsg *UDPDispatcherSessionManager::processQueryActiveSessions(EventMsg *qryListTrama){

    logger->debug("[UDPDispatcherSessionManager::processQueryActiveSessions] return Available sessions for input client [%d]:[%d]",qryListTrama->getPacketUPD()->address.host,qryListTrama->getPacketUPD()->address.port);

    EventMsg *msgOutput = new EventMsg();

    msgOutput->setTypeMsg(TRAMA_GET_SESSION_LIST);
    msgOutput->setTramaGet(qryListTrama->getTramaGet()+1);
    msgOutput->setTramaSend(qryListTrama->getTramaSend());
    msgOutput->setMore(NOK);
    msgOutput->setNumTrazas(1);
    msgOutput->setPacketUPD(qryListTrama->getPacketUPD());

    listSessionAvailableType lSAT;

    lSAT.listSessionsID = TYPE_LIST_SESSION_ID;
    lSAT.map_1_id = session_1->getMapId();
    lSAT.session_1_1 = session_1->getSessionId();
    lSAT.num_player_ava_1_1 = session_1->getNumClients();
    lSAT.num_player_max_1_1 = session_1->getMaxClients();

    lSAT.session_1_2 = session_2->getSessionId();
    lSAT.num_player_ava_1_2 = session_2->getNumClients();
    lSAT.num_player_max_1_2 = session_2->getMaxClients();

    lSAT.map_2_id = 0;
    lSAT.session_2_1 = 0;
    lSAT.num_player_ava_2_1 = 0;
    lSAT.num_player_max_2_1 = 0;

    lSAT.session_2_2 = 0;
    lSAT.num_player_ava_2_2 = 0;
    lSAT.num_player_max_2_2 = 0;

    msgOutput->setListSessionAvaliableType(lSAT);

    return msgOutput;
};



void UDPDispatcherSessionManager::processInputConnections(EventMsg *ackTrama){

     if ((ackTrama->getTypeMsg() == TRAMA_QRY_CONECTION) &&
        (ackTrama->getTramaSend() == 1) &&
        (ackTrama->getTramaGet() == 0)){

            int freeSocketID = -1;
            //Get free space array of packets.
            for(int loop=0; loop<MAX_CLIENT; loop++){
                if (freeSocket[loop] == true){
                    freeSocketID = loop;
                    break;
                }
            }

            if (freeSocketID != -1){
                bool found_it = false;
                //new client!
                for(int loop_1=0; ((loop_1<MAX_CLIENT) && (!found_it)); loop_1++){
                    if (clientPackets[loop_1]!=NULL){
                        found_it = (clientPackets[loop_1]->getPacketUPD()->address.host == ackTrama->getPacketUPD()->address.host);
                    }
                }

                if (!found_it){
                    freeSocket[freeSocketID] = false;
                    clientPackets[freeSocketID]->setMsg(ackTrama);
                    //RESPUESTA AFIRMATIVA (RESPUESTA ACK SI!)
                    EventMsg *answerACK = generatingACKPackets(1, 1, OK, ackTrama->getPacketUPD());
                    nCUDP->sendMsgToClientUDP(answerACK);

                }else{
                    //SOLICITUD DE CONEXION DE PAQUETE CONECTADO Y DADO DE ALTA PREVIAMENTE (SE DESCARTA)
                    logger->warn("[SSNETWORKMANAGERSERVER::establishCommunication] ACK PACKET FROM CLIENT [%d]:[%d]. PREVIOUSLY ACCEPTED. DISCART PACKET",ackTrama->getPacketUPD()->address.host, ackTrama->getPacketUPD()->address.port);
                }

            //NO HA ENCONTRADO ESPACIO LIBRE (RESPUESTA ACK NO!)
            }else{
                EventMsg *answerACK = generatingACKPackets(1, 1, NOK, ackTrama->getPacketUPD());
                nCUDP->sendMsgToClientUDP(answerACK);
            }
        }
}; //--> QRY_CONECTION; CONECTION


EventMsg *UDPDispatcherSessionManager::generatingACKPackets(int tramaSend, int tramaGet, int _OK, UDPpacket *packet){

    EventMsg *outputMsg = new EventMsg(TRAMA_GET_CONECTION,tramaSend,tramaGet,NOK,NOK,NOK,packet);
    answerType aType;

    aType.type_trama = TYPE_MSG_ANSWER_CONNECTION;
    aType.trama =   tramaGet;
    aType.command = TRAMA_QRY_CONECTION;
    aType.result = OK;
    outputMsg->setAnswerType(aType);

    return outputMsg;
};


