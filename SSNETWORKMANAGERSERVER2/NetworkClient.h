#ifndef NETWORKCLIENT_H_INCLUDED
#define NETWORKCLIENT_H_INCLUDED

#include "Stdafx.h"
#include "LogEngine.h"
#include "EventMsg.h"

#define BUFFER_SIZE 512
#define TRAMA_SIZE 128

#define PORT 10022
#define HOST "localhost"

//#define MAX_SOCKETS 5
//#define MAX_CLIENT 4

#define MAX_SOCKETS 9
#define MAX_CLIENT 8

class NetworkClient{

public:

    NetworkClient(LogEngine *_logger){
        logger = _logger;
        inputLength = 0;
        indexTrama = 0;
        clientCount = 0;
    };

    ~NetworkClient(){};
    void initCommunication();

    void establishCommunication();
    void processACKTrama(TCPsocket client, bool res);

    void endCommunication();

    int getActTrama(){return indexTrama;}
    void setActTrama(int _indexTrama){indexTrama = _indexTrama;}

    EventMsg *getMsgFromClient(TCPsocket clientSocket);


    void sendMsgToClient(TCPsocket clientSocket,EventMsg *msg);
    void sendFourMsgToClient(TCPsocket clientSocket,EventMsg *msg_1, EventMsg *msg_2, EventMsg *msg_3, EventMsg *msg_4);
    char *serializeFourMsg(EventMsg *msg_1, EventMsg *msg_2, EventMsg *msg_3, EventMsg *msg_4);



    void clearBuffer(){
        for(int i=0; i<BUFFER_SIZE; i++){buffer[i] = '\0';}
    }

    TCPsocket *getClientSockets(){return clientSocket;}

    void setClientSocketFree(int indexClientSocket){
        clientSocket[indexClientSocket] = NULL;
        freeSocket[indexClientSocket] = true;
    }

    void closeClient(TCPsocket clientSocket){
        SDLNet_TCP_DelSocket(socketSet, clientSocket);
        SDLNet_TCP_Close(clientSocket);
    }

private:

IPaddress serverIP;
TCPsocket serverSocket;
SDLNet_SocketSet socketSet;

TCPsocket clientSocket[MAX_CLIENT];
bool freeSocket[MAX_CLIENT];

int numActiveSockets;
int clientCount;

std::string userInput;
int inputLength;
char buffer[BUFFER_SIZE];

LogEngine *logger;
const char *host;

int activeSockets;
int gotServerResponse;

int indexTrama;

};

#endif // NETWORKCLIENT_H_INCLUDED
