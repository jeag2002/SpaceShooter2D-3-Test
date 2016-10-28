#ifndef QUEUEMANAGER_H_INCLUDED
#define QUEUEMANAGER_H_INCLUDED

#include "MemManager.h"
#include "EventMsg.h"
#include <queue>
#include "NetworkClient.h"
#include "LogEngine.h"
#include "PredictionEngine.h"
#include "ClockEngine.h"

class QueueManager{

public:

QueueManager(LogEngine *_log, MemManager *_mem, NetworkClient *_nClient, PredictionEngine *_pEngine, SDL_mutex *_blockMem, SDL_mutex *_blockSock, SDL_cond *_prodMem, SDL_cond *_consMem, SDL_cond *_prodSock, SDL_cond *_consSock){
    log = _log;
    mem = _mem;
    nClient = _nClient;
    pEngine = _pEngine;
    nClock = new ClockEngine(100);
    runAsLocal = true;

    blockMem = _blockMem;
    blockSock = _blockSock;
    prodMem = _prodMem;
    consMem = _consMem;
    prodSock = _prodSock;
    consSock = _consSock;

}


void processRemoteMsg(EventMsg *inputMsg);


~QueueManager(){}

void setRunAsLocal(bool _runAsLocal){runAsLocal = _runAsLocal;}
bool isRunAsLocal(){return runAsLocal;}

void runRemoteData();
void runLocalData();


private:
    LogEngine *log;
    MemManager *mem;
    NetworkClient *nClient;
    ClockEngine *nClock;
    std::queue<EventMsg *> dataFromServer; //
    std::queue<EventMsg *> msgFromServer;  //
    PredictionEngine *pEngine;
    bool runAsLocal;

    SDL_mutex *blockMem;
    SDL_mutex *blockSock;

    SDL_cond *prodMem;
    SDL_cond *consMem;

    SDL_cond *prodSock;
    SDL_cond *consSock;

};

#endif // QUEUEMANAGER_H_INCLUDED
