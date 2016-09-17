#include "TaskRemPlayer.h"

/*
void TaskRemPlayer::PrintLog(const std::string fmt, ...){
    if (sem_wait(&OKToBuyMilk)==0){
        pthread_mutex_lock(&lock);
        iThread = pthread_self();
        int i=0;
        sem_getvalue(&OKToBuyMilk,&i);

        va_list ap;
        char msg[SIZE];
        for(int i=0;i<SIZE; i++){msg[i]='\0';}

        va_start(ap, fmt);
        int size_msg = vsnprintf(msg, (sizeof(msg)/sizeof(*msg))-1, fmt.c_str(), ap);

        PrintLog("TaskRemPlayer:: PID %d [%08x] - SEMAPHOR [%d] - %s",getpid(),iThread,i, msg);
        sem_post(&Remote);
        sem_post(&OKToBuyMilk);
        pthread_mutex_unlock(&lock);
    }
}
*/


void TaskRemPlayer::Run(){

    if (sem_wait(&OKToBuyMilk)==0){
        pthread_mutex_lock(&lock);
        iThread = pthread_self();
        int i=0;
        sem_getvalue(&OKToBuyMilk,&i);
        log->debug("TaskRemPlayer:: PID %d CreateThread [%08x] - SEMAPHOR [%d]",getpid(), iThread, i);
        sem_post(&Remote);
        sem_post(&OKToBuyMilk);
        pthread_mutex_unlock(&lock);
    }


    bool DONE = false;

    while (!DONE) {

       for(int i=0; i<remPlayers.size(); i++){
            DynamicEntity *dEntity = remPlayers[i];

            if (dEntity->GetState() == DynamicEntity::UNITIALIZED){
                dEntity->VOnInit();
            }

            if (dEntity->GetState() == DynamicEntity::RUNNING){
                dEntity->VOnUpdate(100,iThread);
                ProcessEntity(dEntity);
            }

            if (dEntity->isDead()){

                switch(dEntity->GetState()){
                    case DynamicEntity::SUCCEED:
                        dEntity->VOnSuccess();
                    break;

                    case DynamicEntity::FAILED:
                        dEntity->VOnFail();
                    break;

                    case DynamicEntity::ABORTED:
                        dEntity->VOnAbort();
                    break;

                }
            }
       }

       //DONE = true;
    }

}


void TaskRemPlayer::ProcessEntity(DynamicEntity *dEntity){
    coll->isCollDynamicElement(dEntity,iThread);
    anim->isAnimDynamicElement(dEntity,iThread);
    ia->isIADynamicElement(dEntity,iThread);
}
