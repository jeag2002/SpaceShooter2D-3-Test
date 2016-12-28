#include "CollisionEntities.h"


bool CollisionEntities::isCollDynamicElement(DynamicEntity *ent){
    bool res = false;

    std::map<int, DynamicEntity *>enemies = mem->getEnemyMapByLevel(ent->getActLevel());
    std::map<int, DynamicEntity *>dynelements = mem->getDynElemMapByLevel(ent->getActLevel());
    std::map<int, DynamicEntity *>remPlayers = mem->getRemPlayerMap();


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
