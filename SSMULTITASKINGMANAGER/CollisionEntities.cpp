#include "CollisionEntities.h"


 bool CollisionEntities::isCollDynamicPlayer(DynamicPlayer *ent, pthread_t iThread){

    bool res = false;

    std::vector<DynamicEntity *>enemies = mem->getEnemiesByLevel(ent->getActLevel());
    std::vector<DynamicEntity *>dynelements = mem->getDynElemByLevel(ent->getActLevel());
    std::vector<DynamicEntity *>remPlayers = mem->getRemPlayer();


    res = (mem->getPlayer_1()->getActLevel() == ent->getActLevel()) &&
          (mem->getPlayer_1()->getIndexPlayer() != ent->getIndexPlayer()) &&
          (!mem->getPlayer_1()->isLocked()) &&
          (mem->getPlayer_1()->getX() == ent->getX()) &&
          (mem->getPlayer_1()->getY() == ent->getY());

    if (res){
        if (sem_wait(&OKToBuyMilk)==0){
        pthread_mutex_lock(&lock);
        logger->debug("[COLLISION] Thread[%08x] Player [%d] (%f,%f) collides Player [%d] (%f,%f)", iThread, ent->getIndexPlayer(), ent->getX(), ent->getY(), mem->getPlayer_1()->getIndexPlayer(), mem->getPlayer_1()->getX(), mem->getPlayer_1()->getY());
        pthread_mutex_unlock(&lock);
        sem_post(&Remote);
        sem_post(&OKToBuyMilk);
        }
    }

    res = res ||
              ((mem->getPlayer_2()->getActLevel() == ent->getActLevel()) &&
              (mem->getPlayer_2()->getIndexPlayer() != ent->getIndexPlayer()) &&
              (!mem->getPlayer_2()->isLocked()) &&
              (mem->getPlayer_2()->getX() == ent->getX()) &&
              (mem->getPlayer_2()->getY() == ent->getY()));

    if (res){
        if (sem_wait(&OKToBuyMilk)==0){
        pthread_mutex_lock(&lock);
        logger->debug("[COLLISION] Thread[%08x] Player [%d] (%f,%f) collides Player [%d] (%f,%f)", iThread, ent->getIndexPlayer(), ent->getX(), ent->getY(), mem->getPlayer_2()->getIndexPlayer(), mem->getPlayer_2()->getX(), mem->getPlayer_2()->getY());
        pthread_mutex_unlock(&lock);
        sem_post(&Remote);
        sem_post(&OKToBuyMilk);
        }
    }

    res = res ||
              ((mem->getPlayer_3()->getActLevel() == ent->getActLevel()) &&
              (mem->getPlayer_3()->getIndexPlayer() != ent->getIndexPlayer()) &&
              (!mem->getPlayer_3()->isLocked()) &&
              (mem->getPlayer_3()->getX() == ent->getX()) &&
              (mem->getPlayer_3()->getY() == ent->getY()));

    if (res){
        if (sem_wait(&OKToBuyMilk)==0){
        pthread_mutex_lock(&lock);
        logger->debug("[COLLISION] Thread[%08x] Player [%d] (%f,%f) collides Player [%d] (%f,%f)", iThread, ent->getIndexPlayer(), ent->getX(), ent->getY(), mem->getPlayer_3()->getIndexPlayer(), mem->getPlayer_3()->getX(), mem->getPlayer_3()->getY());
        pthread_mutex_unlock(&lock);
        sem_post(&Remote);
        sem_post(&OKToBuyMilk);
        }
    }

    //enemigos
    if (!res){
        for(int i=0; ((i<enemies.size()) && (!res)); i++){
           DynamicEntity *_entity = enemies[i];
            if (ent->getIndexPlayer() != _entity->getIDDE()){
                if (!_entity->isBlocked()){
                    res = ((ent->getX() == _entity->getX()) && (ent->getY() == _entity->getY()));
                    if (res){
                        if (sem_wait(&OKToBuyMilk)==0){
                        pthread_mutex_lock(&lock);
                        logger->debug("[COLLISION] Thread[%08x] Player [%d] (%f,%f) collides with enemy [%d] (%f,%f)", iThread, ent->getIndexPlayer(), ent->getX(), ent->getY(), _entity->getIDDE(), _entity->getX(), _entity->getY());
                        pthread_mutex_unlock(&lock);
                        sem_post(&Remote);
                        sem_post(&OKToBuyMilk);
                        }
                    }
                }
            }
        }
    }

    //elementos dinamicos
    if (!res){
        for(int i=0; ((i<dynelements.size()) && (!res)); i++){
            DynamicEntity *_entity = dynelements[i];
            if (ent->getIndexPlayer() != _entity->getIDDE()){
                if (!_entity->isBlocked()){
                    res = ((ent->getX() == _entity->getX()) && (ent->getY() == _entity->getY()));
                    if (res){
                        if (sem_wait(&OKToBuyMilk)==0){
                        pthread_mutex_lock(&lock);
                        logger->debug("[COLLISION] Thread[%08x] Player [%d] (%f,%f) collides with dynenemy [%d] (%f,%f)", iThread, ent->getIndexPlayer(), ent->getX(), ent->getY(), _entity->getIDDE(), _entity->getX(), _entity->getY());
                        pthread_mutex_unlock(&lock);
                        sem_post(&Remote);
                        sem_post(&OKToBuyMilk);
                        }
                    }
                }
            }
        }
    }

    //jugadores remotos
    if (!res){
        for(int i=0; ((i<remPlayers.size()) && (!res)); i++){
            DynamicEntity *_entity = remPlayers[i];
            if (ent->getActLevel() == _entity->getActLevel()){
                if (ent->getIndexPlayer() != _entity->getIDDE()){
                    if (!_entity->isBlocked()){
                        res = ((ent->getX() == _entity->getX()) && (ent->getY() == _entity->getY()));
                        if (res){
                            if (sem_wait(&OKToBuyMilk)==0){
                                pthread_mutex_lock(&lock);
                                logger->debug("[COLLISION] Thread[%08x] Player [%d] (%f,%f) collides with rem player [%d] (%f,%f)", iThread, ent->getIndexPlayer(), ent->getX(), ent->getY(), _entity->getIDDE(), _entity->getX(), _entity->getY());
                                pthread_mutex_unlock(&lock);
                                sem_post(&Remote);
                                sem_post(&OKToBuyMilk);
                            }
                        }
                    }
                }
            }
        }

    }

    return res;
 };





bool CollisionEntities::isCollDynamicElement(DynamicEntity *ent, pthread_t iThread){
    bool res = false;

    std::vector<DynamicEntity *>enemies = mem->getEnemiesByLevel(ent->getActLevel());
    std::vector<DynamicEntity *>dynelements = mem->getDynElemByLevel(ent->getActLevel());
    std::vector<DynamicEntity *>remPlayers = mem->getRemPlayer();


    res = (mem->getPlayer_1()->getActLevel() == ent->getActLevel()) &&
          (mem->getPlayer_1()->getIndexPlayer() != ent->getIDDE()) &&
          (!mem->getPlayer_1()->isLocked()) &&
          (mem->getPlayer_1()->getX() == ent->getX()) &&
          (mem->getPlayer_1()->getY() == ent->getY());

    if (res){
        if (sem_wait(&OKToBuyMilk)==0){
        pthread_mutex_lock(&lock);
        logger->debug("[COLLISION] Thread [%08x] Entity [%d] (%f,%f) collides Player [%d] (%f,%f)", iThread, ent->getIDDE(), ent->getX(), ent->getY(), mem->getPlayer_1()->getIndexPlayer(), mem->getPlayer_1()->getX(), mem->getPlayer_1()->getY());
        pthread_mutex_unlock(&lock);
        sem_post(&Remote);
        sem_post(&OKToBuyMilk);
        }
    }

    res = res ||
              ((mem->getPlayer_2()->getActLevel() == ent->getActLevel()) &&
              (mem->getPlayer_2()->getIndexPlayer() != ent->getIDDE()) &&
              (!mem->getPlayer_2()->isLocked()) &&
              (mem->getPlayer_2()->getX() == ent->getX()) &&
              (mem->getPlayer_2()->getY() == ent->getY()));

    if (res){
        if (sem_wait(&OKToBuyMilk)==0){
        pthread_mutex_lock(&lock);
        logger->debug("[COLLISION] Thread [%08x] Entity [%d] (%f,%f) collides Player [%d] (%f,%f)", iThread, ent->getIDDE(), ent->getX(), ent->getY(), mem->getPlayer_2()->getIndexPlayer(), mem->getPlayer_2()->getX(), mem->getPlayer_2()->getY());
        pthread_mutex_unlock(&lock);
        sem_post(&Remote);
        sem_post(&OKToBuyMilk);
        }
    }

    res = res ||
              ((mem->getPlayer_3()->getActLevel() == ent->getActLevel()) &&
              (mem->getPlayer_3()->getIndexPlayer() != ent->getIDDE()) &&
              (!mem->getPlayer_3()->isLocked()) &&
              (mem->getPlayer_3()->getX() == ent->getX()) &&
              (mem->getPlayer_3()->getY() == ent->getY()));

    if (res){
        if (sem_wait(&OKToBuyMilk)==0){
            pthread_mutex_lock(&lock);
            logger->debug("[COLLISION] Thread [%08x] Entity [%d] (%f,%f) collides Player [%d] (%f,%f)", iThread, ent->getIDDE(), ent->getX(), ent->getY(), mem->getPlayer_3()->getIndexPlayer(), mem->getPlayer_3()->getX(), mem->getPlayer_3()->getY());
            pthread_mutex_unlock(&lock);
            sem_post(&Remote);
            sem_post(&OKToBuyMilk);
        }
    }



    if (!res){
        //enemigos
        for(int i=0; ((i<enemies.size()) && (!res)); i++){
           DynamicEntity *_entity = enemies[i];
            if (ent->getIDDE() != _entity->getIDDE()){
                if (!_entity->isBlocked()){
                    res = ((ent->getX() == _entity->getX()) && (ent->getY() == _entity->getY()));
                    if (res){
                        if (sem_wait(&OKToBuyMilk)==0){
                            pthread_mutex_lock(&lock);
                            logger->debug("[COLLISION] Thread [%08x]  element [%d] (%f,%f) collides with enemy [%d] (%f,%f)", iThread, ent->getIDDE(), ent->getX(), ent->getY(), _entity->getIDDE(), _entity->getX(), _entity->getY());
                            pthread_mutex_unlock(&lock);
                            sem_post(&Remote);
                            sem_post(&OKToBuyMilk);
                        }
                    }
                }
            }
        }
    }

    //elementos dinamicos

    if (!res){
        for(int i=0; ((i<dynelements.size()) && (!res)); i++){
            DynamicEntity *_entity = dynelements[i];
            if (ent->getIDDE() != _entity->getIDDE()){
                if (!_entity->isBlocked()){
                    res = ((ent->getX() == _entity->getX()) && (ent->getY() == _entity->getY()));
                    if (res){
                        if (sem_wait(&OKToBuyMilk)==0){
                            pthread_mutex_lock(&lock);
                            logger->debug("[COLLISION] Thread [%08x] element [%d] (%f,%f) collides with dynenemy [%d] (%f,%f)", iThread, ent->getIDDE(), ent->getX(), ent->getY(), _entity->getIDDE(), _entity->getX(), _entity->getY());
                            pthread_mutex_unlock(&lock);
                            sem_post(&Remote);
                            sem_post(&OKToBuyMilk);
                        }
                    }
                }
            }
        }
    }

    //jugadores remotos

    if (!res){

        for(int i=0; ((i<remPlayers.size()) && (!res)); i++){
            DynamicEntity *_entity = remPlayers[i];
            if (ent->getActLevel() == _entity->getActLevel()){
                if (ent->getIDDE() != _entity->getIDDE()){
                    if (!_entity->isBlocked()){
                        res = ((ent->getX() == _entity->getX()) && (ent->getY() == _entity->getY()));
                        if (res){
                            if (sem_wait(&OKToBuyMilk)==0){
                                pthread_mutex_lock(&lock);
                                logger->debug("[COLLISION] Thread [%08x] element [%d] (%f,%f) collides with rem player [%d] (%f,%f)", iThread, ent->getIDDE(), ent->getX(), ent->getY(), _entity->getIDDE(), _entity->getX(), _entity->getY());
                                pthread_mutex_unlock(&lock);
                                sem_post(&Remote);
                                sem_post(&OKToBuyMilk);
                            }
                        }
                    }
                }
            }
        }

    }

    return res;
}
