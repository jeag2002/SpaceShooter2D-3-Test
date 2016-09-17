#include "TaskManager.h"



void TaskManager::Run(std::vector<DynamicEntity *> data, int roof, int index){
    ProcessDynamicEntities(data, roof, index);
}


void TaskManager::ProcessEntity(DynamicEntity *dEntity){
    bool isCollision = coll->isCollDynamicElement(dEntity,iThread);
    if (!isCollision){
        anim->isAnimDynamicElement(dEntity,iThread);
        ia->isIADynamicElement(dEntity,iThread);
    }
}

char *TaskManager::indexToChar(int index){

    if (index == 1){
        return "Enemies Roof 1";
    }else if (index == 2){
        return "Enemies Roof 2";
    }else if (index == 3){
        return "Enemies Roof 3";
    }else if (index == 4){
        return "DynEl Roof 1";
    }else if (index == 5){
        return "DynEl Roof 2";
    }else{
        return "DynEl Roof 3";
    }

}

bool TaskManager::processBroadcastMessages(){
    bool res = false;
    pthread_mutex_lock(&lock);

    //struct timeval tv;
    struct timespec ts;
    ts.tv_sec = 100 / 1000;
    ts.tv_nsec = (100 % 1000) * 1000000;

    pthread_cond_timedwait(&dataNotProduced, &lock, &ts);

    if (!qMem->isEmptyMessageOutput()){
        EventMsg *eventMsg = qMem->getMessageOutput();
        if ((eventMsg->getTypeMsg() != 0) && (eventMsg->getIndex() >= index_data)){
            log->debug("[TaskManager-BROADCAST] CreateThread [%08x] GetMSG [%d] index_dataPacket [%d] index_data Expected [%d]",iThread,eventMsg->getTypeMsg(),eventMsg->getIndex(),index_data);
            index_data=index_data+1;
            if (eventMsg->getTypeMsg() == 6){
                res = true;
            }
        }
    }
    pthread_cond_signal(&dataNotConsumed);


    pthread_mutex_unlock(&lock);
    return res;
}


void TaskManager::ProcessDynamicEntities(std::vector<DynamicEntity *> eLvl, int roof, int index){


    bool DONE = false;
    DynamicEntity *dEntity;

    if (sem_wait(&OKToBuyMilk)==0){
        pthread_mutex_lock(&lock);
        iThread = pthread_self();
        int i=0;
        sem_getvalue(&OKToBuyMilk,&i);
        log->debug("TaskManager:: [%s] PID %d CreateThread [%08x] - SEMAPHOR [%d]", indexToChar(index),getpid(), iThread, i);
        sem_post(&Remote);
        sem_post(&OKToBuyMilk);
        pthread_mutex_unlock(&lock);
    }


    while ((!DONE) && (eLvl.size() > 0)){

       if (roof == mem->getRoofIndex()){

           for(int i=0; i<eLvl.size(); i++){

               pthread_mutex_lock(&lock);
               dEntity = eLvl[i];
               eLvl[i]->setBlocked(true);
               pthread_mutex_unlock(&lock);

               if (dEntity->GetState() == DynamicEntity::UNITIALIZED){
                    dEntity->VOnInit();
               }

               if (dEntity->GetState() == DynamicEntity::RUNNING){

                    if (sem_wait(&OKToBuyMilk)==0){
                        pthread_mutex_lock(&lock);
                        iThread = pthread_self();
                        int i=0;
                        sem_getvalue(&OKToBuyMilk,&i);
                        log->debug("TaskManager:: [%s] PID %d Processing Thread [%08x]", indexToChar(index),getpid(), iThread);
                        sem_post(&Remote);
                        sem_post(&OKToBuyMilk);
                        pthread_mutex_unlock(&lock);
                    }

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

               pthread_mutex_lock(&lock);
               eLvl[i]->setDynamicEntity(dEntity);
               eLvl[i]->setBlocked(false);
               pthread_mutex_unlock(&lock);
           }// end for
       }
       DONE = processBroadcastMessages();
    }
}

