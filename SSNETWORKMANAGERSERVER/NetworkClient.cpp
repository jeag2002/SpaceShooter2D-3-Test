#include "NetworkClient.h"

//configura SDL_net, comunicacion cliente-servidor.
void NetworkClient::initCommunication(){

    if (SDLNet_Init() < 0){
        logger->error("[SSNETWORKMANAGERSERVER::initCommunication] Failed SDLNet_Int [%s]",SDLNet_GetError());
        exit(-1);
    }

    socketSet = SDLNet_AllocSocketSet(MAX_CLIENT);
    if(socketSet == NULL){
        logger->error("[SSNETWORKMANAGERSERVER::initCommunication] Error Allocating [%d] Sockets SDLNet_Int [%s]",MAX_CLIENT,SDLNet_GetError());
        exit(-1);
    }else{
        logger->debug("[SSNETWORKMANAGERSERVER::initCommunication] [%d] sockets created",MAX_CLIENT);
    }

    for(int loop = 0; loop < MAX_CLIENT; loop++){
        clientSocket[loop] = NULL;
        freeSocket[loop] = true;
    }

    int hostResolved = SDLNet_ResolveHost(&serverIP,NULL,PORT);

    if (hostResolved == -1){
        logger->error("[SSNETWORKMANAGERSERVER::initCommunication] Sockets SDLNet_Int [%s]", SDLNet_GetError());
        exit(-1);
    }

    serverSocket = SDLNet_TCP_Open(&serverIP);

    if (!serverSocket){
        logger->error("[SSNETWORKMANAGERSERVER::initCommunication] Error Open Server Socket [%s]", SDLNet_GetError());
        exit(-1);
    }

    SDLNet_TCP_AddSocket(socketSet, serverSocket);
    logger->debug("[SSNETWORKMANAGERSERVER::initCommunication] TCP SERVER CONFIGURATED!");
};


//establece primera comunicacion entre cliente-servidor.
void NetworkClient::establishCommunication(){

    numActiveSockets = SDLNet_CheckSockets(socketSet,0);
    if (numActiveSockets != 0){
        //logger->debug("[SSNETWORKMANAGERSERVER::establishCommunication] [%d] activeSockets",numActiveSockets);
    }

    int serverSocketActivity = SDLNet_SocketReady(serverSocket);
    if (serverSocketActivity > 0){

        if (clientCount < MAX_CLIENT){
            int freeSocketID = -1;
            for(int loop=0; loop<MAX_CLIENT; loop++){
                if (freeSocket[loop] == true){
                    freeSocket[loop] = false;
                    freeSocketID = loop;
                    break;
                }
            }

            if (freeSocketID != -1){
                clientSocket[freeSocketID] = SDLNet_TCP_Accept(serverSocket);
                SDLNet_TCP_AddSocket(socketSet,clientSocket[freeSocketID]);
                clientCount++;
                //logger->debug("[SSNETWORKMANAGERSEVER::establishCommunication] New Client connected. Act Clients [%d]", clientCount);
                processACKTrama(clientSocket[freeSocketID],true);
            }else{
                TCPsocket auxSocket = SDLNet_TCP_Accept(serverSocket);
                //logger->debug("[SSNETWORKMANAGERSEVER::establishCommunication] Fail in Client connection. Act Clients [%d]", clientCount);
                processACKTrama(auxSocket, false);
                SDLNet_TCP_Close(auxSocket);
            }

        }else{
            TCPsocket auxSocket = SDLNet_TCP_Accept(serverSocket);
            //logger->debug("[SSNETWORKMANAGERSEVER::establishCommunication] There is not space for new Client Act Clients [%d]", clientCount);
            processACKTrama(auxSocket, false);
            SDLNet_TCP_Close(auxSocket);
        }
    //eleiminamos acceso al socket.
    }
};


void NetworkClient::processACKTrama(TCPsocket client, bool res){

    sendMsgToClient(client,new EventMsg(TRAMA_SYNACK_CONECTION,0,0,0,0,(uint16_t)0));
    EventMsg *inputMsg = getMsgFromClient(client);
    if (inputMsg->getTypeMsg() == TRAMA_QRY_CONECTION){
        EventMsg *outputMsg = new EventMsg(TRAMA_GET_CONECTION,
                                           inputMsg->getTramaSend(),
                                           inputMsg->getTramaGet(),
                                           NOK,
                                           NOK,
                                           (uint16_t)0);
        answerType aType;

        aType.type_trama = TYPE_MSG_ANSWER_CONNECTION;
        aType.trama =   inputMsg->getTramaGet();
        aType.command = TRAMA_QRY_CONECTION;

        if (res){
            aType.result = OK;
        }else{
            aType.result = NOK;
        }

        outputMsg->setAnswerType(aType);
        sendMsgToClient(client,outputMsg);
    }

}


void NetworkClient::sendMsgToClient(TCPsocket clientSocket, EventMsg *msg){
    char *bufferSend = msg->marshallMsg();
    int bufferSendSize = strlen(bufferSend) + 1;
    logger->debug("SSNETWORKMANAGERSERVER::MSGTOCLIENT sndMsg --> [%s] size [%d]",bufferSend,bufferSendSize);
    int datasend = SDLNet_TCP_Send(clientSocket, (void *)bufferSend, bufferSendSize);
    logger->debug("SSNETWORKMANAGERSERVER::MSGTOCLIENT sndMsg --> [%s] size [%d] data send[%d]",bufferSend,bufferSendSize,datasend);
    if (bufferSendSize> datasend){
        logger->debug("SSNETWORKMANAGERSERVER::MSGTOCLIENT ERROR [%d]",SDLNet_GetError());
    }
}


char *NetworkClient::serializeFourMsg(EventMsg *msg_1, EventMsg *msg_2, EventMsg *msg_3, EventMsg *msg_4){

    std::string buffer;

    if (msg_1 != NULL){
        std::string msg1Str(msg_1->marshallMsg()); //TRAMAÑO TRAMA FIJOS de 128
        buffer = msg1Str + std::string(TRAMA_SIZE - msg1Str.length(), '0') ;
    }

    if (msg_2 != NULL){
        std::string msg2Str(msg_2->marshallMsg()); //TRAMAÑO TRAMA FIJOS de 128
        buffer = msg2Str + std::string(TRAMA_SIZE - msg2Str.length(), '0') ;
    }

    if (msg_3 != NULL){
        std::string msg3Str(msg_3->marshallMsg()); //TRAMAÑO TRAMA FIJOS de 128
        buffer = msg3Str + std::string(TRAMA_SIZE - msg3Str.length(), '0') ;
    }

    if (msg_4 != NULL){
        std::string msg4Str(msg_4->marshallMsg()); //TRAMAÑO TRAMA FIJOS de 128
        buffer = msg4Str + std::string(TRAMA_SIZE - msg4Str.length(), '0') ;
    }

    buffer = buffer + std::string(BUFFER_SIZE - buffer.length(), '0'); //TRAMAÑO BUFFER FIJO DE 512 Bytes;

    return (char *)buffer.c_str();
}

void NetworkClient::sendFourMsgToClient(TCPsocket clientSocket,EventMsg *msg_1, EventMsg *msg_2, EventMsg *msg_3, EventMsg *msg_4){

    char *bufferSend = serializeFourMsg(msg_1,msg_2,msg_3,msg_4);
    int bufferSendSize = strlen(bufferSend) + 1;
    logger->debug("[SSNETWORKMANAGERSERVER::SENDFOURMSGTOCLIENT] sndMsg --> [%s] size [%d]",bufferSend,bufferSendSize);
    int datasend = SDLNet_TCP_Send(clientSocket, (void *)bufferSend, bufferSendSize);
    logger->debug("[SSNETWORKMANAGERSERVER::SENDFOURMSGTOCLIENT] sndMsg --> [%s] size [%d] data send[%d]",bufferSend,bufferSendSize,datasend);
    if (bufferSendSize> datasend){
        logger->debug("[SSNETWORKMANAGERSERVER::SENDFOURMSGTOCLIENT] ERROR [%d]",SDLNet_GetError());
    }
}




EventMsg *NetworkClient::getMsgFromClient(TCPsocket clientSocket){

    EventMsg *eMsg = new EventMsg();
    char bufferAux[128];
    int data_rev=0;

    bool DONE = false;

    int initialMark = SDL_GetTicks();

    while(!DONE){
        int socketActive = SDLNet_CheckSockets(socketSet,0);
        if (socketActive != 0)
        {
                int messageFromServer = SDLNet_SocketReady(clientSocket);
                if (messageFromServer != 0){
                    clearBuffer();
                    int awaiting_buff =  strlen(buffer)+1;
                    int buffer_int = SDLNet_TCP_Recv(clientSocket, buffer, 512);
                    if (buffer_int > 0){
                        buffer[buffer_int] = 0;
                        logger->debug("SSNETWORKMANAGERSERVER::MSGFROMCLIENT getMsg --> [%s] size expected [%d] size get[%d]",buffer, awaiting_buff, buffer_int);
                        if ((buffer_int >= awaiting_buff) && (buffer_int >=26) && (buffer_int <= 512 )){
                            eMsg->unmarshallMsg((const char *)buffer);
                        }
                        DONE = true;
                    }else{
                        logger->warn("SSNETWORKMANAGERSERVER::MSGFROMCLIENT Error [%s]",SDLNet_GetError());
                        SDLNet_TCP_Close(clientSocket);
                        exit(1);
                        DONE = true;
                    }
                }else{
                    logger->warn("[SSNETWORKMANAGERSERVER::MSGFROMCLIENT] getMsg --> CLIENT SOCKET SEND MSG OF 0 BYTES");
                }
        }else{
             logger->warn("[SSNETWORKMANAGERSERVER::MSGFROMCLIENT] getMsg --> SOCKET SET IS NOT ACTIVE");
        }

        int diff = SDL_GetTicks()-initialMark;

        if (!DONE){
            logger->warn("[SSNETWORKMANAGERSERVER::MSGFROMCLIENT] --> SOCKET INACTIVE DURING [%d] MS", diff);
            if (diff > 150){
                DONE = true;
                SDLNet_TCP_DelSocket(socketSet, clientSocket);
                SDLNet_TCP_Close(clientSocket);
            }
        }
    }

    return eMsg;
}


//cerrar comunicacion entre cliente-servidor
void NetworkClient::endCommunication(){
    SDLNet_FreeSocketSet(socketSet);
    SDLNet_TCP_Close(serverSocket);
    SDLNet_Quit();
};
