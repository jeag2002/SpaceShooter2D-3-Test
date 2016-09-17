#ifndef TASKMANAGER_H_INCLUDED
#define TASKMANAGER_H_INCLUDED

#include "Stdafx.h"
#include "MemManager.h"
#include "QueueManager.h"
#include "LogEngine.h"
#include "Subject.h"

#include "CollisionEntities.h"
#include "AnimationEntities.h"
#include "IAEntities.h"

#define SIZE 500

class TaskManager{

public:

TaskManager(LogEngine *_log, MemManager *_mem, QueueManager *_qMem, pthread_mutex_t _lock, pthread_cond_t _dataNotProduced,  pthread_cond_t _dataNotConsumed, sem_t _OKToBuyMilk, sem_t _Remote){

    mem = _mem;
    log = _log;
    qMem = _qMem;
    lock = _lock;
    dataNotProduced = _dataNotProduced;
    dataNotConsumed = _dataNotConsumed;

    OKToBuyMilk = _OKToBuyMilk;
    Remote = _Remote;

    coll = new CollisionEntities(mem,_log, _lock, OKToBuyMilk, Remote);
    anim = new AnimationEntities(mem,_log, _lock, OKToBuyMilk, Remote);
    ia = new IAEntities(mem,_log, _lock, OKToBuyMilk, Remote);

    index_data = 0;

}

~TaskManager(){}

void Run(std::vector<DynamicEntity *> eLvl, int roof, int index);


private:

void ProcessDynamicEntities(std::vector<DynamicEntity *> eLvl, int roof, int index);
void ProcessEntity(DynamicEntity *dEntity);
//void PrintLog(int index, const std::string fmt, ...);
char *indexToChar(int index);
bool processBroadcastMessages();



MemManager *mem;
QueueManager *qMem;
LogEngine *log;
pthread_t iThread;
pthread_mutex_t lock;
pthread_cond_t dataNotProduced;
pthread_cond_t dataNotConsumed;

int index_data = 0;

sem_t OKToBuyMilk;
sem_t Remote;

CollisionEntities *coll;
AnimationEntities *anim;
IAEntities *ia;
Subject *sub;

};

#endif // TASKMANAGER_H_INCLUDED
