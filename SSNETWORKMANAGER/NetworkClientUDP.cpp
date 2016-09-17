#include "NetworkClientUDP.h"

//https://www.libsdl.org/projects/SDL_net/docs/demos/udptftpserver.c
void NetworkClientUDP::initCommunicationUDP(){

    /* initialize SDL */
	if(SDL_Init(0)==-1)
	{
		logger->warn("SDL_Init: %s\n",SDL_GetError());
		exit(1);
	}

	/* initialize SDL_net */
	if(SDLNet_Init()==-1)
	{
		logger->warn("SDLNet_Init: %s\n",SDLNet_GetError());
		exit(2);
	}

	if(SDLNet_ResolveHost(&serverIP,"localhost",8888)==-1)
	{
		logger->warn("SDLNet_ResolveHost: %s\n",SDLNet_GetError());
		exit(4);
	}

	/* open udp client socket */
	if(!(clientSocket=SDLNet_UDP_Open(0)))
	{
		logger->warn("SDLNet_UDP_Open: %s\n",SDLNet_GetError());
		exit(5);
	}

	/* allocate max packet */
	if(!(out=SDLNet_AllocPacket(512)))
	{
		logger->warn("SDLNet_AllocPacket: %s\n",SDLNet_GetError());
		exit(6);
	}

    out->address.host = serverIP.host;
    out->address.port = serverIP.port;

	if(!(in=SDLNet_AllocPacket(512)))
	{
		logger->warn("SDLNet_AllocPacket: %s\n",SDLNet_GetError());
		exit(6);
	}

	/* bind server address to channel 0 */
	if(SDLNet_UDP_Bind(clientSocket, 0, &serverIP)==-1)
	{
		logger->warn("SDLNet_UDP_Bind: %s\n",SDLNet_GetError());
		exit(7);
	}


    /*
    UDPsocket sd;

    if (SDLNet_Init()< 0){
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] --> fallo inicializacion SDLNET [%s]",SDLNet_GetError());
        exit(-1);
    }

    if(!(sd = SDLNet_UDP_Open(0))) {
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] --> Could not create socket [%s]",SDLNet_GetError());
        exit(-1);
    }

    int hostResolved = SDLNet_ResolveHost(&serverIP,REMOTE_HOST,REMOTE_PORT);

    if (hostResolved == -1){
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] --> server hostname [%s]",SDLNet_GetError());
        exit(-1);
    }else{
        logger->info("[SSNETWORKMANAGER::initConnectionUDP] set [%s]:[%d] --> SERVERIP [%d]:[%d]",REMOTE_HOST,REMOTE_PORT,serverIP.host,serverIP.port);
    }

    if ((host = SDLNet_ResolveIP(&serverIP)) == NULL){
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] --> resolve IP [%s]",SDLNet_GetError());
        exit(-1);
    }else{
        logger->debug("[SSNETWORKMANAGER::initConnectionUDP] --> resolve host [%s]",host);
    }

    packet = SDLNet_AllocPacket(BUFFER_SIZE);
    if ( packet == NULL ){
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] --> Cannot find free enough memory space for packet of size [%d]::[%s]",BUFFER_SIZE,SDLNet_GetError());
        exit(-1);
    }

    packet->address.host = serverIP.host;
    packet->address.port = serverIP.port;

    clientSocket = SDLNet_UDP_Open( LOCAL_PORT );
    //clientSocket = SDLNet_UDP_Open(&serverIP);
    if ( clientSocket == NULL ){
        logger->warn("[SSNETWORKMANAGER::initConnectionUDP] --> error open UDP Socket [%s]",SDLNet_GetError());
        exit(-1);
    }

    logger->info("[SSNETWORKMANAGER::initConnectionUDP] --> UDP Configuration DONE! (CLIENT) sending packets to [%d]:[%d]",packet->address.host,packet->address.port);
    */
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

       indexTramaSend++;
       //-->QRY ACK PACKET (SEND TO SERVER) indexTramaSend:1; indexTramaGet:0
       EventMsg *qryACK = new EventMsg(TRAMA_QRY_CONECTION,indexTramaSend,indexTramaGet,0,1,(uint16_t)0);
       sendMsgToServer(qryACK);
       indexTramaGet++;

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
               logger->info("[SSNETWORKMANAGER::establishCommunicationUDP] --> ACK SERVER ESTABLISHED");
           }else{
               logger->info("[SSNETWORKMANAGER::establishCommunicationUDP] --> ACK SERVER FAILED (CANNOT ACCEPT MORE CLIENTS)");
           }

        }else if(responseACK->getTypeMsg() == TRAMA_NULL){
            logger->warn("[SSNETWORKMANAGER::establishCommunicationUDP] --> ACK SERVER FAILED (CONNECTION FAILED)");
            SDLNet_UDP_Close(clientSocket);
            SDLNet_Quit();
            exit(1);
        }
};


//send one message to REMOTE
void NetworkClientUDP::sendMsgToServer(EventMsg *msg){

    char *data = msg->marshallMsg();
    int size_data = strlen(buffer)+1;
    clearBuffer();

    sprintf(buffer,"%s",data);
    out->len = size_data;

    for(int i=0;i<out->len;i++){out->data[i]=buffer[i];}
    //memcpy(packet->data,buffer,packet->len);

    if (enabledCompression){
        unsigned char *dataCompression = cP->CompressionData((char *)out->data,out->len);
        int size_after_dataCompression = strlen((const char *)dataCompression);
        logger->warn("[SSNETWORKMANAGER::sendMsgToServerUPD] --> size_data_before_compression [%d] size_data_after_compression [%d]",out->len,size_after_dataCompression);
    }

    //if (SDLNet_UDP_Send(clientSocket,-1,packet) == 0){
    if (SDLNet_UDP_Send(clientSocket, 0, out )==0){
        logger->warn("[SSNETWORKMANAGER::sendMsgToServerUDP] --> UDP DATA NOT SEND! [%s]", SDLNet_GetError());
    }else{
        logger->warn("[SSNETWORKMANAGER::sendMsgToServerUDP] --> BUFFER SEND TO [%d]:[%d] [%s] size [%d] CRC[%d]",out->address.host, out->address.port, out->data, out->len, msg->getCRC16());
    }

};

//receive one message from REMOTE.
EventMsg *NetworkClientUDP::getMsgFromServer(){

    bool DONE = false;

    EventMsg *returnMsg = new EventMsg();

    long initialMark = SDL_GetTicks();

    while(!DONE){

          //if (SDLNet_UDP_Recv(clientSocket, packet)){
          if (SDLNet_UDP_Recv(clientSocket, in)){
            std::string data((char *)in->data);
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


