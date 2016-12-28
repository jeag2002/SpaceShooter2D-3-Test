#ifndef TCPSESSION_H_INCLUDED
#define TCPSESSION_H_INCLUDED

#include "NetworkClient.h"
#include "MemManager.h"
#include "Concurrent_queue.h"

#define MAX_CLIENT_SESSION 4

class TCPSession{


public:

    TCPSession(LogEngine *_logger, MemManager *_mem, NetworkClient *_nClient, Concurrent_queue *_cQ){
        logger = _logger;
        mem = _mem;
        nClient = _nClient;
        cQ = _cQ;
        numPlayers = 0;
        maxPlayers = 4;

        for(int loop=0; loop<MAX_CLIENT_SESSION; loop++){
            freeSocket[loop] = false;
            clientSocket[loop] = NULL;
         }
    }

    ~TCPSession(){
    }

    void Run();

private:

void processInputMsgFromClient(TCPsocket client, int index, EventMsg *inputMsg);
void sendServerDataToClient(TCPsocket client, EventMsg *inputMsg);
void processCommandsFromClient(TCPsocket client, EventMsg *inputMsg);


int numPlayers;
int maxPlayers;

TCPsocket clientSocket[MAX_CLIENT_SESSION];
bool freeSocket[MAX_CLIENT_SESSION];

LogEngine *logger;
MemManager *mem;
Concurrent_queue *cQ;
NetworkClient *nClient;

};

#endif // TCPSESSION_H_INCLUDED
