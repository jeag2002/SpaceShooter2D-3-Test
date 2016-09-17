#ifndef ITEMENTITY_H_INCLUDED
#define ITEMENTITY_H_INCLUDED

#include "Stdafx.h"
#include "Entity.h"
#include "CoreString.h"

/*
ID              INT
ID_TILE         INT         //ID_TILE asociado (2D)
ID_MESH         INT         //ID_MESH asociado (3D)
VALUE           INT
SCRIPT_ANIM     CHAR(20)
SCRIPT_AI       CHAR(20)
*/


class ItemEntity : public Entity{

public:

ItemEntity():Entity(ITEM_ENT){
    this->itemType = 0;
    this->value = 0;
};

ItemEntity(uint32_t timestamp):Entity(ITEM_ENT, timestamp){
    this->itemType = 0;
    this->value = 0;
};

ItemEntity(ItemEntity *exitRef, uint32_t timestamp):Entity(ITEM_ENT, timestamp){
    Entity::copyTo((Entity *)exitRef);
    this->itemType = exitRef->getType();
    this->value = exitRef->getValue();
};

void clear(){
    Entity::clear();
    this->itemType = 0;
    this->value = 0;
};

~ItemEntity(){
    Entity::clear();
    this->itemType = 0;
    this->value = 0;
};

uint32_t getItemType(){return this->itemType;}
void setItemType(uint32_t _type){this->itemType = _type;}

uint32_t getValue(){return this->value;}
void setValue(uint32_t _value){this->value = _value;}

private:

uint32_t itemType;
uint32_t value;

};



#endif // ITEMENTITY_H_INCLUDED
