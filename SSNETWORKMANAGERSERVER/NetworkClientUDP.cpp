#include "NetworkClientUDP.h"


//-->init SERVER UPD Communication
void NetworkClientUDP::initCommunicationUDP(){


    if ( SDLNet_Init() == -1 ){
        logger->error("[SSNETWORKMANAGERSERVER::initCommunicationUDP] Failed SDLNet_Int [%s]",SDLNet_GetError());
        exit(-1);
    }

    serverSocket = SDLNet_UDP_Open(LOCAL_PORT);

    if (serverSocket==NULL){
        logger->error("[SSNETWORKMANAGERSERVER::initCommunicationUDP] Error creating serverSocket [%s]",SDLNet_GetError());
        exit(-1);
    }else{
        logger->debug("[SSNETWORKMANAGERSERVER::initCommunicationUDP] listen from 0.0.0.0/[%d]",LOCAL_PORT);
    }

    host = REMOTE_HOST;
    int remoteport = REMOTE_PORT;

    if ( SDLNet_ResolveHost( &serverIP, host.c_str(), remoteport )  == -1 ){
        logger->error("[SSNETWORKMANAGERSERVER::initCommunicationUDP] cannot connect with URL [%s]:%d",host.c_str(),remoteport);
        exit(-1);
    }

    packet = SDLNet_AllocPacket(BUFFER_SIZE);
    if ( packet == NULL ){
        logger->error("[SSNETWORKMANAGERSERVER::initCommunicationUDP] cannot allocate buffer size [%s]",BUFFER_SIZE);
        exit(-1);
    }

    packet->address.host = serverIP.host;
    packet->address.port = serverIP.port;

    out = SDLNet_AllocPacketV(SIZE_REMOTE_ELEMS, BUFFER_SIZE);

    if (out == NULL){
        logger->error("[SSNETWORKMANAGERSERVER::initCommunicationUDP] cannot allocate vector size [%s] buffer size [%s]",SIZE_REMOTE_ELEMS,BUFFER_SIZE);
        //exit(-1);
    }


    logger->info("[SSNETWORKMANAGERSERVER::initCommunicationUDP] UDP CONFIGURATION DONE!");
};


//-->SEND ONE MSG TO CLIENT(S)
void NetworkClientUDP::sendMsgToClientUDP(EventMsg *msg){

    SDL_LockMutex(mutexSend);
    SDL_CondWaitTimeout( condSendV, mutexSend, 100);

    clearBuffer();
    UDPpacket *packetUDP = msg->getPacketUPD();
    //clearBufferPacket(packetUDP);

    char *tramaBuffChr = msg->marshallMsg();
    std::string tramaStr(tramaBuffChr);

    memcpy(packetUDP->data, tramaStr.c_str(), tramaStr.length() );
    packetUDP->len = tramaStr.length();

    if (enabledCompression){
        unsigned char *dataCompression = cP->CompressionData((char *)packetUDP->data,packetUDP->len);
        int size_after_dataCompression = strlen((const char *)dataCompression);
        logger->warn("[SSNETWORKMANAGERSERVER::sendMsgToClientUPD] --> size_data_before_compression [%d] size_data_after_compression [%d] ",packetUDP->len,size_after_dataCompression);
    }

    remoteHostData rHD = UtilsProtocol::parseRemoteHostData(packetUDP);
    logPackets->debug("[TRAMA SEND SERVER] --> RAW DATA[%s] (%s:%d)",packetUDP->data,rHD.host,rHD.port);

    if ( SDLNet_UDP_Send(serverSocket, -1, packetUDP) == 0 ){
        logger->warn("[SSNETWORKMANAGERSERVER::sendMsgToClientUDP] --> UDP DATA NOT SEND! [%s]", SDLNet_GetError());
        exit(-1);
    }

    if (packetUDP != NULL){
        remoteHostData rHD = UtilsProtocol::parseRemoteHostData(packetUDP);
        logger->debug("[SSNETWORKMANAGERSERVER::sendMsgToClientUDP] SERVER MSG [%s] TO CLIENT [%s]:[%d] size [%d] CRC16 [%d]",packetUDP->data, rHD.host, rHD.port, packetUDP->len,msg->getCRC16());
    }else{
          logger->debug("[SSNETWORKMANAGERSERVER::sendMsgToClientUDP] SERVER MSG [%s] size [%d] CRC16 [%d]",packetUDP->data, packetUDP->len,msg->getCRC16());
    }

    SDL_CondSignal( condSend );
    SDL_UnlockMutex(mutexSend);

};


void NetworkClientUDP::sendMsgVectorToClientUDP(EventMsg **msgs){

    SDL_LockMutex(mutexSendV);
    SDL_CondWaitTimeout( condSend, mutexSendV, 100);

    logger->debug("[SSNETWORKMANAGERSERVER::sendMsgVectorToClientUDP] --> SEND PACKETS TO CLIENT");

    for(int index_packet = 0; index_packet < SIZE_REMOTE_ELEMS; index_packet++){

             UDPpacket *packet_data = SDLNet_AllocPacket(BUFFER_SIZE);
             for(int i=0; i<100; i++){packet_data->data[i]='\0';}

             EventMsg *eventMsg = msgs[index_packet];
             std::string msgAsString(eventMsg->marshallMsg());
             memcpy(packet_data->data, msgAsString.c_str(), msgAsString.length() );

             packet_data->len = msgAsString.length();
             packet_data->channel = eventMsg->getPacketUPD()->channel;
             packet_data->status = eventMsg->getPacketUPD()->status;
             packet_data->address.host = eventMsg->getPacketUPD()->address.host;
             packet_data->address.port = eventMsg->getPacketUPD()->address.port;

             logPackets->debug("[TRAMA SEND SERVER VECTOR] --> RAW DATA[%s] [%d]:[%d]",packet_data->data,packet_data->address.host,packet_data->address.port);

             int actMap = eventMsg->getRemotePlayerType().actMap;
             int actSession = eventMsg->getRemotePlayerType().session;

             logger->debug("[SSNETWORKMANAGERSERVER::sendMsgVectorToClientUDP MAP[%d] SESSION[%d]] tramaSend[%d] tramaGet[%d] data_to_client[%d]:=[%s]",actMap,actSession,eventMsg->getTramaSend(),eventMsg->getTramaGet(),index_packet,packet_data->data);

             out[index_packet] = packet_data;
    }


    int data = SDLNet_UDP_SendV(serverSocket,out,SIZE_REMOTE_ELEMS);
    if(data <SIZE_REMOTE_ELEMS){
       logger->debug("[SSNETWORKMANAGERSERVER::sendMsgVectorToClientUDP] ERROR IN THE PROCESS OF SENDING [%d] MSG, SENT DATA [%d] ERROR [%s]",SIZE_REMOTE_ELEMS,data, SDLNet_GetError());
    }

    SDL_CondSignal( condSendV );
    SDL_UnlockMutex(mutexSendV);


}

//-->RECEIVE ONE MSG FROM CLIENT(S)
EventMsg *NetworkClientUDP::getMsgFromClientUDP(){

    bool DONE = false;

    EventMsg *returnMsg = new EventMsg();

    SDL_LockMutex(mutexGet);

    long initialMark = SDL_GetTicks();
    SDLNet_UDP_Unbind(serverSocket, 0);
    IPaddress ipAdd;

    while(!DONE){

        if ( SDLNet_UDP_Recv(serverSocket, packet))
		{
		    logger->debug("[SSNETWORKMANAGERSERVER::getMsgFromClientUDP] CHANNEL [%d] RAW DATA [%s]",packet->channel, packet->data);
		    remoteHostData rHD = UtilsProtocol::parseRemoteHostData(packet);
		    logPackets->debug("[TRAMA GET SERVER] --> RAW DATA[%s] - (%s:%d)",packet->data,rHD.host,rHD.port);

		    memcpy(&ipAdd,&packet->address,sizeof(IPaddress));

            const char *host=SDLNet_ResolveIP(&ipAdd);
            Uint32 ipnum=SDL_SwapBE32(ipAdd.host);
            Uint16 port=SDL_SwapBE16(ipAdd.port);

            if(host){
               logger->debug("[SSNETWORKMANAGERSERVER::getMsgFromClientUDP] GET FROM HOST %s:%d",host,port);
            }else{
               logger->debug("[SSNETWORKMANAGERSERVER::getMsgFromClientUDP] GET FROM HOST %d.%d.%d.%d:%d",(ipnum>>24),((ipnum>>16)&0xff),((ipnum>>8)&0xff),(ipnum&0xff),port);
            }

            if(SDLNet_UDP_Bind(serverSocket, 0, &ipAdd)==-1)
            {
                logger->debug("[SSNETWORKMANAGERSERVER::getMsgFromClientUDP] SDLNet_UDP_Bind: %s",SDLNet_GetError());
                exit(-1);
            }

            std::string data((char *)packet->data);
            std::string msg = data.substr(0,128);

            logger->debug("[SSNETWORKMANAGERSERVER::getMsgFromClientUDP] PACKET DATA getMsg [%s]",msg.c_str());

            returnMsg->unmarshallMsg((const char *)msg.c_str());
            returnMsg->setPacketUPD(packet);

            DONE = true;
		}

		if (!DONE){
            long DIFF = SDL_GetTicks()-initialMark;
            logger->warn("[SSNETWORKMANAGERSERVER::getMsgFromClientUDP] --> SOCKET INACTIVE DURING [%d] MS", DIFF);
            if (DIFF >= MAX_DELAY){
                DONE = true;
            }
            SDL_Delay(10);
		}
    }

    SDL_UnlockMutex(mutexGet);

    return returnMsg;

};


