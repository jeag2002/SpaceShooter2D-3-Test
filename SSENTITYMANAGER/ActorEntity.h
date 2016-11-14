#ifndef ACTORENTITY_H_INCLUDED
#define ACTORENTITY_H_INCLUDED

#include "Stdafx.h"
#include "Entity.h"
#include "CoreString.h"
#include "AnimationNode.h"


/*

TABLE ENT_ACTOR           //-->definicion actor

ID              INT       //identificador del ACTOR
ID_ANIMATION    INT       //identificador ANIMATION

INC             FLOAT
SHIELD          FLOAT
LIVE            FLOAT
SCORE           INT

SCRIPT_IA       CHAR(20)  //Comportamiento IA (Jugador, define el gameplay separado de su animacion)
LIMIT           CHAR(100) //nodos mapa colision. (mapa luz?)
SHADE           CHAR(100) //nodos mapa sombreado.

TABLE ENT_ACTOR_COMPONENT_ITEM //-->definicion componentes de un actor.

ID              INT            //identificador del componente
ID_ACTOR        INT            //identificador del actor.
ID_ITEM         INT            //identficador del item

TABLE ENT_ACTOR_COMPONENT_WEAPON //-->definicion componente armas

ID              INT           //identificador del componente
ID_ACTOR        INT           //identificador del actor.
ID_WEAPON       INT           //identificador del arma.

*/

class ActorEntity: public Entity{

public:

ActorEntity():Entity(ACTOR_ENT){
    this->shield = 0;
    this->live = 0;
    this->score = 0;
    this->tree = new AnimationNode();
    clearBuffers();
};

ActorEntity(uint32_t timestamp):Entity(ACTOR_ENT, timestamp){
    this->shield = 0;
    this->live = 0;
    this->score = 0;
    this->tree = new AnimationNode();
    clearBuffers();
};

ActorEntity(ActorEntity *actorRef, uint32_t timestamp):Entity(ACTOR_ENT, timestamp){
    Entity::copyTo((Entity *)actorRef);
    this->shield = actorRef->getShield();
    this->live = actorRef->getLive();
    this->score = actorRef->getScore();
    this->tree = new AnimationNode(actorRef->getAnimationTree());
    copyBuffers(actorRef);
    copyActorComponents(actorRef);
};


void clear(){
    this->shield = 0;
    this->live = 0;
    this->score = 0;
    clearBuffers();
    delete tree;
};


~ActorEntity(){
    this->shield = 0;
    this->live = 0;
    this->score = 0;
    clearBuffers();
    delete tree;
};



void copyTo(ActorEntity *actorRef){
    Entity::copyTo((Entity *)actorRef);
    this->shield = actorRef->getShield();
    this->live = actorRef->getLive();
    this->score = actorRef->getScore();
    //this->tree = new AnimationNode(actorRef->getAnimationTree());
    //copyBuffers(actorRef);
    //copyActorComponents(actorRef);
};


uint32_t getShield(){return this->shield;}
void setShield(uint32_t _shield){this->shield = _shield;}

uint32_t getLive(){return this->live;}
void setLive(uint32_t _live){this->live = _live;}

uint32_t getScore(){return this->score;}
void setScore(uint32_t _score){this->score = _score;}

coordsXY *getLimits(){return limits;}
uint8_t getLimitsSize(){return lim;}

coordsXY *getShade(){return shade;}
uint8_t getShadeSize(){return shad;}


void addLimitXY(coordsXY data){
    if (this->lim < SIZE_COORD){
        limits[lim] = data;
        lim++;
    }
}

void addShadeXY(coordsXY data){
    if (this->shad < SIZE_COORD){
        shade[shad] = data;
        shad++;
    }
}

coordsXY getLimitByIndex(int index){

    coordsXY coordDummy;
    coordDummy.rel_pos_x = 0;
    coordDummy.rel_pos_y = 0;

    if ((index >=0) && (index < SIZE_COORD)){
        return limits[index];
    }else{
        return coordDummy;
    }
}

coordsXY getShadeByIndex(int index){

    coordsXY coordDummy;
    coordDummy.rel_pos_x = 0;
    coordDummy.rel_pos_y = 0;

    if ((index >=0) && (index < SIZE_COORD)){
        return shade[index];
    }else{
        return coordDummy;
    }
}

void copyBuffers(ActorEntity *actorRef){

    uint8_t refLim = actorRef->getLimitsSize();
    uint8_t refShad = actorRef->getShadeSize();

    clearBuffers();

    for(int i=0; i<refLim; i++){
       coordsXY cXY = actorRef->getLimitByIndex(i);
       limits[i].rel_pos_x = cXY.rel_pos_x;
       limits[i].rel_pos_y = cXY.rel_pos_y;
    }

    this->lim = refLim;

    for(int j=0; j<refShad; j++){
       coordsXY cXY = actorRef->getShadeByIndex(j);
       shade[j].rel_pos_x = cXY.rel_pos_x;
       shade[j].rel_pos_y = cXY.rel_pos_y;
    }

    this->shad = refShad;
}

AnimationNode *getAnimationTree(){return tree;}
void setAnimationTree(AnimationNode *treeRef){this->tree = treeRef;}


void addItems(Entity *item){
    items.push_back(item);
}

Entity *getItem(int index){
    if ((index >=0) && (index < items.size())){
        return items[index];
    }else{
        return NULL;
    }
}

int getItemsSize(){return items.size();}

void addWeapons(Entity *weapon){
    weapons.push_back(weapon);
}

Entity *getWeapon(int index){
    if ((index >=0) && (index < weapons.size())){
        return weapons[index];
    }else{
        return NULL;
    }
}

int getWeaponsSize(){return weapons.size();}

void copyActorComponents(ActorEntity *actorRef){

    items.clear();
    weapons.clear();

    for(int i=0; i<actorRef->getItemsSize(); i++){
        Entity *data = actorRef->getItem(i);
        Entity *cpyData = new Entity(data,ITEM_ENT);
        items.push_back(cpyData);

    }

   for(int j=0; j<actorRef->getWeaponsSize(); j++){
       Entity *data = actorRef->getWeapon(j);
       Entity *cpyData = new Entity(data,WEAPON_ENT);
       weapons.push_back(cpyData);
    }

}

void marshallActorEntity(char **data);


private:

uint32_t id;
uint32_t shield;
uint32_t live;
uint32_t score;

coordsXY limits[SIZE_COORD];
uint8_t lim;

coordsXY shade[SIZE_COORD];
uint8_t shad;

AnimationNode *tree;

void clearBuffers(){

    lim = 0;
    shad = 0;

    for(int i=0; i<SIZE_COORD; i++){
        limits[i].rel_pos_x = 0;
        limits[i].rel_pos_y = 0;

        shade[i].rel_pos_x = 0;
        shade[i].rel_pos_y = 0;
    }

    items.clear();
    weapons.clear();

    act_item = 0;
    weapon_item = 0;

}

std::vector<Entity *> items;    //--> compoennte del actor
int act_item;
std::vector<Entity *> weapons;   //--> armas del actor.
int weapon_item;

};


#endif // ACTORENTITY_H_INCLUDED
