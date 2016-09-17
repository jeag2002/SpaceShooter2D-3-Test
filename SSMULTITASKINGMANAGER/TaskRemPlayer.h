#ifndef TASKREMPLAYER_H_INCLUDED
#define TASKREMPLAYER_H_INCLUDED

#include "Stdafx.h"
#include "MemManager.h"
#include "QueueManager.h"
#include "LogEngine.h"

#include "CollisionEntities.h"
#include "AnimationEntities.h"
#include "IAEntities.h"

#define SIZE 500

class TaskRemPlayer{

public:

TaskRemPlayer(LogEngine *_log, MemManager *_mem, QueueManager *_qMem, pthread_mutex_t _lock, sem_t _OKToBuyMilk, sem_t _Remote){
    mem = _mem;
    log = _log;
    qMem = _qMem;
    lock = _lock;
    OKToBuyMilk = _OKToBuyMilk;
    Remote = _Remote;


    coll = new CollisionEntities(mem,_log, _lock, OKToBuyMilk, Remote);
    anim = new AnimationEntities(mem,_log, _lock, OKToBuyMilk, Remote);
    ia = new IAEntities(mem,_log, _lock, OKToBuyMilk, Remote);

    remPlayers = mem->getRemPlayer();
}

~TaskRemPlayer(){}
void Run();
void PrintLog(const std::string fmt, ...);


private:

QueueManager *qMem;
MemManager *mem;
LogEngine *log;
pthread_t iThread;
pthread_mutex_t lock;
sem_t OKToBuyMilk;
sem_t Remote;

CollisionEntities *coll;
AnimationEntities *anim;
IAEntities *ia;

std::vector<DynamicEntity *>remPlayers;

void ProcessEntity(DynamicEntity *dEntity);

};



#endif // TASKREMPLAYER_H_INCLUDED
