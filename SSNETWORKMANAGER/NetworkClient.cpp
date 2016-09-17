#include "NetworkClient.h"

//configura SDL_net, comunicacion cliente-servidor.
void NetworkClient::initCommunication(){

   if (SDLNet_Init()< 0){
        logger->warn("[SSNETWORKMANAGER::initConnectionTCP] --> fallo inicializacion SDLNET [%s]",SDLNet_GetError());
        exit(-1);
    }

    socketSet = SDLNet_AllocSocketSet(1);

    if (socketSet == NULL){
      logger->warn("[SSNETWORKMANAGER::initConnectionTCP] --> fallo socket set SDLNET [%s]",SDLNet_GetError());
      exit(-1);
    }

    int hostResolved = SDLNet_ResolveHost(&serverIP,HOST,PORT);

    if (hostResolved == -1){
        logger->warn("[SSNETWORKMANAGER::initConnectionTCP] --> server hostname [%s]",SDLNet_GetError());
        exit(-1);
    }

    if ((host = SDLNet_ResolveIP(&serverIP)) == NULL){
        logger->warn("[SSNETWORKMANAGER::initConnectionTCP] --> resolve IP [%s]",SDLNet_GetError());
        exit(-1);
    }

    clientSocket = SDLNet_TCP_Open(&serverIP);

    if (!clientSocket){
        logger->warn("[SSNETWORKMANAGER::initConnectionTCP] --> create clientSocket [%s]",SDLNet_GetError());
        exit(-1);
    }

    SDLNet_TCP_AddSocket(socketSet,clientSocket);
    activeSockets = SDLNet_CheckSockets(socketSet,5000);
    gotServerResponse = SDLNet_SocketReady(clientSocket);

    logger->info("[SSNETWORKMANAGER::initConnectionTCP] --> TCP Configuration DONE! (CLIENT)");

};


//establece primera comunicacion entre cliente-servidor.
void NetworkClient::establishCommunication(){

    EventMsg *responseSYNACK = getMsgFromServer();
    sendMsgToServer(new EventMsg(TRAMA_QRY_CONECTION,indexTrama,indexTrama,0,0,(uint16_t)0));
    EventMsg *response = getMsgFromServer();
    if (response->getTypeMsg() == TRAMA_GET_CONECTION){
        answerType aType = response->getAnswerType();
        if (aType.result == OK){
            logger->info("[SSNETWORKMANAGER::establishCommunicationTCP] --> ACK SERVER ESTABLISHED");
        }else{
            logger->info("[SSNETWORKMANAGER::establishCommunicationTCP] --> ACK SERVER FAILED (CANNOT ACCEPT MORE CLIENTS)");
        }
    }else if(response->getTypeMsg() == TRAMA_NULL){
        logger->warn("[SSNETWORKMANAGER::establishCommunicationTCP] --> ACK SERVER FAILED (CONNECTION FAILED)");
        SDLNet_TCP_Close(clientSocket);
        SDLNet_Quit();
        exit(1);
    }
};

//establecer Active Sessions
void NetworkClient::getListActiveSessions(){
    sendMsgToServer(new EventMsg(TRAMA_QRY_SESSION_LIST,indexTrama,indexTrama,0,0,(uint16_t)0));
    EventMsg *response = getMsgFromServer();
    if (response->getTypeMsg() == TRAMA_GET_SESSION_LIST){
        listSessionAvailableType lSAType = response->getListSessionAvailableType();
        logger->info("[SSNETWORKMANAGER::LISTACTIVESESSION] mapa_ID [%d] session [%d] max_Players [%d] act_Players[%d]",lSAType.map_1_id,lSAType.session_1_1,lSAType.num_player_max_1_1,lSAType.num_player_ava_1_1);
        logger->info("[SSNETWORKMANAGER::LISTACTIVESESSION] mapa_ID [%d] session [%d] max_Players [%d] act_Players[%d]",lSAType.map_1_id,lSAType.session_1_2,lSAType.num_player_max_1_2,lSAType.num_player_ava_1_2);
        logger->info("[SSNETWORKMANAGER::LISTACTIVESESSION] mapa_ID [%d] session [%d] max_Players [%d] act_Players[%d]",lSAType.map_2_id,lSAType.session_2_1,lSAType.num_player_max_2_1,lSAType.num_player_ava_2_1);
        logger->info("[SSNETWORKMANAGER::LISTACTIVESESSION] mapa_ID [%d] session [%d] max_Players [%d] act_Players[%d]",lSAType.map_2_id,lSAType.session_2_2,lSAType.num_player_max_2_2,lSAType.num_player_ava_2_2);
    }else if (response->getTypeMsg() == TRAMA_NULL){
        logger->warn("[SSNETWORKMANAGER::LISTACTIVESESSION] --> CANNOT GET LIST. CLOSE SOCKET");
        //SDLNet_TCP_Close(clientSocket);
        //SDLNet_Quit();
        //exit(1);
    }
};

//establecer Remote Players.
EventMsg *NetworkClient::getRemoteIdPlayer(){

    EventMsg *inputMsg = new EventMsg(TRAMA_SYNACK_SESSION,indexTrama,indexTrama,0,0,(uint16_t)0);

    playerDataType pDTypeInput;
    pDTypeInput.playerDataID = TYPE_PLAYER_INI_SESSION_ID;
    pDTypeInput.idPlayer = 0;
    pDTypeInput.actMap = 1;
    pDTypeInput.session = 1;
    pDTypeInput.typeID = 200;
    pDTypeInput.lvl = 1;
    pDTypeInput.x_pos = 0.0f;
    pDTypeInput.y_pos = 0.0f;
    pDTypeInput.width = 64;
    pDTypeInput.heigth = 64;

    logger->debug("[SSNETWORKMANAGER::GETREMOTEIDPLAYER] QUERY REMOTE IDPLAYER [%d] TYPE [%d] FOR MAP [%d] SESSION [%d]",pDTypeInput.idPlayer,pDTypeInput.typeID,pDTypeInput.actMap,pDTypeInput.session);

    inputMsg->setPlayerDataType(pDTypeInput);

    sendMsgToServer(inputMsg);
    EventMsg *response = getMsgFromServer();

    return response;
};


void NetworkClient::sendMsgToServer(EventMsg *msg){
    //SDLNet_TCP_Send(clientSocket, (void *)msg->marshallMsg(), strlen(msg->marshallMsg())+1);
    char *bufferSend = msg->marshallMsg();
    int bufferSendSize = strlen(buffer) + 1;
    logger->debug("SSNETWORKMANAGER::MSGTOSERVER sndMsg --> [%s] size [%d]",bufferSend,bufferSendSize);
    int datasend = SDLNet_TCP_Send(clientSocket, (void *)bufferSend, bufferSendSize);
    logger->debug("SSNETWORKMANAGER::MSGTOSERVER sndMsg --> [%s] size [%d] data send[%d]",bufferSend,bufferSendSize,datasend);
    if (bufferSendSize > datasend){
        logger->debug("SSNETWORKMANAGER::MSGTOSERVER ERROR [%d]",SDLNet_GetError());
    }

}


EventMsg **NetworkClient::unMarsharMsgsServer(const char *buffer){

    EventMsg **eventMsgs = new EventMsg *[NUM_MSGS];
    for(int i=0; i<NUM_MSGS; i++){
        eventMsgs[i] = new EventMsg();
    }

    std::string bufferStr(buffer);

    if (bufferStr.length() == BUFFER_SIZE){
        std::string msgStr1 = bufferStr.substr(0,128);
        std::string msgStr2 = bufferStr.substr(128,128);
        std::string msgStr3 = bufferStr.substr(256,128);
        std::string msgStr4 = bufferStr.substr(385,128);

        EventMsg *msg_1 = new EventMsg(); msg_1->unmarshallMsg(msgStr1.c_str());
        EventMsg *msg_2 = new EventMsg(); msg_2->unmarshallMsg(msgStr2.c_str());
        EventMsg *msg_3 = new EventMsg(); msg_3->unmarshallMsg(msgStr3.c_str());
        EventMsg *msg_4 = new EventMsg(); msg_4->unmarshallMsg(msgStr4.c_str());

        eventMsgs[0]->setMsg(msg_1);
        eventMsgs[1]->setMsg(msg_2);
        eventMsgs[2]->setMsg(msg_3);
        eventMsgs[3]->setMsg(msg_4);
    }

    return eventMsgs;
}



EventMsg **NetworkClient::getMsgsFromServer(){

    EventMsg **eventMsgs = new EventMsg *[NUM_MSGS];
    for(int i=0; i<NUM_MSGS; i++){
        eventMsgs[i] = new EventMsg();
    }

    bool DONE = false;

    int initialMark = SDL_GetTicks();

    while(!DONE){
        int socketActive = SDLNet_CheckSockets(socketSet,0);
        if (socketActive != 0){

                int messageFromServer = SDLNet_SocketReady(clientSocket);
                if (messageFromServer != 0){
                    clearBuffer();
                    int awaiting_buff =  strlen(buffer)+1;
                    int buffer_int = SDLNet_TCP_Recv(clientSocket, buffer, BUFFER_SIZE);
                    if (buffer_int > 0){
                        buffer[buffer_int] = 0;
                        logger->debug("SSNETWORKMANAGER::MSGFROMSERVER getMsg --> [%s] size expected [%d] size get[%d]",buffer, awaiting_buff, buffer_int);
                        if ((buffer_int >= awaiting_buff) && (buffer_int >= 26) && (buffer_int <= BUFFER_SIZE)){
                            eventMsgs = unMarsharMsgsServer((const char *)buffer);
                        }
                        DONE = true;
                    }else{
                        logger->warn("SSNETWORKMANAGER::MSGFROMSERVER Error [%s]",SDLNet_GetError());
                        SDLNet_TCP_Close(clientSocket);
                        exit(1);
                        DONE = true;
                    }

                }else{
                    logger->warn("[SSNETWORKMANAGER::MSGFROMSERVER] getMsg --> SERVER SOCKET SEND MSG OF 0 BYTES");
                }
        }else{
          logger->warn("[SSNETWORKMANAGER::MSGFROMSERVER] getMsg --> SOCKET SET IS NOT ACTIVE");
        }

        int diff = SDL_GetTicks()-initialMark;

        if (!DONE){
            logger->warn("[SSNETWORKMANAGER::MSGFROMSERVER] --> SOCKET INACTIVE DURING [%d] MS", diff);
            if (diff > 500){
                DONE = true;
            }
        }
    }

    return eventMsgs;
}


EventMsg *NetworkClient::getMsgFromServer(){

    EventMsg *eMsg = new EventMsg();
    char bufferAux[128];
    int data_rev=0;

    bool DONE = false;

    int initialMark = SDL_GetTicks();

    while(!DONE){
        int socketActive = SDLNet_CheckSockets(socketSet,0);
        if (socketActive != 0){

                int messageFromServer = SDLNet_SocketReady(clientSocket);
                if (messageFromServer != 0){
                    clearBuffer();
                    int awaiting_buff =  strlen(buffer)+1;
                    int buffer_int = SDLNet_TCP_Recv(clientSocket, buffer, 512);
                    if (buffer_int > 0){
                        buffer[buffer_int] = 0;
                        logger->debug("SSNETWORKMANAGER::MSGFROMSERVER getMsg --> [%s] size expected [%d] size get[%d]",buffer, awaiting_buff, buffer_int);
                        if ((buffer_int >= awaiting_buff) && (buffer_int >= 26) && (buffer_int <= 512 )){
                            eMsg->unmarshallMsg((const char *)buffer);
                        }
                        DONE = true;
                    }else{
                        logger->warn("SSNETWORKMANAGER::MSGFROMSERVER Error [%s]",SDLNet_GetError());
                        SDLNet_TCP_Close(clientSocket);
                        exit(1);
                        DONE = true;
                    }

                }else{
                    logger->warn("[SSNETWORKMANAGER::MSGFROMSERVER] getMsg --> SERVER SOCKET SEND MSG OF 0 BYTES");
                }
        }else{
          logger->warn("[SSNETWORKMANAGER::MSGFROMSERVER] getMsg --> SOCKET SET IS NOT ACTIVE");
        }

        int diff = SDL_GetTicks()-initialMark;

        if (!DONE){
            logger->warn("[SSNETWORKMANAGER::MSGFROMSERVER] --> SOCKET INACTIVE DURING [%d] MS", diff);
            if (diff > 500){
                DONE = true;
            }
        }

    }

    return eMsg;
}


//cerrar comunicacion entre cliente-servidor
void NetworkClient::endCommunication(){
    SDLNet_TCP_Close(clientSocket);
    SDLNet_Quit();
};
