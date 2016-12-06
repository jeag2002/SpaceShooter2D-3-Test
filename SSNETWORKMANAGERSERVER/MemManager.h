#ifndef MEMMANAGER_H_INCLUDED
#define MEMMANAGER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "DynamicEntity.h"

class MemManager{

public:

MemManager(){

    setEnemyMap_lvl1M = SDL_CreateMutex();
    setEnemyMap_lvl2M = SDL_CreateMutex();
    setEnemyMap_lvl3M = SDL_CreateMutex();

    setDynElemMap_lvl1M = SDL_CreateMutex();
    setDynElemMap_lvl2M = SDL_CreateMutex();
    setDynElemMap_lvl3M = SDL_CreateMutex();

    setRemPlayerM = SDL_CreateMutex();
};

~MemManager(){
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
};


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


/********************************************************/

//ENEMIESMAP_1
///////////////////////////////////////////////////////
void addEnemiesMap_lvl_1(int key, DynamicEntity *data){
    std::pair<int, DynamicEntity *> node(key, data);
    EnemiesMap_lvl_1.insert(node);
};

DynamicEntity *getEnemiesMapElem_lvl_1(int key){
    SDL_LockMutex(setEnemyMap_lvl1M);
    DynamicEntityType::iterator it;
    it = EnemiesMap_lvl_1.find(key);
    if (it!=EnemiesMap_lvl_1.end()){
        return it->second;
    }else{
        return NULL;
    }
    SDL_UnlockMutex(setEnemyMap_lvl1M);
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
    SDL_LockMutex(setEnemyMap_lvl2M);
    DynamicEntityType::iterator it;
    it = EnemiesMap_lvl_2.find(key);
    if (it!=EnemiesMap_lvl_2.end()){
        return it->second;
    }else{
        return NULL;
    }
    SDL_UnlockMutex(setEnemyMap_lvl2M);
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
    SDL_LockMutex(setEnemyMap_lvl3M);
    DynamicEntityType::iterator it;
    it = EnemiesMap_lvl_3.find(key);
    if (it!=EnemiesMap_lvl_3.end()){
        return it->second;
    }else{
        return NULL;
    }
    SDL_UnlockMutex(setEnemyMap_lvl3M);
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


//DYNELEMMAP_1
///////////////////////////////////////////////////////
void addDynElemMap_lvl_1(int key, DynamicEntity *data){
    std::pair<int, DynamicEntity *> node(key, data);
    DynElemMap_lvl_1.insert(node);
};

DynamicEntity *getDynElemMapElem_lvl_1(int key){
    SDL_LockMutex(setDynElemMap_lvl1M);
    DynamicEntityType::iterator it;
    it = DynElemMap_lvl_1.find(key);
    if (it!=DynElemMap_lvl_1.end()){
        return it->second;
    }else{
        return NULL;
    }
    SDL_UnlockMutex(setDynElemMap_lvl1M);
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
    SDL_LockMutex(setDynElemMap_lvl2M);
    DynamicEntityType::iterator it;
    it = DynElemMap_lvl_2.find(key);
    if (it!=DynElemMap_lvl_2.end()){
        return it->second;
    }else{
        return NULL;
    }
    SDL_UnlockMutex(setDynElemMap_lvl2M);
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
    SDL_LockMutex(setDynElemMap_lvl3M);
    DynamicEntityType::iterator it;
    it = DynElemMap_lvl_3.find(key);
    if (it!=DynElemMap_lvl_3.end()){
        return it->second;
    }else{
        return NULL;
    }
    SDL_UnlockMutex(setDynElemMap_lvl3M);
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


//REMPLAYER
///////////////////////////////////////////////////////
void addRemPlayerMap(int key, DynamicEntity *data){
    std::pair<int, DynamicEntity *> node(key, data);
    remPlayerMap.insert(node);
};

DynamicEntity *getRemPlayerMapElem(int key){
    SDL_LockMutex(setRemPlayerM);
    DynamicEntityType::iterator it;
    it = remPlayerMap.find(key);
    if (it!=remPlayerMap.end()){
        return it->second;
    }else{
        return NULL;
    }
    SDL_UnlockMutex(setRemPlayerM);
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


//enemigos x planta
std::vector<DynamicEntity *>Enemies_lvl_1;
std::vector<DynamicEntity *>Enemies_lvl_2;
std::vector<DynamicEntity *>Enemies_lvl_3;
//elementos dinamicos x planta
std::vector<DynamicEntity *>DynElem_lvl_1;
std::vector<DynamicEntity *>DynElem_lvl_2;
std::vector<DynamicEntity *>DynElem_lvl_3;

std::vector<DynamicEntity *>remPlayer;

SDL_mutex *setEnemyMap_lvl1M;
SDL_mutex *setEnemyMap_lvl2M;
SDL_mutex *setEnemyMap_lvl3M;

SDL_mutex *setDynElemMap_lvl1M;
SDL_mutex *setDynElemMap_lvl2M;
SDL_mutex *setDynElemMap_lvl3M;

SDL_mutex *setRemPlayerM;

/********************************************************/

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
