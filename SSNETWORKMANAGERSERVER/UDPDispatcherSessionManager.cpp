#include "UDPDispatcherSessionManager.h"


void UDPDispatcherSessionManager::activeSessions(){

    logger->info("[UDPDispatcherSessionManager::activeSession] --> SESSIONS CREATED");

    hebra_1 = SDL_CreateThread(threadFunction,"Session_1",session_1);
    hebra_2 = SDL_CreateThread(threadFunction,"Session_2",session_2);


}

bool UDPDispatcherSessionManager::isClientConnected(EventMsg *msg, int typeTrama){
    bool findClient = false;

    int loop_1 = 0;
    int res = 0;
    logger->debug("[UDPDispatcherSessionManager::isClientConnected] evaluating input client [%d]",clientPackets.size());
    for(loop_1=0; ((loop_1<clientPackets.size()) && (!findClient)); loop_1++){
        if (clientPackets[loop_1]->getTypeMsg() < TRAMA_NULL){
            findClient = (
                       (clientPackets[loop_1]->getPacketUPD().address.host == msg->getPacketUPD().address.host) &&
                       (clientPackets[loop_1]->getPacketUPD().address.port == msg->getPacketUPD().address.port) &&
                       (clientPackets[loop_1]->getTypeMsg() == typeTrama)
                        );

            if (findClient){res = 1;}
            else{res = 0;}

            logger->debug("[UDPDispatcherSessionManager::isClientConnected] CLIENT REGISTERED(%d:%d)-[%d] == INPUT PACKET(%d:%d)-[%d] res [%d]",
                          clientPackets[loop_1]->getPacketUPD().address.host,
                          clientPackets[loop_1]->getPacketUPD().address.port,
                          clientPackets[loop_1]->getTypeMsg(),
                          msg->getPacketUPD().address.host,
                          msg->getPacketUPD().address.port,
                          typeTrama,
                          res);
        }
    }

    return findClient;
}


void UDPDispatcherSessionManager::processingOutputMsgToClients(){
    while(!cQ2->isEmpty()){
        EventMsg *msgUDP = cQ2->front();

        remoteHostData rHD = UtilsProtocol::parseRemoteHostData(msgUDP->getPacketUPD());

        logger->debug("[UDPDispatcherSessionManager::processingOutputMsgToClients] TRAMA_COMMAND OUTPUT_PACKET_[%02d] TRAMA_SEND [%d] TRAMA_GET [%d] SEND TO [%s]:[%d]",
                        msgUDP->getTypeMsg(),
                        msgUDP->getTramaSend(),
                        msgUDP->getTramaGet(),
                        rHD.host,
                        rHD.port
                        );

        nCUDP->sendMsgToClientUDP(msgUDP);
        cQ2->pop();
    }

}


void UDPDispatcherSessionManager::processingInputMsgsFromClients(){

        EventMsg *msgUDP = nCUDP->getMsgFromClientUDP();
        if (msgUDP->getTypeMsg() != TRAMA_NULL){
            remoteHostData rHD = UtilsProtocol::parseRemoteHostData(msgUDP->getPacketUPD());
            if (msgUDP->getTypeMsg() == TRAMA_QRY_CONECTION){
                   processInputConnections(msgUDP);
            }else if (msgUDP->getTypeMsg() == TRAMA_QRY_SESSION_LIST){
                   nCUDP->sendMsgToClientUDP(processQueryActiveSessions(msgUDP));
            }else if (msgUDP->getTypeMsg() == TRAMA_SYNACK_SESSION){
                    if (isClientConnected(msgUDP, TRAMA_QRY_CONECTION)){
                        processActivateSession(msgUDP);
                    }
            }else{
                    //if (isClientConnected(msgUDP, TRAMA_SYNACK_SESSION)){
                        //->MENSAJE DE LOG INPUT COMMAND
                        if (msgUDP->getTypeMsg() == TRAMA_COMMAND){

                            logger->debug("[UDPDispatcherSessionManager::processingInputMsgsFromClients] set TRAMA_COMMAND INPUT_PACKET_[%02d] TRAMA_SEND [%d] TRAMA_GET [%d] TO QUEUE Q1 [%s]:[%d]",
                                          msgUDP->getTypeMsg(),
                                          msgUDP->getTramaSend(),
                                          msgUDP->getTramaGet(),
                                          rHD.host,
                                          rHD.port
                                          );

                        }else if (msgUDP->getTypeMsg() == TRAMA_QRY_DATASERVER){
                            logger->debug("[UDPDispatcherSessionManager::processingInputMsgsFromClients] set TRAMA_QRY_DATASERVER INPUT_PACKET_[%02d] TRAMA_SEND [%d] TRAMA_GET [%d] TO QUEUE Q1 [%s]:[%d]",
                                          msgUDP->getTypeMsg(),
                                          msgUDP->getTramaSend(),
                                          msgUDP->getTramaGet(),
                                          rHD.host,
                                          rHD.port
                                          );
                        }
                        cQ1->push(msgUDP);
                    //}


            }
        }
};


void UDPDispatcherSessionManager::processActivateSession(EventMsg *ackSession){


    remoteHostData rHD = UtilsProtocol::parseRemoteHostData(ackSession->getPacketUPD());
    logger->debug("[SSNETWORKMANAGERSERVER::processActivateSession] activate session for input client [%s]:[%d]",rHD.host,rHD.port);

    bool found_it = false;
    int loop_1=0;

    for(loop_1=0; ((loop_1<clientPackets.size()) && (!found_it)); loop_1++){
        if (clientPackets[loop_1]->getTypeMsg() < TRAMA_NULL){
            found_it = (
                       (clientPackets[loop_1]->getPacketUPD().address.host == ackSession->getPacketUPD().address.host) &&
                       (clientPackets[loop_1]->getPacketUPD().address.port == ackSession->getPacketUPD().address.port) &&
                       (clientPackets[loop_1]->getTypeMsg() == TRAMA_QRY_CONECTION)
                        );
        }
    }

    if (found_it){
       loop_1--;
       EventMsg *inputMsg = clientPackets[loop_1];

       logger->debug("[SSNETWORKMANAGERSERVER::processActivateSession]REGISTED_CONNECTION: [%d] typeMsg [%d] tramaSend [%d] tramaGet [%d] ",loop_1,inputMsg->getTypeMsg(),inputMsg->getTramaSend(),inputMsg->getTramaSend());
       logger->debug("[SSNETWORKMANAGERSERVER::processActivateSession]SYNACK_CONECTION: typeMsg [%d] tramaSend [%d] tramaGet [%d] ",ackSession->getTypeMsg(),ackSession->getTramaSend(),ackSession->getTramaSend());

       if (inputMsg->getTypeMsg() == TRAMA_QRY_CONECTION){
           if ((ackSession->getTypeMsg() == TRAMA_SYNACK_SESSION) &&
              (inputMsg->getTramaSend() <= ackSession->getTramaSend()) &&
              (inputMsg->getTramaGet() <= ackSession->getTramaGet())){
                clientPackets[loop_1]->setMsg(ackSession);
                cQ1->push(ackSession);
           }else{
                logger->warn("[UDPDispatcherSessionManager::processActivateSession] DISCARD PACKET NOT SYNACK_SESSION OR TIMESTAMP NOT CORRECT (trama:[%d],send:[%d],get:[%d])-[%s]:[%d]",
                             ackSession->getTypeMsg(),
                             ackSession->getTramaSend(),
                             ackSession->getTramaGet(),
                             rHD.host,
                             rHD.port);
           }
       }else{
            logger->warn("[UDPDispatcherSessionManager::processActivateSession] DISCARD PACKET ACK SESSION CLIENT NOT CONNECTED [%s]:[%d]",rHD.host,rHD.port);
       }
       delete inputMsg;
    }else{
        logger->warn("[UDPDispatcherSessionManager::processActivateSession] DISCARD PACKET ACK SESSION CLIENT NOT CONNECTED [%s]:[%d]",rHD.host,rHD.port);
    }
}


//INDEPENDIENTEMENTE SI SE HA CONECTADO O NO, DEBEMOS DE DAR LA POSIBLIDAD DE CONSULTAR LAS SESIONES Y LOS MAPAS ACTIVOS.
EventMsg *UDPDispatcherSessionManager::processQueryActiveSessions(EventMsg *qryListTrama){

    remoteHostData rHD = UtilsProtocol::parseRemoteHostData(qryListTrama->getPacketUPD());

    logger->debug("[UDPDispatcherSessionManager::processQueryActiveSessions] return Available sessions for input client [%s]:[%d]",rHD.host,rHD.port);

    EventMsg *msgOutput = new EventMsg();

    msgOutput->setTypeMsg(TRAMA_GET_SESSION_LIST);
    msgOutput->setTramaGet(qryListTrama->getTramaGet()+1);
    msgOutput->setTramaSend(qryListTrama->getTramaSend());
    msgOutput->setMore(NOK);
    msgOutput->setNumTrazas(1);
    msgOutput->setPacketUDP(qryListTrama->getPacketUPD());

    listSessionAvailableType lSAT;

    lSAT.listSessionsID = TYPE_LIST_SESSION_ID;
    lSAT.map_1_id = session_1->getMapId();
    lSAT.session_1_1 = session_1->getSessionId();
    lSAT.num_player_ava_1_1 = session_1->getNumClients();
    lSAT.num_player_max_1_1 = session_1->getMaxClients();

    lSAT.session_1_2 = 0;
    lSAT.num_player_ava_1_2 = 0;
    lSAT.num_player_max_1_2 = 0;

    /*
    lSAT.session_1_2 = session_2->getSessionId();
    lSAT.num_player_ava_1_2 = session_2->getNumClients();
    lSAT.num_player_max_1_2 = session_2->getMaxClients();
    */

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

     remoteHostData rHD1 = UtilsProtocol::parseRemoteHostData(ackTrama->getPacketUPD());

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

            logger->debug("[UDPDispatcherSessionManager::processInputConnections] --> TYPEMSG [%d] SEND [%d] GET [%d] FREESOCKET [%d] (%s:%d)",
                          ackTrama->getTypeMsg(),ackTrama->getTramaSend(),ackTrama->getTramaGet(),freeSocketID,rHD1.host,rHD1.port);

            if (freeSocketID != -1){
                bool found_it = false;
                //new client!
                for(int loop_1=0; ((loop_1<clientPackets.size()) && (!found_it)); loop_1++){
                    if (clientPackets[loop_1]->getTypeMsg()<=TRAMA_NULL){
                        //UDPpacket *pack_1 = clientPackets[loop_1]->getPacketUPD();
                        //UDPpacket *pack_2 = ackTrama->getPacketUPD();

                        logger->debug("[UDPDispatcherSessionManager::processInputConnections] REGISTERED_CLIENT[%d] (%d:%d) ACK_PACKET (%d:%d)",
                                      loop_1,
                                      clientPackets[loop_1]->getPacketUPD().address.host,
                                      clientPackets[loop_1]->getPacketUPD().address.port,
                                      ackTrama->getPacketUPD().address.host,
                                      ackTrama->getPacketUPD().address.port
                                      );

                        //remoteHostData rHD1 = UtilsProtocol::parseRemoteHostData(pack_1);
                        //remoteHostData rHD2 = UtilsProtocol::parseRemoteHostData(pack_2);
                        //logger->debug("[SSNETWORKMANAGER::establishCommunication] -->  free Packet [%s:%d] - Input Packet [%s:%d]",rHD1.host,rHD1.port,rHD2.host,rHD2.port);

                        found_it = (
                                    (clientPackets[loop_1]->getPacketUPD().address.host == ackTrama->getPacketUPD().address.host) &&
                                    (clientPackets[loop_1]->getPacketUPD().address.port == ackTrama->getPacketUPD().address.port)
                                    );
                    }
                }

                if (!found_it){
                    freeSocket[freeSocketID] = false;


                    clientPackets[freeSocketID]->setMsg(ackTrama);

                    logger->debug("[UDPDispatcherSessionManager::processInputConnections] REGISTER TYPE [%d] SEND [%d] GET [%d]",
                                  clientPackets[freeSocketID]->getTypeMsg(),
                                  clientPackets[freeSocketID]->getTramaSend(),
                                  clientPackets[freeSocketID]->getTramaGet());

                    //RESPUESTA AFIRMATIVA (RESPUESTA ACK SI!)
                    EventMsg *answerACK = generatingACKPackets(1, 1, OK, ackTrama->getPacketUPD());
                    nCUDP->sendMsgToClientUDP(answerACK);

                    logger->debug("[UDPDispatcherSessionManager::processInputConnections] ACK PACKET ACCEPTED [%s]:[%d]",rHD1.host, rHD1.port);
                    delete answerACK;

                }else{
                    //SOLICITUD DE CONEXION DE PAQUETE CONECTADO Y DADO DE ALTA PREVIAMENTE (SE DESCARTA)
                    logger->warn("[UDPDispatcherSessionManager::processInputConnections] ACK PACKET FROM CLIENT [%s]:[%d]. PREVIOUSLY ACCEPTED. DISCART PACKET",rHD1.host, rHD1.port);
                }

            //NO HA ENCONTRADO ESPACIO LIBRE (RESPUESTA ACK NO!)
            }else{
                EventMsg *answerACK = generatingACKPackets(1, 1, NOK, ackTrama->getPacketUPD());
                nCUDP->sendMsgToClientUDP(answerACK);
                logger->debug("[UDPDispatcherSessionManager::processInputConnections] ACK PACKET REJECTED [%s]:[%d]",rHD1.host, rHD1.port);
                delete answerACK;
            }
        }
}; //--> QRY_CONECTION; CONECTION


EventMsg *UDPDispatcherSessionManager::generatingACKPackets(int tramaSend, int tramaGet, int _OK, packetDataType packet){

    EventMsg *outputMsg = new EventMsg(TRAMA_GET_CONECTION,tramaSend,tramaGet,NOK,NOK,NOK);
    outputMsg->setPacketUDP(packet);
    answerType aType;

    aType.type_trama = TYPE_MSG_ANSWER_CONNECTION;
    aType.trama =   tramaGet;
    aType.command = TRAMA_QRY_CONECTION;
    aType.result = OK;
    outputMsg->setAnswerType(aType);

    return outputMsg;
};


