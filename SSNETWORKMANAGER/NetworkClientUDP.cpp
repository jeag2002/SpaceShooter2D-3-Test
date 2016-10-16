#include "NetworkClientUDP.h"

//https://www.libsdl.org/projects/SDL_net/docs/demos/udptftpserver.c
void NetworkClientUDP::initCommunicationUDP(int localPort){


    if ( SDLNet_Init() == -1 ){
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] -->  SDLNet_Init: %s\n",SDLNet_GetError());
        exit(-1);
    }

    clientSocket = SDLNet_UDP_Open(localPort);
    if ( clientSocket == nullptr ){
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] -->  SDLNet_UDP_Open: %s\n",SDLNet_GetError());
        exit(-1);
    }

    std::string ip = REMOTE_HOST;
    int remoteport = REMOTE_PORT;

    if ( SDLNet_ResolveHost( &serverIP, ip.c_str(), remoteport )  == -1 ){
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

       logger->info("[SSNETWORKMANAGER::establishCommunicationUDP] --> QRY_CONECTION TRAMASEND[%d] TRAMAGET[%d]",indexTramaSend,indexTramaGet);

       EventMsg *qryACK = new EventMsg(TRAMA_QRY_CONECTION,indexTramaSend,indexTramaGet,0,1,(uint16_t)0,packet);
       sendMsgToServer(qryACK);
       indexTramaGet++;
       delete qryACK;

        //-->ACK PACKET  (GET FROM SERVER) indexTramaSend:1; indexTramaGet:1
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
           }

        }else if(responseACK->getTypeMsg() == TRAMA_NULL){
            logger->warn("[SSNETWORKMANAGER::establishCommunicationUDP] --> ACK SERVER FAILED (CONNECTION FAILED)");

            SDLNet_UDP_Close(clientSocket);
            SDLNet_FreePacket(packet);
            SDLNet_Quit();
            exit(1);
        }

        delete responseACK;
};


void NetworkClientUDP::getListActiveSessions(){


    logger->info("[SSNETWORKMANAGER::getListActiveSessions] --> QRY_LIST_ACTIVE_SESSION TRAMASEND[%d] TRAMAGET[%d]",indexTramaSend,indexTramaGet);
    EventMsg *TRQRYSESSIONLIST = new EventMsg(TRAMA_QRY_SESSION_LIST,indexTramaSend,indexTramaGet,0,1,(uint16_t)0,packet);
    sendMsgToServer(TRQRYSESSIONLIST);
    delete TRQRYSESSIONLIST;

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
        SDLNet_UDP_Close(clientSocket);
        SDLNet_FreePacket(packet);
        SDLNet_Quit();
        exit(1);
    }
    delete response;

};

EventMsg *NetworkClientUDP::registerToActiveSession(int mapClient, int sessionClient){

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

    EventMsg *response = getMsgFromServer();
    return response;
}


//send one message to REMOTE
void NetworkClientUDP::sendMsgToServer(EventMsg *msg){

    clearBuffer();
    UDPpacket *packetUDP = msg->getPacketUPD();
    clearBufferPacket(packetUDP);

    char *tramaBuffChr = msg->marshallMsg();
    std::string tramaStr(tramaBuffChr);

    memcpy(packetUDP->data, tramaStr.c_str(), tramaStr.length() );
    packetUDP->len = tramaStr.length();

    if (enabledCompression){
        unsigned char *dataCompression = cP->CompressionData((char *)packetUDP->data,packetUDP->len);
        int size_after_dataCompression = strlen((const char *)dataCompression);
        logger->warn("[SSNETWORKMANAGER::sendMsgToServerUPD] --> size_data_before_compression [%d] size_data_after_compression [%d] ",packetUDP->len,size_after_dataCompression);
    }

    if ( SDLNet_UDP_Send(clientSocket, -1, packetUDP) == 0 ){
        logger->warn("[SSNETWORKMANAGER::sendMsgToServerUDP] --> UDP DATA NOT SEND! [%s]", SDLNet_GetError());
        exit(-1);
    }

    logger->debug("[SSNETWORKMANAGER::sendMsgToServerUDP] CLIENT MSG TO SERVER [%s] size [%d]",packetUDP->data,packetUDP->len);

};

//receive one message from REMOTE.
EventMsg *NetworkClientUDP::getMsgFromServer(){

    bool DONE = false;

    EventMsg *returnMsg = new EventMsg();

    long initialMark = SDL_GetTicks();

    while(!DONE){

          //if (SDLNet_UDP_Recv(clientSocket, packet)){
          for(int i=0; i<BUFFER_SIZE; i++){packet->data[i] = '\0';}
          if (SDLNet_UDP_Recv(clientSocket, packet)){

            logger->warn("[SSNETWORKMANAGER::getMsgFromServerUDP] --> PACKET RECEIVED [%s]", packet->data);

            std::string data((char *)packet->data);
            std::string msg = data.substr(0,128);
            returnMsg->unmarshallMsg((const char *)msg.c_str());
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


