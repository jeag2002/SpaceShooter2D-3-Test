#include "NetworkClientUDP.h"


void NetworkClientUDP::initCommunicationUDP(std::string _ip, int _remotePort, int _localPort, int _remotePort_1, int _localPort_1){

    if ( SDLNet_Init() == -1 ){
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] -->  SDLNet_Init: %s\n",SDLNet_GetError());
        exit(-1);
    }

    clientSocket = SDLNet_UDP_Open(_localPort);
    if ( clientSocket == nullptr ){
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] -->  SDLNet_UDP_Open: %s\n",SDLNet_GetError());
        exit(-1);
    }

    clientSocket_1 = SDLNet_UDP_Open(_localPort_1);
    if ( clientSocket_1 == nullptr ){
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] -->  SDLNet_UDP_Open: %s\n",SDLNet_GetError());
        exit(-1);
    }

    std::string ip = _ip;
    int remotePort = _remotePort;
    int remotePort_1 = _remotePort_1;


    if ( SDLNet_ResolveHost( &serverIP, ip.c_str(), remotePort )  == -1 ){
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] --> SDLNet_ResolveHost: %s\n",SDLNet_GetError());
        exit(-1);
    }

    if ( SDLNet_ResolveHost( &serverIP_1, ip.c_str(), remotePort_1 )  == -1 ){
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] --> SDLNet_ResolveHost: %s\n",SDLNet_GetError());
        exit(-1);
    }

    packet = SDLNet_AllocPacket( BUFFER_SIZE );
    if ( packet == nullptr )
    {
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] --> Cannot find free enough memory space for packet of size [%d]::[%s]",BUFFER_SIZE,SDLNet_GetError());
        exit(-1);
    }


    packet_1 = SDLNet_AllocPacket( BUFFER_SIZE );
    if ( packet_1 == nullptr )
    {
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] --> Cannot find free enough memory space for packet of size [%d]::[%s]",BUFFER_SIZE,SDLNet_GetError());
        exit(-1);
    }


    packet->address.host = serverIP.host;
    packet->address.port = serverIP.port;

    packet_1->address.host = serverIP_1.host;
    packet_1->address.port = serverIP_1.port;


    logger->debug("[SSNETWORKMANAGER::initConnectionUDP] --> INITCONNNECTIONUDP DONE!");
}





//https://www.libsdl.org/projects/SDL_net/docs/demos/udptftpserver.c
void NetworkClientUDP::initCommunicationUDP(std::string _ip, int _remotePort, int _localPort){


    if ( SDLNet_Init() == -1 ){
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] -->  SDLNet_Init: %s\n",SDLNet_GetError());
        exit(-1);
    }

    clientSocket = SDLNet_UDP_Open(_localPort);
    if ( clientSocket == nullptr ){
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] -->  SDLNet_UDP_Open: %s\n",SDLNet_GetError());
        exit(-1);
    }

    std::string ip = _ip;
    int remotePort = _remotePort;



    if ( SDLNet_ResolveHost( &serverIP, ip.c_str(), remotePort )  == -1 ){
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] --> SDLNet_ResolveHost: %s\n",SDLNet_GetError());
        exit(-1);
    }

    packet = SDLNet_AllocPacket( BUFFER_SIZE );
    if ( packet == nullptr )
    {
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] --> Cannot find free enough memory space for packet of size [%d]::[%s]",BUFFER_SIZE,SDLNet_GetError());
        exit(-1);
    }

    packet->address.host = serverIP.host;
    packet->address.port = serverIP.port;

    logger->debug("[SSNETWORKMANAGER::initConnectionUDP] --> INITCONNNECTIONUDP DONE!");

};

/*

PROTOCOL FOR ESTABLISHING A UDP CHANNEL COMMUNICATION. (CLIENT SIZE)

1) GET SYNACK PACKET FROM SERVER.
2) SET QUERY ACK TO SERVER.
3) GET ACK FROM SERVER.

indexTramaSend (indexClientTrama)
indexTramaGet (indexServerTrama)

//-->SYNACK PACKET  (SERVER) indexTramaSend: 0; indexTramaGet:1
//-->QRY ACK PACKET (CLIENT) indexTramaSend: 1; indexTramaGet:1
//-->ACK PACKET     (SERVER) indexTramaSend: 1; indexTramaGet:2

Assumptions: Not verify CRC16, not request same packet. If handshacking doesn't work,  close communication.
*/

void NetworkClientUDP::establishCommunicationUDP(){

       //indexTramaSend++;
       //-->QRY ACK PACKET (SEND TO SERVER) indexTramaSend:1; indexTramaGet:0
       int times = 50;
       int time_resend_ack = 50;

       bool DONE = false;
       bool NOT_ACCEPTED = false;


       while ((time_resend_ack >= 0) && (!DONE) && (!NOT_ACCEPTED)){

           indexTramaSend=1;
           indexTramaGet=0;
           logger->info("[SSNETWORKMANAGER::establishCommunicationUDP] --> QRY_CONECTION TRAMASEND[%d] TRAMAGET[%d]",indexTramaSend,indexTramaGet);
           EventMsg *qryACK = new EventMsg(TRAMA_QRY_CONECTION,indexTramaSend,indexTramaGet,0,1,(uint16_t)0,packet);
           sendMsgToServer(qryACK);
           delete qryACK;

           DONE = false;
           NOT_ACCEPTED = false;
           times = 3;

           while ((times >= 0) && (!DONE)){

               indexTramaGet=1;
               SDL_Delay(100);
               EventMsg *responseACK = getMsgFromServer();

               if ((responseACK->getTypeMsg() == TRAMA_GET_CONECTION) &&
                  (responseACK->getTramaSend() == indexTramaSend) &&
                  (responseACK->getTramaGet() == indexTramaGet)){

                   uint16_t CRC16FromServer = responseACK->getCRC16();
                   uint16_t CRC16Calculated = UtilsProtocol::calculateCRC16_CCITT((const unsigned char *)responseACK->serializeMsg().c_str(),responseACK->serializeMsg().size());
                   logger->debug("[SSNETWORKMANAGER::establishCommunicationUDP] CRC ACK COMM FROM SERVER [%X] COMM FROM CLIENT [%X]",CRC16FromServer,CRC16Calculated);

                   answerType aType = responseACK->getAnswerType();
                   if (aType.result == OK){
                       logger->info("[SSNETWORKMANAGER::establishCommunicationUDP] --> ACK SERVER ESTABLISHED TRAMASEND[%d] TRAMAGET[%d]",indexTramaSend,indexTramaGet);
                   }else{
                       logger->info("[SSNETWORKMANAGER::establishCommunicationUDP] --> ACK SERVER FAILED (CANNOT ACCEPT MORE CLIENTS) TRAMASEND[%d] TRAMAGET[%d]",indexTramaSend,indexTramaGet);
                       NOT_ACCEPTED = true;
                   }

                   DONE = true;

                }else if(responseACK->getTypeMsg() == TRAMA_NULL){
                    logger->warn("[SSNETWORKMANAGER::establishCommunicationUDP] --> ACK SERVER FAILED (CONNECTION FAILED)");
                    times--;
                }

                delete responseACK;
           }

           time_resend_ack--;
       }

        if (NOT_ACCEPTED){
            SDLNet_UDP_Close(clientSocket);
            SDLNet_FreePacket(packet);
            SDLNet_Quit();
            exit(1);
        }


        if (!DONE){
            SDLNet_UDP_Close(clientSocket);
            SDLNet_FreePacket(packet);
            SDLNet_Quit();
            exit(1);
        }

};


resultPingType NetworkClientUDP::sendPingAndResult(int mapClient, int sessionClient, int playerID){
    long result = 0;
    long result_ClientSide = 0;
    long result_ServerSide = 0;

    resultPingType rPingTypeServer;

    rPingTypeServer.millisping = 0;
    rPingTypeServer.indexAuthServer = 0;

    logger->info("[SSNETWORKMANAGER::sendPingAndResult] --> INIT CONNECTION PING!. SEND TEST");
    EventMsg *msgTest = new EventMsg(TRAMA_TEST,indexTramaSend,indexTramaGet,0,1,(uint16_t)0,packet);

    OrderType oT;
    oT.orderID = ORDER_TEST;
    oT.actMap = mapClient;
    oT.session = sessionClient;
    oT.level = 0;
    oT.orderID = 0;
    oT.orderType = playerID;
    oT.pos_x = 0.0;
    oT.pos_y = 0.0;
    oT.height = 0;
    oT.width = 0;
    oT.value = 0;

    msgTest->setOrderType(oT);
    sendMsgToServer(msgTest);
    delete msgTest;

    result_ClientSide = SDL_GetTicks();
    SDL_Delay(10);

    EventMsg *msgPing = getMsgFromServer();
    if (msgPing->getTypeMsg() == TRAMA_PING){
        logger->info("[SSNETWORKMANAGER::sendPingAndResult] --> GET PING");
        EventMsg *msgPong = new EventMsg(TRAMA_PONG,indexTramaSend,indexTramaGet,0,1,(uint16_t)0,packet);

        OrderType oT_1;
        oT_1.orderID = ORDER_PONG;
        oT_1.actMap = mapClient;
        oT_1.session = sessionClient;
        oT_1.level = 0;
        oT_1.orderID = 0;
        oT_1.orderType = playerID;
        oT_1.pos_x = 0.0;
        oT_1.pos_y = 0.0;
        oT_1.height = 0;
        oT_1.width = 0;
        oT_1.value = 0;
        msgPong->setOrderType(oT_1);


        sendMsgToServer(msgPong);
        delete msgPong;

        logger->info("[SSNETWORKMANAGER::sendPingAndResult] --> SEND PONG");

        SDL_Delay(10);
        EventMsg *msgResultPong = getMsgFromServer();
        if (msgResultPong->getTypeMsg() == TRAMA_RESULT_TEST){

            logger->info("[SSNETWORKMANAGER::sendPingAndResult] --> GET RESULT TEST");
            result_ServerSide = msgResultPong->getResultPingType().millisping;
            rPingTypeServer.indexAuthServer =  msgResultPong->getResultPingType().indexAuthServer;
        }
    }

    result_ClientSide = SDL_GetTicks() - result_ClientSide;

    logger->info("[SSNETWORKMANAGER::sendPingAndResult] QOS CLIENTE [%d] QOS SERVER [%d]", result_ClientSide, result_ServerSide);

    if (result_ClientSide >= result_ServerSide){result = result_ClientSide;}
    else{result = result_ServerSide;}

    rPingTypeServer.millisping = result;

    return rPingTypeServer;

}



void NetworkClientUDP::getListActiveSessions(){


    logger->info("[SSNETWORKMANAGER::getListActiveSessions] --> QRY_LIST_ACTIVE_SESSION TRAMASEND[%d] TRAMAGET[%d]",indexTramaSend,indexTramaGet);
    EventMsg *TRQRYSESSIONLIST = new EventMsg(TRAMA_QRY_SESSION_LIST,indexTramaSend,indexTramaGet,0,1,(uint16_t)0,packet);
    sendMsgToServer(TRQRYSESSIONLIST);
    delete TRQRYSESSIONLIST;

    SDL_Delay(100);

    EventMsg *response = getMsgFromServer();
    if (response->getTypeMsg() == TRAMA_GET_SESSION_LIST){

        uint16_t CRC16FromServer = response->getCRC16();
        uint16_t CRC16Calculated = UtilsProtocol::calculateCRC16_CCITT((const unsigned char *)response->serializeMsg().c_str(),response->serializeMsg().size());
        logger->debug("[SSNETWORKMANAGER::LISTACTIVESESSION] CRC GET ACTIVE SESSION LIST TRAMASEND[%d] TRAMAGET[%d] COMM FROM SERVER [%X] COMM FROM CLIENT [%X]",indexTramaSend,indexTramaGet,CRC16FromServer,CRC16Calculated);

        listSessionAvailableType lSAType = response->getListSessionAvailableType();
        logger->info("[SSNETWORKMANAGER::LISTACTIVESESSION] *** LIST ACTIVE MAPS - ACTIVE SESSION FROM SERVER *** -INI- *** ");
        logger->info("[SSNETWORKMANAGER::LISTACTIVESESSION] mapa_ID [%d] session [%d] max_Players [%d] act_Players[%d]",lSAType.map_1_id,lSAType.session_1_1,lSAType.num_player_max_1_1,lSAType.num_player_ava_1_1);
        logger->info("[SSNETWORKMANAGER::LISTACTIVESESSION] mapa_ID [%d] session [%d] max_Players [%d] act_Players[%d]",lSAType.map_1_id,lSAType.session_1_2,lSAType.num_player_max_1_2,lSAType.num_player_ava_1_2);
        logger->info("[SSNETWORKMANAGER::LISTACTIVESESSION] mapa_ID [%d] session [%d] max_Players [%d] act_Players[%d]",lSAType.map_2_id,lSAType.session_2_1,lSAType.num_player_max_2_1,lSAType.num_player_ava_2_1);
        logger->info("[SSNETWORKMANAGER::LISTACTIVESESSION] mapa_ID [%d] session [%d] max_Players [%d] act_Players[%d]",lSAType.map_2_id,lSAType.session_2_2,lSAType.num_player_max_2_2,lSAType.num_player_ava_2_2);
        logger->info("[SSNETWORKMANAGER::LISTACTIVESESSION] *** LIST ACTIVE MAPS - ACTIVE SESSION FROM SERVER *** -END- *** ");
    }else if (response->getTypeMsg() == TRAMA_NULL){
        logger->warn("[SSNETWORKMANAGER::LISTACTIVESESSION] --> CANNOT GET LIST. CLOSE SOCKET");
        //SDLNet_UDP_Close(clientSocket);
        //SDLNet_FreePacket(packet);
        //SDLNet_Quit();
        //exit(1);
    }
    delete response;

};

void NetworkClientUDP::registerToActiveSession(int mapClient, int sessionClient){

    indexTramaSend++;

    playerDataType pDT;
    pDT.actMap = mapClient;
    pDT.session = sessionClient;
    pDT.idPlayer = 0;
    pDT.lvl = 0;
    pDT.playerDataID = 0;
    pDT.typeID = 0;
    pDT.heigth = 0;
    pDT.width = 0;
    pDT.x_pos = 0.0f;
    pDT.y_pos = 0.0f;


    logger->info("[SSNETWORKMANAGER::registerToActiveSession] --> TRAMA_SYNACK_SESSION TRAMASEND[%d] TRAMAGET[%d]",indexTramaSend,indexTramaGet);

    EventMsg *TRSYNACKSESSION = new EventMsg(TRAMA_SYNACK_SESSION,indexTramaSend,indexTramaGet,0,1,(uint16_t)0,packet,pDT);
    sendMsgToServer(TRSYNACKSESSION);
    delete TRSYNACKSESSION;
}


//send one message to REMOTE
void NetworkClientUDP::sendMsgToServer(EventMsg *msg){

    //SDL_LockMutex(send_mutex);

    clearBuffer();
    UDPpacket *packetUDP = SDLNet_AllocPacket(BUFFER_SIZE);
    clearBufferPacket(packetUDP);

    char *tramaBuffChr = msg->marshallMsg();
    std::string tramaStr(tramaBuffChr);

    //memcpy(packetUDP->data, tramaStr.c_str(), tramaStr.length() );

    for(int i=0; i<tramaStr.length(); i++){
        packetUDP->data[i] = ((Uint8)(tramaBuffChr[i]));
    }

    packetUDP->len = tramaStr.length();
    packetUDP->address.host = msg->getPacketUPD()->address.host;
    packetUDP->address.port = msg->getPacketUPD()->address.port;
    packetUDP->channel = msg->getPacketUPD()->channel;
    packetUDP->status = msg->getPacketUPD()->status;

    if (enabledCompression){
        unsigned char *dataCompression = cP->CompressionData((char *)packetUDP->data,packetUDP->len);
        int size_after_dataCompression = strlen((const char *)dataCompression);
        logger->warn("[SSNETWORKMANAGER::sendMsgToServerUPD] --> size_data_before_compression [%d] size_data_after_compression [%d] ",packetUDP->len,size_after_dataCompression);
    }

    remoteHostData rHD = UtilsProtocol::parseRemoteHostData(packetUDP);
    logPackets->debug("[TRAMA SEND CLIENT] --> RAW DATA[%s] TRAMABUFF[%s] - (%s:%d)",packetUDP->data,tramaBuffChr,rHD.host,rHD.port);

    if ( SDLNet_UDP_Send(clientSocket, -1, packetUDP) == 0 ){
        logger->warn("[SSNETWORKMANAGER::sendMsgToServerUDP] --> UDP DATA NOT SEND! [%s]", SDLNet_GetError());
        exit(-1);
    }

    delete packetUDP;

    logger->debug("[SSNETWORKMANAGER::sendMsgToServerUDP] CLIENT MSG TO SERVER [%s] size [%d]",packetUDP->data,packetUDP->len);

    //SDL_UnlockMutex(send_mutex);

};

EventMsg **NetworkClientUDP::getMsgsFromServer(){

    EventMsg **dataMsg = new EventMsg *[PACKETS];

    for(int i=0; i<PACKETS; i++){
        dataMsg[i] = new EventMsg();
    }

    UDPpacket **packetV = SDLNet_AllocPacketV(PACKETS, BUFFER_SIZE);

    int numrecv = SDLNet_UDP_RecvV(clientSocket, packetV);

    if (numrecv == -1){
        logger->warn("[SSNETWORKMANAGER::getMsgsFromServer] GET DATA [%d] ERROR [%s]",numrecv,SDLNet_GetError());
    }else{
        logger->debug("SSNETWORKMANAGER::getMsgsFromServer] GET [%d] PACKETS",numrecv);
    }

    for(int i=0; i<numrecv; i++){
        dataMsg[i]->unmarshallMsg(((const char *)packetV[i]->data));
    }

    SDLNet_FreePacketV(packetV);

    return dataMsg;
};


EventMsg *NetworkClientUDP::getMsgFromServerQueue(){

    bool DONE = false;

    EventMsg *returnMsg = new EventMsg();

    //SDL_LockMutex(get_mutex);
    long initialMark = SDL_GetTicks();

    while(!DONE){

          //if (SDLNet_UDP_Recv(clientSocket, packet)){
          for(int i=0; i<BUFFER_SIZE; i++){packet_1->data[i] = '\0';}
          if (SDLNet_UDP_Recv(clientSocket_1, packet_1)){

            logger->warn("[SSNETWORKMANAGER::getMsgFromServerUDP] --> PACKET RECEIVED [%s]", packet_1->data);
            remoteHostData rHD = UtilsProtocol::parseRemoteHostData(packet_1);
            logPackets->debug("[TRAMA GET CLIENT] --> RAW DATA[%s]  - (%s:%d)",packet_1->data,rHD.host,rHD.port);

            std::string data((char *)packet_1->data);
            std::string msg = data.substr(0,128);
            returnMsg->unmarshallMsg((const char *)msg.c_str());
            DONE = true;

          }

          if (!DONE){

            long DIFF = SDL_GetTicks()-initialMark;
            if (DIFF >= MAX_DELAY){
                logger->warn("[SSNETWORKMANAGER::getMsgFromServerUDP] --> SOCKET INACTIVE DURING [%d] MS SYSTEMOUT", DIFF);
                DONE = true;
            }

          }
    }

    //SDL_UnlockMutex(get_mutex);
    return returnMsg;

};



//receive one message from REMOTE.
EventMsg *NetworkClientUDP::getMsgFromServer(){

    bool DONE = false;

    EventMsg *returnMsg = new EventMsg();

    //SDL_LockMutex(get_mutex);
    long initialMark = SDL_GetTicks();

    while(!DONE){

          //if (SDLNet_UDP_Recv(clientSocket, packet)){
          for(int i=0; i<BUFFER_SIZE; i++){packet->data[i] = '\0';}
          if (SDLNet_UDP_Recv(clientSocket, packet)){

            logger->warn("[SSNETWORKMANAGER::getMsgFromServerUDP] --> PACKET RECEIVED [%s]", packet->data);
            remoteHostData rHD = UtilsProtocol::parseRemoteHostData(packet);
            logPackets->debug("[TRAMA GET CLIENT] --> RAW DATA[%s] - (%s:%d)",packet->data, rHD.host, rHD.port);

            std::string data((char *)packet->data);
            std::string msg = data.substr(0,128);
            returnMsg->unmarshallMsg((const char *)msg.c_str());
            DONE = true;

          }

          if (!DONE){

            long DIFF = SDL_GetTicks()-initialMark;
            if (DIFF >= MAX_DELAY){
                logger->warn("[SSNETWORKMANAGER::getMsgFromServerUDP] --> SOCKET INACTIVE DURING [%d] MS SYSTEMOUT", DIFF);
                DONE = true;
            }

          }
    }

    //SDL_UnlockMutex(get_mutex);

    return returnMsg;

};

