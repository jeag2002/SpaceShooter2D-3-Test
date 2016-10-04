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

    logger->info("[SSNETWORKMANAGERSERVER::initCommunicationUDP] UDP CONFIGURATION DONE!");
};


//-->SEND ONE MSG TO CLIENT(S)
void NetworkClientUDP::sendMsgToClientUDP(EventMsg *msg){

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

    if ( SDLNet_UDP_Send(serverSocket, -1, packetUDP) == 0 ){
        logger->warn("[SSNETWORKMANAGERSERVER::sendMsgToClientUDP] --> UDP DATA NOT SEND! [%s]", SDLNet_GetError());
        exit(-1);
    }

    logger->debug("[SSNETWORKMANAGERSERVER::sendMsgToClientUDP] SERVER MSG TO CLIENT [%s] size [%d] CRC16 [%d]",packetUDP->data,packetUDP->len,msg->getCRC16());

};

//-->RECEIVE ONE MSG FROM CLIENT(S)
EventMsg *NetworkClientUDP::getMsgFromClientUDP(){

    bool DONE = false;

    EventMsg *returnMsg = new EventMsg();

    long initialMark = SDL_GetTicks();
    SDLNet_UDP_Unbind(serverSocket, 0);
    IPaddress ipAdd;

    while(!DONE){

        if ( SDLNet_UDP_Recv(serverSocket, packet))
		{
		    logger->debug("[SSNETWORKMANAGERSERVER::getMsgFromClientUDP] CHANNEL [%d] RAW DATA [%s]",packet->channel, packet->data);
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
                std::cout << "SDLNet_UDP_Bind: " << SDLNet_GetError() << "\n";
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

    return returnMsg;

};


