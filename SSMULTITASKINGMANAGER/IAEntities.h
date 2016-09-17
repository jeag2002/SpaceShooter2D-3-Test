#ifndef IAENTITIES_H_INCLUDED
#define IAENTITIES_H_INCLUDED

#include "MemManager.h"
#include "LogEngine.h"

class IAEntities{

public:
    IAEntities(MemManager *_mem, LogEngine *_log, pthread_mutex_t _lock, sem_t _OKToBuyMilk, sem_t _Remote){
        mem = _mem;
        log = _log;
        lock = _lock;
        OKToBuyMilk = _OKToBuyMilk;
        Remote = _Remote;
    }

    ~IAEntities(){
    }

    bool isIADynamicElement(DynamicEntity *ent,pthread_t iThread){
        if (sem_wait(&OKToBuyMilk)==0){
            pthread_mutex_lock(&lock);
            log->debug("[IAEntities::isIADynamicElement] Thread [%08x] processing IA element ID [%d]",iThread, ent->getIDDE());
            pthread_mutex_unlock(&lock);
            sem_post(&Remote);
            sem_post(&OKToBuyMilk);
        }
        return false;
    }
    bool isIADynamicPlayer(DynamicPlayer *ent,pthread_t iThread){
        if (sem_wait(&OKToBuyMilk)==0){
            pthread_mutex_lock(&lock);
            log->debug("[IAEntities::isIADynamicPlayer] Thread [%08x] processing IA player ID [%d]", iThread, ent->getIndexPlayer());
            pthread_mutex_unlock(&lock);
            sem_post(&Remote);
            sem_post(&OKToBuyMilk);
        }
        return false;
    }


private:

    MemManager *mem;
    LogEngine *log;
    pthread_mutex_t lock;
    sem_t OKToBuyMilk;
    sem_t Remote;


};



#endif // IAENTITIES_H_INCLUDED
