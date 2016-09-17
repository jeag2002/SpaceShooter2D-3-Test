#include "CollisionEntities.h"


 bool CollisionEntities::isCollDynamicPlayer(DynamicPlayer *ent){

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
    }

    res = res ||
              ((mem->getPlayer_2()->getActLevel() == ent->getActLevel()) &&
              (mem->getPlayer_2()->getIndexPlayer() != ent->getIndexPlayer()) &&
              (!mem->getPlayer_2()->isLocked()) &&
              (mem->getPlayer_2()->getX() == ent->getX()) &&
              (mem->getPlayer_2()->getY() == ent->getY()));

    if (res){
    }

    res = res ||
              ((mem->getPlayer_3()->getActLevel() == ent->getActLevel()) &&
              (mem->getPlayer_3()->getIndexPlayer() != ent->getIndexPlayer()) &&
              (!mem->getPlayer_3()->isLocked()) &&
              (mem->getPlayer_3()->getX() == ent->getX()) &&
              (mem->getPlayer_3()->getY() == ent->getY()));

    if (res){
    }

    //enemigos
    if (!res){
        for(int i=0; ((i<enemies.size()) && (!res)); i++){
           DynamicEntity *_entity = enemies[i];
            if (ent->getIndexPlayer() != _entity->getIDDE()){
                if (!_entity->isBlocked()){
                    res = ((ent->getX() == _entity->getX()) && (ent->getY() == _entity->getY()));
                    if (res){
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
                        }
                    }
                }
            }
        }

    }

    return res;
 };





bool CollisionEntities::isCollDynamicElement(DynamicEntity *ent){
    bool res = false;

    std::map<int, DynamicEntity *>enemies = mem->getEnemyMapByLevel(ent->getActLevel());
    std::map<int, DynamicEntity *>dynelements = mem->getDynElemMapByLevel(ent->getActLevel());
    std::map<int, DynamicEntity *>remPlayers = mem->getRemPlayerMap();


    res = (mem->getPlayer_1()->getActLevel() == ent->getActLevel()) &&
          (mem->getPlayer_1()->getIndexPlayer() != ent->getIDDE()) &&
          (!mem->getPlayer_1()->isLocked()) &&
          (mem->getPlayer_1()->getX() == ent->getX()) &&
          (mem->getPlayer_1()->getY() == ent->getY());

    if (res){
    }

    res = res ||
              ((mem->getPlayer_2()->getActLevel() == ent->getActLevel()) &&
              (mem->getPlayer_2()->getIndexPlayer() != ent->getIDDE()) &&
              (!mem->getPlayer_2()->isLocked()) &&
              (mem->getPlayer_2()->getX() == ent->getX()) &&
              (mem->getPlayer_2()->getY() == ent->getY()));

    if (res){
    }

    res = res ||
              ((mem->getPlayer_3()->getActLevel() == ent->getActLevel()) &&
              (mem->getPlayer_3()->getIndexPlayer() != ent->getIDDE()) &&
              (!mem->getPlayer_3()->isLocked()) &&
              (mem->getPlayer_3()->getX() == ent->getX()) &&
              (mem->getPlayer_3()->getY() == ent->getY()));

    if (res){
    }



    if (!res){
        //enemigos
        for(auto iterator = enemies.begin(); iterator != enemies.end(); iterator++){
            int i = iterator->first;
            DynamicEntity *_entity = enemies[i];
            if (ent->getIDDE() != _entity->getIDDE()){
                if (!_entity->isBlocked()){
                    res = ((ent->getX() == _entity->getX()) && (ent->getY() == _entity->getY()));
                    if (res){
                    }
                }
            }
        }
    }

    //elementos dinamicos

    if (!res){
        for(auto iterator = dynelements.begin(); iterator != dynelements.end(); iterator++){
            int i = iterator->first;
            DynamicEntity *_entity = dynelements[i];
            if (ent->getIDDE() != _entity->getIDDE()){
                if (!_entity->isBlocked()){
                    res = ((ent->getX() == _entity->getX()) && (ent->getY() == _entity->getY()));
                    if (res){
                    }
                }
            }
        }
    }

    //jugadores remotos

    if (!res){
        for(auto iterator = remPlayers.begin(); iterator != remPlayers.end(); iterator++){
            int i = iterator->first;
            DynamicEntity *_entity = remPlayers[i];
            if (ent->getActLevel() == _entity->getActLevel()){
                if (ent->getIDDE() != _entity->getIDDE()){
                    if (!_entity->isBlocked()){
                        res = ((ent->getX() == _entity->getX()) && (ent->getY() == _entity->getY()));
                        if (res){
                        }
                    }
                }
            }
        }

    }

    return res;
}
