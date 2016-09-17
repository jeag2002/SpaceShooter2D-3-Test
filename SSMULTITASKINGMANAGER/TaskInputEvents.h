#ifndef TASKINPUTEVENTS_H_INCLUDED
#define TASKINPUTEVENTS_H_INCLUDED

#include <pthread.h>
#include <SDL.h>
#include "MemManager.h"
#include "QueueManager.h"
#include "LogEngine.h"
#include "Subject.h"

#include "CollisionEntities.h"
#include "AnimationEntities.h"
#include "IAEntities.h"

class TaskInputEvents{

public:

TaskInputEvents(LogEngine *_log, MemManager *_mem, QueueManager *_qMem, Subject *_sub, pthread_mutex_t _lock, pthread_cond_t _dataNotProduced,  pthread_cond_t _dataNotConsumed, sem_t _OKToBuyMilk, sem_t _Remote){

    this->logger = _log;
    this->mem = _mem;
    this->qMem = _qMem;
    this->lock = _lock;
    this->sub = _sub;

    this->dataNotProduced = _dataNotProduced;
    this->dataNotConsumed = _dataNotConsumed;

    OKToBuyMilk = _OKToBuyMilk;
    Remote = _Remote;

    coll = new CollisionEntities(mem,_log, _lock, OKToBuyMilk, Remote);
    anim = new AnimationEntities(mem,_log, _lock, OKToBuyMilk, Remote);
    ia = new IAEntities(mem,_log, _lock, OKToBuyMilk, Remote);
}

~TaskInputEvents(){}
bool getEventPollsThreadSafe(SDL_Event *event);

void Run();

private:

void processLocalPlayer();
void evalLocalPlayerAgainstEnv(DynamicPlayer *dPlayer);

CollisionEntities *coll;
AnimationEntities *anim;
IAEntities *ia;

MemManager *mem;
QueueManager *qMem;
LogEngine *logger;
Subject *sub;

sem_t OKToBuyMilk;
sem_t Remote;

pthread_t iThread;

pthread_mutex_t lock;
pthread_cond_t dataNotProduced;
pthread_cond_t dataNotConsumed;



};

#endif // TASKINPUTEVENTS_H_INCLUDED
