#ifndef NETWORKCLIENTUDP_H_INCLUDED
#define NETWORKCLIENTUDP_H_INCLUDED

#include "Stdafx.h"
#include "LogEngine.h"
#include "EventMsg.h"
#include "CompressPacket.h"

#define BUFFER_SIZE 512
#define SIZE_TRAMA 128
#define MAX_DELAY 500

/*
#define REMOTE_PORT 8888
#define LOCAL_PORT 10022
*/

#define REMOTE_PORT 10022
#define LOCAL_PORT 8888

#define REMOTE_HOST "localhost"

#define MAX_SOCKETS 9
#define MAX_CLIENT 8


class NetworkClientUDP{

public:

NetworkClientUDP(LogEngine *_logger){
    logger = _logger;
    indexTramaSend = 1;
    indexTramaGet = 0;
    clearBuffer();
    cP = new CompressPacket(logger);
    enabledCompression = false;
    enabledCompression = cP->Init();

}

~NetworkClientUDP(){
    SDLNet_FreeSocketSet(socketSet);
    SDLNet_UDP_Close(serverSocket);
    SDLNet_Quit();
};

void initCommunicationUDP();

void clearBuffer(){
    for(int i=0; i<BUFFER_SIZE-1; i++){buffer[i] = '0';}
    buffer[BUFFER_SIZE-1] = '\0';
}

/*
int getIndexTramaSend(){return indexTramaSend;}
void setIndexTramaSend(int _indexTramaSend){indexTramaSend = _indexTramaSend;}

int getIndexTramaGet(){return indexTramaGet;}
void setIndexTramaGet(int _indexTramaGet){indexTramaGet = _indexTramaGet;}

*/

void sendMsgToClientUDP(EventMsg *msg);
EventMsg *getMsgFromClientUDP();

SDLNet_SocketSet getSocketSet(){return socketSet;}
UDPsocket getUDPSocket(){return serverSocket;}
UDPpacket *getUDPPacket(){return packet;}

//EventMsg *evaluatingIncomingPackets();


private:

IPaddress serverIP;
UDPsocket serverSocket;
UDPpacket *packet;
const char *host;

CompressPacket *cP;
bool enabledCompression;

SDLNet_SocketSet socketSet;
//UDPsocket clientSocket[MAX_CLIENT];
UDPpacket *clientPackets[MAX_CLIENT];
bool freeSocket[MAX_CLIENT];

char buffer[BUFFER_SIZE];
LogEngine *logger;

int indexTramaSend;
int indexTramaGet;

EventMsg *generatingACKPackets(int tramaSend,
                               int tramaGet,
                               int _OK,
                               UDPpacket *packet);
void establishCommunicationUDP(EventMsg *ackTrama);

};

#endif // NETWORKCLIENTUDP_H_INCLUDED
