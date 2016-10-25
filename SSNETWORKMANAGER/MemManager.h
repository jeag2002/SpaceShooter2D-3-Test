#ifndef MEMMANAGER_H_INCLUDED
#define MEMMANAGER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "DynamicEntity.h"
#include "DynamicPlayer.h"

class MemManager{

public:

MemManager(){
    player = 1;
    roof = 1;
    player_1 = new DynamicPlayer();
    player_2 = new DynamicPlayer();
    player_3 = new DynamicPlayer();

    setEnemyMap_lvl1M = SDL_CreateMutex();
    setEnemyMap_lvl2M = SDL_CreateMutex();
    setEnemyMap_lvl3M = SDL_CreateMutex();

    setDynElemMap_lvl1M = SDL_CreateMutex();
    setDynElemMap_lvl2M = SDL_CreateMutex();
    setDynElemMap_lvl3M = SDL_CreateMutex();

    setRemPlayerM = SDL_CreateMutex();


};

~MemManager(){
    player = 0;
    roof = 0;

    Enemies_lvl_1.clear();
    Enemies_lvl_2.clear();
    Enemies_lvl_3.clear();

    DynElem_lvl_1.clear();
    DynElem_lvl_2.clear();
    DynElem_lvl_3.clear();

    remPlayer.clear();

    EnemiesMap_lvl_1.clear();
    EnemiesMap_lvl_2.clear();
    EnemiesMap_lvl_3.clear();

    DynElemMap_lvl_1.clear();
    DynElemMap_lvl_2.clear();
    DynElemMap_lvl_3.clear();

    remPlayerMap.clear();

    delete player_1;
    delete player_2;
    delete player_3;

};

int getPlayerIndex(){return this->player;}
void setPlayerIndex(int _player){this->player = _player;}

int getRoofIndex(){return this->roof;}
void setRoofIndex(int _roof){this->roof = _roof;}

void setPlayer_1(DynamicPlayer *entity){player_1->setDynamicPlayer(entity);}
void setPlayer_2(DynamicPlayer *entity){player_2->setDynamicPlayer(entity);}
void setPlayer_3(DynamicPlayer *entity){player_3->setDynamicPlayer(entity);}

DynamicPlayer *getPlayer_1(){return player_1;}
DynamicPlayer *getPlayer_2(){return player_2;}
DynamicPlayer *getPlayer_3(){return player_3;}

void setRemPlayer(DynamicEntity *entity){remPlayer.push_back(entity);}
std::vector<DynamicEntity *>getRemPlayer(){return remPlayer;}

void setEnemies_lvl_1(DynamicEntity *entity){Enemies_lvl_1.push_back(entity);}
void setEnemies_lvl_2(DynamicEntity *entity){Enemies_lvl_2.push_back(entity);}
void setEnemies_lvl_3(DynamicEntity *entity){Enemies_lvl_3.push_back(entity);}

std::vector<DynamicEntity *>getEnemies_lvl_1(){return Enemies_lvl_1;}
std::vector<DynamicEntity *>getEnemies_lvl_2(){return Enemies_lvl_2;}
std::vector<DynamicEntity *>getEnemies_lvl_3(){return Enemies_lvl_3;}

void setDynElem_lvl_1(DynamicEntity *entity){DynElem_lvl_1.push_back(entity);}
void setDynElem_lvl_2(DynamicEntity *entity){DynElem_lvl_2.push_back(entity);}
void setDynElem_lvl_3(DynamicEntity *entity){DynElem_lvl_3.push_back(entity);}

std::vector<DynamicEntity *>getDynElem_lvl_1(){return DynElem_lvl_1;}
std::vector<DynamicEntity *>getDynElem_lvl_2(){return DynElem_lvl_2;}
std::vector<DynamicEntity *>getDynElem_lvl_3(){return DynElem_lvl_3;}


std::vector<DynamicEntity *>getEnemiesByLevel(int level){

    if (level == 1){
        return getEnemies_lvl_1();
    }else if (level == 2){
        return getEnemies_lvl_2();
    }else{
        return getEnemies_lvl_3();
    }
}

std::vector<DynamicEntity *>getDynElemByLevel(int level){
    if (level == 1){
        return getDynElem_lvl_1();
    }else if (level == 2){
        return getDynElem_lvl_2();
    }else{
        return getDynElem_lvl_3();
    }
}

DynamicPlayer *getActPlayer(int playerID){
    if (playerID == 1){
        return player_1;
    }else if (playerID == 2){
        return player_2;
    }else{
        return player_3;
    }
}

void setActPlayer(int playerID, DynamicPlayer *player){
    if (playerID == 1){
        player_1->setDynamicPlayer(player);
    }else if (playerID == 2){
        player_2->setDynamicPlayer(player);
    }else{
        player_3->setDynamicPlayer(player);
    }
}

/********************************************************/

//ENEMIESMAP_1
///////////////////////////////////////////////////////
void addEnemiesMap_lvl_1(int key, DynamicEntity *data){
    std::pair<int, DynamicEntity *> node(key, data);
    EnemiesMap_lvl_1.insert(node);
};

DynamicEntity *getEnemiesMapElem_lvl_1(int key){
    DynamicEntityType::iterator it;
    it = EnemiesMap_lvl_1.find(key);
    if (it!=EnemiesMap_lvl_1.end()){
        return it->second;
    }else{
        return NULL;
    }
};

void setEnemiesMap_Lvl_1(int key, DynamicEntity *data){

    SDL_LockMutex(setEnemyMap_lvl1M);

    DynamicEntityType::iterator it;
    it = EnemiesMap_lvl_1.find(key);
    if (it!=EnemiesMap_lvl_1.end()){
        ((DynamicEntity *)EnemiesMap_lvl_1[key])->setDynamicEntity(data);
    }

    SDL_UnlockMutex(setEnemyMap_lvl1M);
}

std::map<int, DynamicEntity *>getEnemy_Lvl_1_Map(){return EnemiesMap_lvl_1;}
///////////////////////////////////////////////////////

//ENEMIESMAP_2
///////////////////////////////////////////////////////
void addEnemiesMap_lvl_2(int key, DynamicEntity *data){
    std::pair<int, DynamicEntity *> node(key, data);
    EnemiesMap_lvl_2.insert(node);
};

DynamicEntity *getEnemiesMapElem_lvl_2(int key){
    DynamicEntityType::iterator it;
    it = EnemiesMap_lvl_2.find(key);
    if (it!=EnemiesMap_lvl_2.end()){
        return it->second;
    }else{
        return NULL;
    }
};

void setEnemiesMap_Lvl_2(int key, DynamicEntity *data){

    SDL_LockMutex(setEnemyMap_lvl2M);

    DynamicEntityType::iterator it;
    it = EnemiesMap_lvl_2.find(key);
    if (it!=EnemiesMap_lvl_2.end()){
        ((DynamicEntity *)EnemiesMap_lvl_2[key])->setDynamicEntity(data);
    }

    SDL_UnlockMutex(setEnemyMap_lvl2M);
}

std::map<int, DynamicEntity *>getEnemy_Lvl_2_Map(){return EnemiesMap_lvl_2;}
///////////////////////////////////////////////////////

//ENEMIESMAP_3
///////////////////////////////////////////////////////
void addEnemiesMap_lvl_3(int key, DynamicEntity *data){
    std::pair<int, DynamicEntity *> node(key, data);
    EnemiesMap_lvl_3.insert(node);
};

DynamicEntity *getEnemiesMapElem_lvl_3(int key){
    DynamicEntityType::iterator it;
    it = EnemiesMap_lvl_3.find(key);
    if (it!=EnemiesMap_lvl_3.end()){
        return it->second;
    }else{
        return NULL;
    }
};

void setEnemiesMap_Lvl_3(int key, DynamicEntity *data){
    SDL_LockMutex(setEnemyMap_lvl3M);

    DynamicEntityType::iterator it;
    it = EnemiesMap_lvl_3.find(key);
    if (it!=EnemiesMap_lvl_3.end()){
        ((DynamicEntity *)EnemiesMap_lvl_3[key])->setDynamicEntity(data);
    }

    SDL_UnlockMutex(setEnemyMap_lvl3M);
}

std::map<int, DynamicEntity *>getEnemy_Lvl_3_Map(){return EnemiesMap_lvl_3;}
///////////////////////////////////////////////////////


std::map<int, DynamicEntity *>getEnemyMapByLevel(int level){
    if (level == 1){
        return getEnemy_Lvl_1_Map();
    }else if (level == 2){
        return getEnemy_Lvl_2_Map();
    }else{
        return getEnemy_Lvl_3_Map();
    }
}

DynamicEntity *getEnemyMapByLevelAndId(int level, int key){
    if (level == 1){
        return getEnemiesMapElem_lvl_1(key);
    }else if (level == 2){
        return getEnemiesMapElem_lvl_2(key);
    }else{
        return getEnemiesMapElem_lvl_3(key);
    }
}

void addEnemyMapByLevelAndId(int level, int key, DynamicEntity *data){
    if (level == 1){
        addEnemiesMap_lvl_1(key,data);
    }else if (level == 2){
        addEnemiesMap_lvl_2(key,data);
    }else{
        addEnemiesMap_lvl_3(key,data);
    }
}


//DYNELEMMAP_1
///////////////////////////////////////////////////////
void addDynElemMap_lvl_1(int key, DynamicEntity *data){
    std::pair<int, DynamicEntity *> node(key, data);
    DynElemMap_lvl_1.insert(node);
};

DynamicEntity *getDynElemMapElem_lvl_1(int key){
    DynamicEntityType::iterator it;
    it = DynElemMap_lvl_1.find(key);
    if (it!=DynElemMap_lvl_1.end()){
        return it->second;
    }else{
        return NULL;
    }
};

void setDynElemMap_lvl_1(int key, DynamicEntity *data){
    SDL_LockMutex(setDynElemMap_lvl1M);
    DynamicEntityType::iterator it;
    it = DynElemMap_lvl_1.find(key);
    if (it!=DynElemMap_lvl_1.end()){
        ((DynamicEntity *)DynElemMap_lvl_1[key])->setDynamicEntity(data);
    }
    SDL_UnlockMutex(setDynElemMap_lvl1M);
}

std::map<int, DynamicEntity *>getDynElem_Lvl_1_Map(){return DynElemMap_lvl_1;}
///////////////////////////////////////////////////////


//DYNELEMMAP_2
///////////////////////////////////////////////////////
void addDynElemMap_lvl_2(int key, DynamicEntity *data){
    std::pair<int, DynamicEntity *> node(key, data);
    DynElemMap_lvl_2.insert(node);
};

DynamicEntity *getDynElemMapElem_lvl_2(int key){
    DynamicEntityType::iterator it;
    it = DynElemMap_lvl_2.find(key);
    if (it!=DynElemMap_lvl_2.end()){
        return it->second;
    }else{
        return NULL;
    }
};

void setDynElemMap_lvl_2(int key, DynamicEntity *data){
    SDL_LockMutex(setDynElemMap_lvl2M);
    DynamicEntityType::iterator it;
    it = DynElemMap_lvl_2.find(key);
    if (it!=DynElemMap_lvl_2.end()){
        ((DynamicEntity *)DynElemMap_lvl_2[key])->setDynamicEntity(data);
    }
    SDL_UnlockMutex(setDynElemMap_lvl2M);
}

std::map<int, DynamicEntity *>getDynElem_Lvl_2_Map(){return DynElemMap_lvl_2;}
///////////////////////////////////////////////////////

//DYNELEMMAP_3
///////////////////////////////////////////////////////
void addDynElemMap_lvl_3(int key, DynamicEntity *data){
    std::pair<int, DynamicEntity *> node(key, data);
    DynElemMap_lvl_3.insert(node);
};

DynamicEntity *getDynElemMapElem_lvl_3(int key){
    DynamicEntityType::iterator it;
    it = DynElemMap_lvl_3.find(key);
    if (it!=DynElemMap_lvl_3.end()){
        return it->second;
    }else{
        return NULL;
    }
};

void setDynElemMap_lvl_3(int key, DynamicEntity *data){
    SDL_LockMutex(setDynElemMap_lvl3M);
    DynamicEntityType::iterator it;
    it = DynElemMap_lvl_3.find(key);
    if (it!=DynElemMap_lvl_3.end()){
        ((DynamicEntity *)DynElemMap_lvl_3[key])->setDynamicEntity(data);
    }
    SDL_UnlockMutex(setDynElemMap_lvl3M);
};

std::map<int, DynamicEntity *>getDynElem_Lvl_3_Map(){return DynElemMap_lvl_3;}
///////////////////////////////////////////////////////

std::map<int, DynamicEntity *>getDynElemMapByLevel(int level){
    if (level == 1){
        return getDynElem_Lvl_1_Map();
    }else if (level == 2){
        return getDynElem_Lvl_2_Map();
    }else{
        return getDynElem_Lvl_3_Map();
    }
}

DynamicEntity *getDynElemMapByLevelAndId(int level, int key){
    if (level == 1){
        return getDynElemMapElem_lvl_1(key);
    }else if (level == 2){
        return getDynElemMapElem_lvl_2(key);
    }else{
        return getDynElemMapElem_lvl_3(key);
    }
}

void addDynElementMapByLevelAndId(int level, int key, DynamicEntity *data){
    if (level == 1){
        addDynElemMap_lvl_1(key,data);
    }else if (level == 2){
       addDynElemMap_lvl_2(key,data);
    }else{
        addDynElemMap_lvl_3(key,data);
    }
}


//REMPLAYER
///////////////////////////////////////////////////////
void addRemPlayerMap(int key, DynamicEntity *data){
    std::pair<int, DynamicEntity *> node(key, data);
    remPlayerMap.insert(node);
};

DynamicEntity *getRemPlayerMapElem(int key){
    DynamicEntityType::iterator it;
    it = remPlayerMap.find(key);
    if (it!=remPlayerMap.end()){
        return it->second;
    }else{
        return NULL;
    }
};

void setRemPlayerMap(int key, DynamicEntity *data){

    SDL_LockMutex(setRemPlayerM);
    DynamicEntityType::iterator it;
    it = remPlayerMap.find(key);
    if (it!=remPlayerMap.end()){
        ((DynamicEntity *)remPlayerMap[key])->setDynamicEntity(data);
    }
    SDL_UnlockMutex(setRemPlayerM);


}

std::map<int, DynamicEntity *>getRemPlayerMap(){return remPlayerMap;}
///////////////////////////////////////////////////////


/********************************************************/


private:

int player;
int roof;

DynamicPlayer *player_1;
DynamicPlayer *player_2;
DynamicPlayer *player_3;

//enemigos x planta
std::vector<DynamicEntity *>Enemies_lvl_1;
std::vector<DynamicEntity *>Enemies_lvl_2;
std::vector<DynamicEntity *>Enemies_lvl_3;
//elementos dinamicos x planta
std::vector<DynamicEntity *>DynElem_lvl_1;
std::vector<DynamicEntity *>DynElem_lvl_2;
std::vector<DynamicEntity *>DynElem_lvl_3;

std::vector<DynamicEntity *>remPlayer;

/********************************************************/


SDL_mutex *setEnemyMap_lvl1M;
SDL_mutex *setEnemyMap_lvl2M;
SDL_mutex *setEnemyMap_lvl3M;

SDL_mutex *setDynElemMap_lvl1M;
SDL_mutex *setDynElemMap_lvl2M;
SDL_mutex *setDynElemMap_lvl3M;

SDL_mutex *setRemPlayerM;


typedef std::map<int, DynamicEntity *> DynamicEntityType;

DynamicEntityType EnemiesMap_lvl_1;
DynamicEntityType EnemiesMap_lvl_2;
DynamicEntityType EnemiesMap_lvl_3;

DynamicEntityType DynElemMap_lvl_1;
DynamicEntityType DynElemMap_lvl_2;
DynamicEntityType DynElemMap_lvl_3;

DynamicEntityType remPlayerMap;

/********************************************************/

};


#endif // MEMMANAGER_H_INCLUDED
