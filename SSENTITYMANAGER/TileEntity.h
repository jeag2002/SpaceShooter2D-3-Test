#ifndef TILEENTITY_H_INCLUDED
#define TILEENTITY_H_INCLUDED


#include "Stdafx.h"
#include "Resource.h"
#include "CoreString.h"

#include "TileComponent.h"

/*
TABLE ENT_TILE             //-->Definicion TILES

ID              INT        //identificador TILE
POS_X           FLOAT
POS_Y           FLOAT      //sit X,Y (inicio de coordenadas)
WIDTH           FLOAT
HEIGHT          FLOAT      //width x height
*/

class TileEntity : public Resource{

public:

TileEntity():Resource(false,0, TILE_ENT){
    this->id = 0;
    this->pos_x = 0;
    this->pos_y = 0;
    this->widht = 0;
    this->height = 0;
    components.clear();
}


TileEntity(uint32_t timestamp):Resource(false, timestamp, TILE_ENT){
    this->id = 0;
    this->pos_x = 0;
    this->pos_y = 0;
    this->widht = 0;
    this->height = 0;
    components.clear();
}

TileEntity(TileEntity *tileRef):Resource(false,0, TILE_ENT){
    this->id = tileRef->getId();
    this->pos_x = tileRef->getPosX();
    this->pos_y = tileRef->getPosY();
    this->widht = tileRef->getWidht();
    this->height = tileRef->getHeight();
    copyComponents(tileRef);
}

TileEntity(TileEntity *tileRef, uint32_t timestamp):Resource(false, timestamp, TILE_ENT){
    this->id = tileRef->getId();
    this->pos_x = tileRef->getPosX();
    this->pos_y = tileRef->getPosY();
    this->widht = tileRef->getWidht();
    this->height = tileRef->getHeight();
    copyComponents(tileRef);
}

~TileEntity(){
    this->id = 0;
    this->pos_x = 0;
    this->pos_y = 0;
    this->widht = 0;
    this->height = 0;
    components.clear();
}

void clear(){
    this->id = 0;
    this->pos_x = 0;
    this->pos_y = 0;
    this->widht = 0;
    this->height = 0;
    components.clear();
}

void copyTo(TileEntity *tileRef){
    this->id = tileRef->getId();
    this->pos_x = tileRef->getPosX();
    this->pos_y = tileRef->getPosY();
    this->widht = tileRef->getWidht();
    this->height = tileRef->getHeight();
    copyComponents(tileRef);
}

uint32_t getId(){return id;}
void setId(uint32_t _id){this->id = _id;}

float getPosX(){return pos_x;}
void setPosX(float _pos_x){this->pos_x = _pos_x;}

float getPosY(){return pos_y;}
void setPosY(float _pos_y){this->pos_y = _pos_y;}

float getWidht(){return widht;}
void setWidht(float _widht){this->widht = _widht;}

float getHeight(){return height;}
void setHeight(float _height){this->height = _height;}

std::vector<TileComponent *>getComponents(){return components;}

TileComponent *getComponent(int index){
    if ((index >= 0) && (index < components.size())){
       return components[index];
    }else{
        //assert("index out of limits");
        return NULL;
    }
}

int getSizeComponents(){return components.size();}

void addComponent(TileComponent *newComponent){
    components.push_back(newComponent);
}

void copyComponents(TileEntity *tileRef){

    int limits = tileRef->getSizeComponents();
    this->components.clear();

    for(int i=0; i<limits; i++){
        TileComponent *component = new TileComponent(tileRef->getComponent(i));
        this->components.push_back(component);
    }
}


private:

uint32_t id;
float pos_x;
float pos_y;
float widht;
float height;

std::vector<TileComponent *>components;

};

#endif // TILEENTITY_H_INCLUDED
