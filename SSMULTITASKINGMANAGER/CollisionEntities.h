#ifndef COLLISIONENTITIES_H_INCLUDED
#define COLLISIONENTITIES_H_INCLUDED

#include "MemManager.h"
#include "LogEngine.h"

class CollisionEntities{

public:
    CollisionEntities(MemManager *_mem, LogEngine *_log, pthread_mutex_t _lock, sem_t _OKToBuyMilk, sem_t _Remote){
        mem = _mem;
        logger = _log;
        lock = _lock;
        OKToBuyMilk = _OKToBuyMilk;
        Remote = _Remote;
    }

    ~CollisionEntities(){}

    bool isCollDynamicElement(DynamicEntity *ent, pthread_t iThread);
    bool isCollDynamicPlayer(DynamicPlayer *ent, pthread_t iThread);

private:

    MemManager *mem;
    LogEngine *logger;
    pthread_mutex_t lock;
    sem_t OKToBuyMilk;
    sem_t Remote;

};


#endif // COLLISIONENTITIES_H_INCLUDED
