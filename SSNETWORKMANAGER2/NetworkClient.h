#ifndef NETWORKCLIENT_H_INCLUDED
#define NETWORKCLIENT_H_INCLUDED

#include "Stdafx.h"
#include "LogEngine.h"
#include "EventMsg.h"

#define BUFFER_SIZE 512
#define SIZE_TRAMA 128
#define NUM_MSGS 4

#define PORT 10022
#define HOST "localhost"

class NetworkClient{

public:

    NetworkClient(LogEngine *_logger){
        logger = _logger;
        inputLength = 0;
        indexTrama = 0;
    };


    ~NetworkClient(){};
    void initCommunication();

    void establishCommunication();
    TCPsocket *incomingCommunication();

    void getListActiveSessions();
    EventMsg *getRemoteIdPlayer();

    void endCommunication();

    int getActTrama(){return indexTrama;}
    void setActTrama(int _indexTrama){indexTrama = _indexTrama;}

    void sendMsgToServer(EventMsg *msg);
    EventMsg *getMsgFromServer();

    void clearBuffer(){
        for(int i=0; i<BUFFER_SIZE; i++){buffer[i] = '\0';}
    }

    void closeClientSocket(){
        SDLNet_TCP_Close(clientSocket);
        SDLNet_Quit();
        exit(1);
    }

    EventMsg **getMsgsFromServer();
    EventMsg **unMarsharMsgsServer(const char *buffer);


private:

IPaddress serverIP;
TCPsocket clientSocket;
SDLNet_SocketSet socketSet;

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
