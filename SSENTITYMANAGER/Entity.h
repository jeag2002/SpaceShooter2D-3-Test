#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "Stdafx.h"
#include "Resource.h"

/*

ID              INT
ID_TILE         INT         //ID_TILE asociado (2D)
ID_MESH         INT         //ID_MESH asociado (3D)
SCRIPT_ANIM     CHAR(20)
SCRIPT_AI       CHAR(20)
*/


class Entity : public Resource{

public:

Entity(uint8_t entityRef):Resource(false,0,entityRef){
    this->id = 0;
    this->xPos = 0;
    this->yPos = 0;
    this->idTile = 0;
    this->idMesh = 0;
    this->scriptAnim = "";
    this->scriptAI = "";
    clearBuffers();
}

Entity(uint8_t entityRef, uint32_t timestamp):Resource(false,timestamp,entityRef){
    this->id = 0;
    this->xPos = 0;
    this->yPos = 0;
    this->idTile = 0;
    this->idMesh = 0;
    this->scriptAnim = "";
    this->scriptAI = "";
    clearBuffers();
}

~Entity(){
    this->id = 0;
    this->xPos = 0;
    this->yPos = 0;
    this->idTile = 0;
    this->idMesh = 0;
    this->scriptAnim = "";
    this->scriptAI = "";
    clearBuffers();
}

Entity(Entity *entityRef, uint8_t entityRefID):Resource(false,0,entityRefID){
    this->id = entityRef->getID();
    this->xPos = entityRef->getXPos();
    this->yPos = entityRef->getYPos();
    this->idTile =  entityRef->getIDTile();
    this->idMesh =  entityRef->getIDMesh();
    this->scriptAnim = CoreString::copySafetyString(entityRef->getScriptAnim());
    this->scriptAI =  CoreString::copySafetyString(entityRef->getScriptAI());
    copyBuffer(entityRef);
}

Entity(Entity *entityRef, uint8_t entityRefID, uint32_t timestamp):Resource(false,timestamp,entityRefID){
    this->id = entityRef->getID();
    this->xPos = entityRef->getXPos();
    this->yPos = entityRef->getYPos();
    this->idTile =  entityRef->getIDTile();
    this->idMesh =  entityRef->getIDMesh();
    this->scriptAnim = CoreString::copySafetyString(entityRef->getScriptAnim());
    this->scriptAI =  CoreString::copySafetyString(entityRef->getScriptAI());
    copyBuffer(entityRef);
}


void copyTo(Entity *entityRef){
    this->id = entityRef->getID();
    this->xPos = entityRef->getXPos();
    this->yPos = entityRef->getYPos();
    this->idTile =  entityRef->getIDTile();
    this->idMesh =  entityRef->getIDMesh();
    this->scriptAnim = CoreString::copySafetyString(entityRef->getScriptAnim());
    this->scriptAI =  CoreString::copySafetyString(entityRef->getScriptAI());
    copyBuffer(entityRef);
}

uint32_t getID(){return this->id;}
void setID(uint32_t _id){this->id = _id;}

float getXPos(){return this->xPos;}
void setXPos(float _xPos){this->xPos = _xPos;}

float getYPos(){return this->yPos;}
void setYPos(float _yPos){this->yPos = _yPos;}

uint32_t getIDTile(){return this->idTile;}
void setIDTile(uint32_t _idTile){this->idTile = _idTile;}

uint32_t getIDMesh(){return this->idMesh;}
void setIDMesh(uint32_t _idMesh){this->idMesh = _idMesh;}

std::string getScriptAnim(){return this->scriptAnim;}
void setScriptAnim(std::string _scriptAnim){this->scriptAnim = CoreString::copySafetyString(_scriptAnim);}

std::string getScriptAI(){return this->scriptAI;}
void setScriptAI(std::string _scriptAI){this->scriptAI = CoreString::copySafetyString(_scriptAI);}

//FUNCIONES ENCARGADAS DE ENVIAR-RECIBIR LOS DATOS DE LOS SCRIPTS DE ANIMACION/AI/GAMEPLAY
virtual std::string serializeToLua(); //C++ --> LUA (JSON)
virtual void deserializeFromLua();    //LUA --> C++

void clear(){
    this->id = 0;
    this->xPos = 0;                 //->atributo redundante. Si no es necesario una estructura esqueletal
    this->yPos = 0;                 //->atributo redundante. Si no es necesario una estructura esqueletal
    this->idTile = 0;               //->atributo redundante. Si no es necesario una estructura esqueletal
    this->idMesh = 0;               //->atributo redundante, Si no es necesario una estructura esqueletal
    this->scriptAnim = "";
    this->scriptAI = "";
    clearBuffers();
}

void addLimitParentsXY(coordsXY data){
    if (this->lim < SIZE_COORD){
        limitsParents[lim].rel_pos_x = data.rel_pos_x;
        limitsParents[lim].rel_pos_y = data.rel_pos_y;
        lim++;
    }
}

uint8_t getLimitParentXY(){return this->lim;}

coordsXY getLimitParentsByIndex(int index){

    coordsXY coordDummy;
    coordDummy.rel_pos_x = 0;
    coordDummy.rel_pos_y = 0;

    if ((index >=0) && (index < SIZE_COORD)){
        return limitsParents[index];
    }else{
        return coordDummy;
    }
}


void copyBuffer(Entity *entityRef){

    uint8_t limits = entityRef->getLimitParentXY();
    clearBuffers();

    for(int i=0; i<limits; i++){
        coordsXY cXY = entityRef->getLimitParentsByIndex(i);
        addLimitParentsXY(cXY);
    }
}


protected:

uint32_t id;

float xPos;
float yPos;

uint32_t idTile;
uint32_t idMesh;

std::string scriptAnim;
std::string scriptAI;

coordsXY limitsParents[SIZE_COORD]; //-->atributo redundante. Si no es necesario una estructura esqueletal.
uint8_t lim;

void clearBuffers(){
    lim = 0;
    for(int i=0; i<SIZE_COORD; i++){
        limitsParents[i].rel_pos_x = 0;
        limitsParents[i].rel_pos_y = 0;
    }
}


};

#endif // ENTITY_H_INCLUDED
