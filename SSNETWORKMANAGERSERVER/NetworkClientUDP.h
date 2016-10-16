#ifndef NETWORKCLIENTUDP_H_INCLUDED
#define NETWORKCLIENTUDP_H_INCLUDED

#include "Stdafx.h"
#include "LogEngine.h"
#include "EventMsg.h"
#include "CompressPacket.h"

#define BUFFER_SIZE 512
#define SIZE_TRAMA 128
#define MAX_DELAY 500

#define REMOTE_PORT 10022
#define LOCAL_PORT 8888

#define SIZE_REMOTE_ELEMS 21

#define REMOTE_HOST "127.0.0.1"


class NetworkClientUDP{

public:

NetworkClientUDP(LogEngine *_logger){
    logger = _logger;
    clearBuffer();
    cP = new CompressPacket(logger);
    enabledCompression = false;
    enabledCompression = cP->Init();
    pthread_mutex_init(&pushData, NULL);

}

~NetworkClientUDP(){
    SDLNet_UDP_Close(serverSocket);
    SDLNet_FreePacket(packet);
    SDLNet_FreePacketV(out);
    SDLNet_Quit();
};

void initCommunicationUDP();

void clearBuffer(){
    for(int i=0; i<BUFFER_SIZE; i++){
            buffer[i] = '\0';
    }
}

void clearBufferPacket(){
    for(int i=0; i<BUFFER_SIZE; i++){
            packet->data[i] = '\0';
    }
}

void clearBufferPacket(UDPpacket *packetUDP){
    for(int i=0; i<BUFFER_SIZE; i++){
            packetUDP->data[i] = '\0';
    }
}


void sendMsgVectorToClientUDP(EventMsg **msgs);
void sendMsgToClientUDP(EventMsg *msg);
void sendBuffMsgToClientUDP(EventMsg *msg[]){}
EventMsg *getMsgFromClientUDP();
EventMsg **getBuffMsgToClientUDP(){EventMsg **buff; return buff;}

UDPsocket getUDPSocket(){return serverSocket;}
UDPpacket *getUDPPacket(){return packet;}


private:

LogEngine *logger;
IPaddress serverIP;
UDPpacket *packet;
UDPsocket serverSocket;
UDPpacket **out;

std::string host;
char buffer[BUFFER_SIZE];


CompressPacket *cP;
bool enabledCompression;

pthread_mutex_t pushData;


};

#endif // NETWORKCLIENTUDP_H_INCLUDED
