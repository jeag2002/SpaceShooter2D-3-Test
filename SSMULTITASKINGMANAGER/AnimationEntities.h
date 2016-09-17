#ifndef ANIMATIONENTITIES_H_INCLUDED
#define ANIMATIONENTITIES_H_INCLUDED

#include "MemManager.h"
#include "LogEngine.h"

class AnimationEntities{

public:
    AnimationEntities(MemManager *_mem, LogEngine *_log, pthread_mutex_t _lock, sem_t _OKToBuyMilk, sem_t _Remote){
        mem = _mem;
        log = _log;
        lock = _lock;
        OKToBuyMilk = _OKToBuyMilk;
        Remote = _Remote;
    }

    ~AnimationEntities(){
    }

    bool isAnimDynamicElement(DynamicEntity *ent, pthread_t iThread){
        if (sem_wait(&OKToBuyMilk)==0){
        pthread_mutex_lock(&lock);
        log->debug("[AnimationEntities::isAnimDynamicElement] Thread[%08x] processing Animation element ID [%d]",iThread,ent->getIDDE());
        pthread_mutex_unlock(&lock);
        sem_post(&Remote);
        sem_post(&OKToBuyMilk);
        }
        return false;
    }
    bool isAnimDynamicPlayer(DynamicPlayer *ent, pthread_t iThread){
        if (sem_wait(&OKToBuyMilk)==0){
        pthread_mutex_lock(&lock);
        log->debug("[AnimationEntities::isAnimDynamicElement] Thread[%08x] processing Animation player ID [%d]",iThread,ent->getIndexPlayer());
        pthread_mutex_unlock(&lock);
        sem_post(&Remote);
        sem_post(&OKToBuyMilk);
        }
        return false;
    }

private:

    LogEngine *log;
    MemManager *mem;
    pthread_mutex_t lock;
    sem_t OKToBuyMilk;
    sem_t Remote;

};




#endif // ANIMATIONENTITIES_H_INCLUDED
