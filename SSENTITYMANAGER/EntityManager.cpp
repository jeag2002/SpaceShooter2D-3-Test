#include "EntityManager.h"


Entity *EntityManager::getEntity(int key){
    Entity *ent = new Entity();
    if (key >= 200){
        ent = getActorEntity(key);
    }
    return ent;
}



ActorEntity *EntityManager::getActorEntity(int key){


        assert(key >= 200 && "key reference for an Actor must be 200 or higher");


        #ifdef PROFILING
        char msgProfiling[200];
        for(int i=0;i<200;i++){msgProfiling[i]='\0';}
        sprintf(msgProfiling,"getActorEntity key %d",key);
        pEngine->setRefIniTime(msgProfiling);
        #endif // NDEBUG


        ActorEntity *aE = new ActorEntity();
        ActorEntity *aECopy = mem->getActorEntity(key);
        if (aECopy != NULL){
            log->debug("[EntityManager::getActorEntity] get Actor Key from CACHE [%d]",key);
            pEngine->setMsg("\tfind Actor Cache Engine");
            aE->copyTo(aECopy);
            delete aECopy;
        }else{

            log->debug("[EntityManager::getActorEntity] get Actor Key from DB [%d]",key);

            #ifdef PROFILING
            pEngine->setMsg("\tnot find Actor in Cache Engine,requested from DB");
            char msgProfActorSize[200];
            for(int i=0;i<200;i++){msgProfActorSize[i]='\0';}
            sprintf(msgProfActorSize,"\t\tsize of cache Engine before set new actor [%d] - [%d]",key,mem->getActorEntityCapacity());
            pEngine->setMsg(msgProfActorSize);
            #endif // NDEBUG

            char inputQuery[1000];
            for (int i=0; i<1000; i++){inputQuery[i]='\0';}

            sprintf(inputQuery,ACTOR_QUERY,key);
            char **data = dbConn->queryConn(inputQuery);

            //int size_data = sizeof(data)/sizeof(data[0]);

            //if (size_data > 4){
                aE->marshallActorEntity(data);
                mem->setActorEntity(key,aE);
            //}

            #ifdef PROFILING
            for(int i=0;i<200;i++){msgProfActorSize[i]='\0';}
            sprintf(msgProfActorSize,"\t\tsize of cache Engine after set new actor [%d] - [%d]",key,mem->getActorEntityCapacity());
            pEngine->setMsg(msgProfActorSize);
            #endif

        }

        #ifdef PROFILING
        for(int i=0;i<200;i++){msgProfiling[i]='\0';}
        sprintf(msgProfiling,"getActorEntity key %d",key);
        pEngine->setRefFinTime(msgProfiling);
        for(int i=0;i<200;i++){msgProfiling[i]='\0';}
        #endif

        return aE;
}
