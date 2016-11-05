#ifndef NETWORKCLIENTUDP_H_INCLUDED
#define NETWORKCLIENTUDP_H_INCLUDED

#include "Stdafx.h"
#include "LogEngine.h"
#include "EventMsg.h"
#include "CompressPacket.h"

#define BUFFER_SIZE 512
#define SIZE_TRAMA 128
#define MAX_DELAY 2000

#define REMOTE_PORT 8888
#define LOCAL_PORT 10022

#define REMOTE_HOST "127.0.0.1"

#define PACKETS 22


class NetworkClientUDP{

public:

NetworkClientUDP(LogEngine *_logger){
    logger = _logger;

    logPackets = new LogEngine();
    logPackets->setOwnFile("TRAMACLIENT.log");
    logPackets->deleteLogFile();
    logPackets->startUp(1,0);

    indexTramaSend = 1;
    indexTramaGet = 0;

    send_mutex = SDL_CreateMutex();
    get_mutex = SDL_CreateMutex();

    clearBuffer();
    cP = new CompressPacket(logger);
    enabledCompression = false;
    enabledCompression = cP->Init();

}

~NetworkClientUDP(){
    delete logPackets;
    SDLNet_UDP_Close(clientSocket);
    SDLNet_FreePacket(packet);
    SDLNet_Quit();
    exit(1);
};

int getIndexTramaSend(){return indexTramaSend;}
void setIndexTramaSend(int _indexTramaSend){indexTramaSend = _indexTramaSend;}

int getIndexTramaGet(){return indexTramaGet;}
void setIndexTramaGet(int _indexTramaGet){indexTramaGet = _indexTramaGet;}


void clearBuffer(){
    for(int i=0; i<BUFFER_SIZE; i++){buffer[i] = '\0';}
}

void clearBufferPacket(){
    for(int i=0; i<BUFFER_SIZE; i++){packet->data[i] = '\0';}
}

void clearBufferPacket(UDPpacket *packetUDP){
    for(int i=0; i<BUFFER_SIZE; i++){packetUDP->data[i] = '\0';}
}

UDPpacket *getRemotePacket(){return packet;}

void sendMsgToServer(EventMsg *msg);

EventMsg *getMsgFromServer();
EventMsg **getMsgsFromServer();

void initCommunicationUDP(int localPort);
void establishCommunicationUDP();
void getListActiveSessions();
void registerToActiveSession(int mapClient, int sessionClient);


private:




IPaddress serverIP;
UDPsocket clientSocket;
UDPpacket *packet;

UDPpacket *in;
UDPpacket *out;

const char *host;

CompressPacket *cP;
bool enabledCompression;

SDLNet_SocketSet socketSet;

char buffer[BUFFER_SIZE];

LogEngine *logger;
LogEngine *logPackets;

int indexTramaSend;
int indexTramaGet;

SDL_mutex *send_mutex;
SDL_mutex *get_mutex;

};

#endif // NETWORKCLIENTUDP_H_INCLUDED
