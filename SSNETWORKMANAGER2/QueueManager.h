#ifndef QUEUEMANAGER_H_INCLUDED
#define QUEUEMANAGER_H_INCLUDED

#include "MemManager.h"
#include "EventMsg.h"
#include <queue>
#include "NetworkClientUDP.h"
#include "LogEngine.h"
#include "PredictionEngine.h"
#include "ClockEngine.h"
#include "Subject.h"

#define SIZE_REMOTE_ELEMS 22
#define TIME_BETWEEN_ACT_SERVER 50
#define TIMEOUT 2000
#define QUEUE_PORT 63000

class QueueManager{

public:

QueueManager(LogEngine *_log, MemManager *_mem, NetworkClientUDP *_nClientUDP, PredictionEngine *_pEngine, playerDataType _pDT, SDL_cond *_cond, Subject *_sub, SDL_Window* _window, SDL_Renderer *_render, TTF_Font *_font){
    log = _log;
    mem = _mem;

    nClientUDP = _nClientUDP;
    pEngine = _pEngine;
    nClock = new ClockEngine(100);
    runAsLocal = true;

    nQueueManager = SDL_CreateMutex();
    cond = _cond;

    pDT = _pDT;

    sub = _sub;
    window = _window;
    render = _render;
    font = _font;

    DONE = false;
}

void processRemoteMsg(EventMsg *inputMsg);

~QueueManager(){}

void setRunAsLocal(bool _runAsLocal){runAsLocal = _runAsLocal;}
bool isRunAsLocal(){return runAsLocal;}

void runRemoteData();
void remoteRemoteProcessData();
void renderScenario();

void runLocalData();

bool getDONE(){return DONE;}
void setDONE(bool _DONE){DONE = _DONE;}

private:
    LogEngine *log;
    MemManager *mem;

    NetworkClientUDP *nClientUDP;
    SDL_mutex *nQueueManager;
    SDL_cond *cond;

    bool DONE;
    ClockEngine *nClock;
    std::queue<EventMsg *> dataFromServer; //
    std::queue<EventMsg *> msgFromServer;  //
    PredictionEngine *pEngine;
    bool runAsLocal;

    playerDataType pDT;

    Subject *sub;
    SDL_Window* window;
    SDL_Renderer *render;
    TTF_Font *font;
    long lowTime = 0;


};

#endif // QUEUEMANAGER_H_INCLUDED
