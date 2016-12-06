#ifndef QUEUEMANAGER_H_INCLUDED
#define QUEUEMANAGER_H_INCLUDED

#include "MemManager.h"
#include "EventMsg.h"
#include <queue>
#include "NetworkClientUDP.h"
#include "LogEngine.h"
#include "PredictionEngine.h"
#include "ClockEngine.h"

#define SIZE_REMOTE_ELEMS 22
#define TIME_BETWEEN_ACT_SERVER 50
#define TIMEOUT 2000
#define QUEUE_PORT 63000

class QueueManager{

public:

QueueManager(LogEngine *_log, MemManager *_mem, NetworkClientUDP *_nClientUDP, PredictionEngine *_pEngine, playerDataType _pDT){
    log = _log;
    mem = _mem;

    nClientUDP = _nClientUDP;

    pEngine = _pEngine;
    nClock = new ClockEngine(100);
    runAsLocal = true;

    pDT = _pDT;

}

void processRemoteMsg(EventMsg *inputMsg);
~QueueManager(){
    //delete nClientQueue;
}

void setRunAsLocal(bool _runAsLocal){runAsLocal = _runAsLocal;}
bool isRunAsLocal(){return runAsLocal;}

void runRemoteData();
void runLocalData();

private:
    LogEngine *log;
    MemManager *mem;

    NetworkClientUDP *nClientUDP;
    //NetworkClientUDP *nClientQueue;

    ClockEngine *nClock;
    std::queue<EventMsg *> dataFromServer; //
    std::queue<EventMsg *> msgFromServer;  //
    PredictionEngine *pEngine;
    bool runAsLocal;

    playerDataType pDT;

};

#endif // QUEUEMANAGER_H_INCLUDED
