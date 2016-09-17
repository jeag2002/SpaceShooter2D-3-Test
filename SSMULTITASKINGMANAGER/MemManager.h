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

private:

int player;
int roof;

DynamicPlayer *player_1;
DynamicPlayer *player_2;
DynamicPlayer *player_3;


DynamicEntity *remPlayer_1;
DynamicEntity *remPlayer_2;
DynamicEntity *remPlayer_3;


//enemigos x planta
std::vector<DynamicEntity *>Enemies_lvl_1;
std::vector<DynamicEntity *>Enemies_lvl_2;
std::vector<DynamicEntity *>Enemies_lvl_3;

//elementos dinamicos x planta
std::vector<DynamicEntity *>DynElem_lvl_1;
std::vector<DynamicEntity *>DynElem_lvl_2;
std::vector<DynamicEntity *>DynElem_lvl_3;


std::vector<DynamicEntity *>remPlayer;

};


#endif // MEMMANAGER_H_INCLUDED
