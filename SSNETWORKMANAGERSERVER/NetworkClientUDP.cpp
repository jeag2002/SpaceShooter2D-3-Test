#include "NetworkClientUDP.h"

//http://stackoverflow.com/questions/24160139/udp-echo-server-not-receiving-on-client

void NetworkClientUDP::initCommunicationUDP(){



    if (SDLNet_Init() < 0){
        logger->error("[SSNETWORKMANAGERSERVER::initCommunicationUDP] Failed SDLNet_Int [%s]",SDLNet_GetError());
        exit(-1);
    }

    serverSocket = SDLNet_UDP_Open(LOCAL_PORT);

    if (serverSocket==NULL){
        logger->error("[SSNETWORKMANAGERSERVER::initCommunicationUDP] Error creating serverSocket [%s]",serverSocket);
        exit(-1);
    }else{
        logger->debug("[SSNETWORKMANAGERSERVER::initCommunicationUDP] listen from 0.0.0.0/[%d]",LOCAL_PORT);
    }

    socketSet = SDLNet_AllocSocketSet(MAX_CLIENT);
    if(socketSet == NULL){
        logger->error("[SSNETWORKMANAGERSERVER::initCommunicationUDP] Error Allocating [%d] Sockets SDLNet_Int [%s]",MAX_CLIENT,SDLNet_GetError());
        exit(-1);
    }else{
        logger->debug("[SSNETWORKMANAGERSERVER::initCommunicationUDP] [%d] sockets created",MAX_CLIENT);
    }

    int used = SDLNet_UDP_AddSocket(socketSet, serverSocket);
    if (used == -1){
        logger->error("[SSNETWORKMANAGERSERVER::initCommunicationUDP] addSocket [%s]",SDLNet_GetError());
        exit(-1);
    }

    packet = SDLNet_AllocPacket(BUFFER_SIZE);
    if (!packet){
        logger->error("[SSNETWORKMANAGERSERVER::initCommunicationUDP] cannot allocate buffer size [%s]",BUFFER_SIZE);
        exit(-1);
    }

    logger->info("[SSNETWORKMANAGERSERVER::initCommunicationUDP] UDP CONFIGURATION DONE!");


};

/*
PROTOCOL FOR ESTABLISHING A UDP CHANNEL COMMUNICATION. (SERVER SIDE)
1)GET ACK PACKET FROM CLIENT         (indexDataSend(1); indexDataGet(0))
2)SEND CONFIRMATION PACKET TO CLIENT (indexDataSend(1); indexDataGet(1))
*/


/*
EventMsg *NetworkClientUDP::evaluatingIncomingPackets(){

    EventMsg *eventMsg = new EventMsg();

    int numActiveSockets = SDLNet_CheckSockets(socketSet,0);
    if (numActiveSockets != 0){
    }

    int serverSocketActivity = SDLNet_SocketReady(serverSocket);
    if (serverSocketActivity > 0){
       EventMsg *msgUDP = getMsgFromClientUDP();
       if (msgUDP->getTypeMsg() != TRAMA_NULL){
           eventMsg->setMsg(msgUDP);
           if (eventMsg->getTypeMsg() == TRAMA_QRY_CONECTION){
              establishCommunicationUDP(eventMsg);
           }
       }
    }
    return eventMsg;
}


void NetworkClientUDP::establishCommunicationUDP(EventMsg *ackTrama){

    if ((ackTrama->getTypeMsg() == TRAMA_QRY_CONECTION) &&
        (ackTrama->getTramaSend() == indexTramaSend) &&
        (ackTrama->getTramaGet() == indexTramaGet)){

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
            UDPpacket *packet = ackTrama->getPacketUPD();
            for(int loop_1=0; ((loop_1<MAX_CLIENT) && (!found_it)); loop_1++){
                if (clientPackets[loop_1]!=NULL){
                    found_it = (clientPackets[loop_1]->address.host == packet->address.host);
                }
            }

            if (!found_it){
                freeSocket[freeSocketID] = false;
                clientPackets[freeSocketID] = packet;
                //RESPUESTA AFIRMATIVA (RESPUESTA ACK SI!)
                EventMsg *answerACK = generatingACKPackets(indexTramaSend, indexTramaGet+1, OK, packet);
                sendMsgToClientUDP(answerACK);
                //indexTramaGet++;

            }else{
            //SOLICITUD DE CONEXION DE PAQUETE CONECTADO Y DADO DE ALTA PREVIAMENTE (SE DESCARTA)
                logger->warn("[SSNETWORKMANAGERSERVER::establishCommunication] ACK PACKET FROM CLIENT [%d]:[%d]. PREVIOUSLY ACCEPTED. DISCART PACKET",packet->address.host, packet->address.port);
            }

        //NO HA ENCONTRADO ESPACIO LIBRE (RESPUESTA ACK NO!)
        }else{
            EventMsg *answerACK = generatingACKPackets(indexTramaSend, indexTramaGet+1, NOK, packet);
            sendMsgToClientUDP(answerACK);
        }
    }
};

EventMsg *NetworkClientUDP::generatingACKPackets(int tramaSend, int tramaGet, int _OK, UDPpacket *packet){

    EventMsg *outputMsg = new EventMsg(TRAMA_GET_CONECTION,tramaSend,tramaGet,NOK,NOK,NOK,packet);
    answerType aType;

    aType.type_trama = TYPE_MSG_ANSWER_CONNECTION;
    aType.trama =   tramaGet;
    aType.command = TRAMA_QRY_CONECTION;
    aType.result = OK;
    outputMsg->setAnswerType(aType);

    return outputMsg;
};
*/


//send one message to REMOTE
void NetworkClientUDP::sendMsgToClientUDP(EventMsg *msg){

    char *data = msg->marshallMsg();
    int size_data = strlen(buffer)+1;
    clearBuffer();

    packet = msg->getPacketUPD();

    sprintf(buffer,"%s",data);
    packet->len = size_data;
    for(int i=0;i<packet->len;i++){packet->data[i]=buffer[i];}

    if (enabledCompression){
        unsigned char *dataCompression = cP->CompressionData((char *)packet->data,packet->len);
        int size_after_dataCompression = strlen((const char *)dataCompression);
        logger->warn("[SSNETWORKMANAGER::sendMsgToServerUPD] --> size_data_before_compression [%d] size_data_after_compression [%d]",packet->len,size_after_dataCompression);
    }

    if (SDLNet_UDP_Send(serverSocket,-1,packet) == 0){
        logger->warn("[SSNETWORKMANAGER::sendMsgToServerUDP] --> UDP DATA NOT SEND! [%s]", SDLNet_GetError());
    }else{
        logger->warn("[SSNETWORKMANAGER::sendMsgToServerUDP] --> BUFFER SEND [%s] size [%d]",packet->data, packet->len);
    }

};

//receive one message from REMOTE.
EventMsg *NetworkClientUDP::getMsgFromClientUDP(){

    bool DONE = false;

    EventMsg *returnMsg = new EventMsg();

    long initialMark = SDL_GetTicks();

    while(!DONE){

          if (SDLNet_UDP_Recv(serverSocket, packet)){
            std::string data((char *)packet->data);
            std::string msg = data.substr(0,128);
            logger->debug("[NetworkClientUDP::getMsgFromClientUDP] getMsg [%s]",msg.c_str());
            returnMsg->unmarshallMsg((const char *)msg.c_str());
            returnMsg->setPacketUPD(packet);

            DONE = true;
          }

          if (!DONE){
            long DIFF = SDL_GetTicks()-initialMark;
            logger->warn("[SSNETWORKMANAGER::getMsgFromServerUDP] --> SOCKET INACTIVE DURING [%d] MS", DIFF);
            if (DIFF >= MAX_DELAY){
                DONE = true;
            }
          }
    }

    return returnMsg;

};


