#ifndef LIGHTRES_H_INCLUDED
#define LIGHTRES_H_INCLUDED

#include "Stdafx.h"
#include "Resource.h"
#include "CoreString.h"

/*
TABLE RES_LIGHTRES

ID          CHAR(20)    //identificador LUZ
ID_TYPE     INT         //0->luz ambiental; 1->foco; 2->material

POS_X       FLOAT
POS_Y       FLOAT
POS_Z       FLOAT
POS_W       FLOAT       //posicion luz

DIR_X       FLOAT
DIR_Y       FLOAT
DIR_Z       FLOAT       //direccion luz -(FOCO)

CONST_AT    FLOAT       //atenuacion constante  - (FOCO)
LIN_AT      FLOAT       //atenuacion lineal     - (FOCO)
QA_AT       FLOAT       //atenuacion cuadratica - (FOCO)

CUT_OFF     FLOAT       //spot - cutoff         - (FOCO) longitud del foco
SPOT_EXP    FLOAT       //spot - exp            - (FOCO) amplitud del foco

AMB_X       FLOAT
AMB_Y       FLOAT
AMB_Z       FLOAT
AMB_W       FLOAT       //luz ambiental.

DIF_X       FLOAT
DIF_Y       FLOAT
DIF_Z       FLOAT
DIF_W       FLOAT       //luz difusa.

SPE_X       FLOAT
SPE_Y       FLOAT
SPE_Z       FLOAT
SPE_W       FLOAT       //luz specular.

EMI_X       FLOAT
EMI_Y       FLOAT
EMI_Z       FLOAT
EMI_W       FLOAT       //Emision.            - (MATERIAL)

SHININ      FLOAT       //brillo
*/

class LightRes  : public Resource{

public:

LightRes():Resource(false,0,LIGHT_REF){

    this->id = "";

    this->idtype = 0;
    this->posX = 0;
    this->posY = 0;
    this->posZ = 0;
    this->posW = 0;

    this->difX = 0;
    this->difY = 0;
    this->difW = 0;

    this->constAt = 0;
    this->linAt = 0;
    this->qaAt = 0;

    this->cutOff = 0;
    this->spotExp = 0;

    this->ambX = 0;
    this->ambY = 0;
    this->ambZ = 0;
    this->ambW = 0;

    this->difX = 0;
    this->difY = 0;
    this->difZ = 0;
    this->difW = 0;

    this->speX = 0;
    this->speY = 0;
    this->speZ = 0;
    this->speW = 0;

    this->emiX = 0;
    this->emiY = 0;
    this->emiZ = 0;
    this->emiW = 0;

    this->shinin = 0;
}


LightRes(uint32_t timestamp):Resource(false,timestamp,LIGHT_REF){
    this->id = "";

    this->idtype = 0;
    this->posX = 0;
    this->posY = 0;
    this->posZ = 0;
    this->posW = 0;

    this->difX = 0;
    this->difY = 0;
    this->difW = 0;

    this->constAt = 0;
    this->linAt = 0;
    this->qaAt = 0;

    this->cutOff = 0;
    this->spotExp = 0;

    this->ambX = 0;
    this->ambY = 0;
    this->ambZ = 0;
    this->ambW = 0;

    this->difX = 0;
    this->difY = 0;
    this->difZ = 0;
    this->difW = 0;

    this->speX = 0;
    this->speY = 0;
    this->speZ = 0;
    this->speW = 0;

    this->emiX = 0;
    this->emiY = 0;
    this->emiZ = 0;
    this->emiW = 0;

    this->shinin = 0;
}

LightRes(LightRes *lRes):Resource(false,0,LIGHT_REF){
     this->id = CoreString::copySafetyString(lRes->getId());

    this->idtype = lRes->getIdType();
    this->posX = lRes->getPosX();
    this->posY = lRes->getPosY();
    this->posZ = lRes->getPosZ();
    this->posW = lRes->getPosW();

    this->difX = lRes->getDifX();
    this->difY = lRes->getDifY();
    this->difW = lRes->getDifW();

    this->constAt = lRes->getConstAt();
    this->linAt = lRes->getLinAt();
    this->qaAt = lRes->getQaAt();

    this->cutOff = lRes->getCutOff();
    this->spotExp = lRes->getSpotExp();

    this->ambX = lRes->getAmbX();
    this->ambY = lRes->getAmbY();
    this->ambZ = lRes->getAmbZ();
    this->ambW = lRes->getAmbW();

    this->difX = lRes->getDifX();
    this->difY = lRes->getDifY();
    this->difZ = lRes->getDifZ();
    this->difW = lRes->getDifW();

    this->speX = lRes->getSpeX();
    this->speY = lRes->getSpeY();
    this->speZ = lRes->getSpeZ();
    this->speW = lRes->getSpeW();

    this->emiX = lRes->getEmiX();
    this->emiY = lRes->getEmiY();
    this->emiZ = lRes->getEmiZ();
    this->emiW = lRes->getEmiW();

    this->shinin = lRes->getShinin();
}


LightRes(LightRes *lRes, uint32_t timestamp):Resource(false,timestamp,LIGHT_REF){
     this->id = CoreString::copySafetyString(lRes->getId());

    this->idtype = lRes->getIdType();
    this->posX = lRes->getPosX();
    this->posY = lRes->getPosY();
    this->posZ = lRes->getPosZ();
    this->posW = lRes->getPosW();

    this->difX = lRes->getDifX();
    this->difY = lRes->getDifY();
    this->difW = lRes->getDifW();

    this->constAt = lRes->getConstAt();
    this->linAt = lRes->getLinAt();
    this->qaAt = lRes->getQaAt();

    this->cutOff = lRes->getCutOff();
    this->spotExp = lRes->getSpotExp();

    this->ambX = lRes->getAmbX();
    this->ambY = lRes->getAmbY();
    this->ambZ = lRes->getAmbZ();
    this->ambW = lRes->getAmbW();

    this->difX = lRes->getDifX();
    this->difY = lRes->getDifY();
    this->difZ = lRes->getDifZ();
    this->difW = lRes->getDifW();

    this->speX = lRes->getSpeX();
    this->speY = lRes->getSpeY();
    this->speZ = lRes->getSpeZ();
    this->speW = lRes->getSpeW();

    this->emiX = lRes->getEmiX();
    this->emiY = lRes->getEmiY();
    this->emiZ = lRes->getEmiZ();
    this->emiW = lRes->getEmiW();

    this->shinin = lRes->getShinin();
}

~LightRes(){
    this->id = "";

    this->idtype = 0;
    this->posX = 0;
    this->posY = 0;
    this->posZ = 0;
    this->posW = 0;

    this->difX = 0;
    this->difY = 0;
    this->difW = 0;

    this->constAt = 0;
    this->linAt = 0;
    this->qaAt = 0;

    this->cutOff = 0;
    this->spotExp = 0;

    this->ambX = 0;
    this->ambY = 0;
    this->ambZ = 0;
    this->ambW = 0;

    this->difX = 0;
    this->difY = 0;
    this->difZ = 0;
    this->difW = 0;

    this->speX = 0;
    this->speY = 0;
    this->speZ = 0;
    this->speW = 0;

    this->emiX = 0;
    this->emiY = 0;
    this->emiZ = 0;
    this->emiW = 0;

    this->shinin = 0;

}


void clear(){
    this->id = "";

    this->idtype = 0;
    this->posX = 0;
    this->posY = 0;
    this->posZ = 0;
    this->posW = 0;

    this->difX = 0;
    this->difY = 0;
    this->difW = 0;

    this->constAt = 0;
    this->linAt = 0;
    this->qaAt = 0;

    this->cutOff = 0;
    this->spotExp = 0;

    this->ambX = 0;
    this->ambY = 0;
    this->ambZ = 0;
    this->ambW = 0;

    this->difX = 0;
    this->difY = 0;
    this->difZ = 0;
    this->difW = 0;

    this->speX = 0;
    this->speY = 0;
    this->speZ = 0;
    this->speW = 0;

    this->emiX = 0;
    this->emiY = 0;
    this->emiZ = 0;
    this->emiW = 0;

    this->shinin = 0;
}

void copyTo(LightRes *lRes){

    this->id = CoreString::copySafetyString(lRes->getId());

    this->idtype = lRes->getIdType();
    this->posX = lRes->getPosX();
    this->posY = lRes->getPosY();
    this->posZ = lRes->getPosZ();
    this->posW = lRes->getPosW();

    this->difX = lRes->getDifX();
    this->difY = lRes->getDifY();
    this->difW = lRes->getDifW();

    this->constAt = lRes->getConstAt();
    this->linAt = lRes->getLinAt();
    this->qaAt = lRes->getQaAt();

    this->cutOff = lRes->getCutOff();
    this->spotExp = lRes->getSpotExp();

    this->ambX = lRes->getAmbX();
    this->ambY = lRes->getAmbY();
    this->ambZ = lRes->getAmbZ();
    this->ambW = lRes->getAmbW();

    this->difX = lRes->getDifX();
    this->difY = lRes->getDifY();
    this->difZ = lRes->getDifZ();
    this->difW = lRes->getDifW();

    this->speX = lRes->getSpeX();
    this->speY = lRes->getSpeY();
    this->speZ = lRes->getSpeZ();
    this->speW = lRes->getSpeW();

    this->emiX = lRes->getEmiX();
    this->emiY = lRes->getEmiY();
    this->emiZ = lRes->getEmiZ();
    this->emiW = lRes->getEmiW();

    this->shinin = lRes->getShinin();

}



std::string getId(){return this->id;}
void setId(std::string _id){this->id = CoreString::copySafetyString(_id);}

int getIdType(){return this->idtype;}
void setIdType(int _idtype){this->idtype = _idtype;}

float getPosX(){return this->posX;}
void setPosX(float _posX){this->posX = _posX;}

float getPosY(){return this->posY;}
void setPosY(float _posY){this->posY = _posY;}

float getPosZ(){return this->posZ;}
void setPosZ(float _posZ){this->posZ = _posZ;}

float getPosW(){return this->posW;}
void setPosW(float _posW){this->posW = _posW;}

float getDirX(){return this->dirX;}
void setDirX(float _dirX){this->dirX = _dirX;}

float getDirY(){return this->dirY;}
void setDirY(float _dirY){this->dirY = _dirY;}

float getDirZ(){return this->dirZ;}
void setDirZ(float _dirZ){this->dirZ = _dirZ;}

float getConstAt(){return this->constAt;}
void setConstAt(float _constAt){this->constAt = _constAt;}

float getLinAt(){return this->linAt;}
void setLinAt(float _linAt){this->linAt = _linAt;}

float getQaAt(){return this->qaAt;}
void setQaAt(float _qaAt){this->qaAt = _qaAt;}

float getCutOff(){return this->cutOff;}
void setCutOff(float _cutOff){this->cutOff = _cutOff;}

float getSpotExp(){return this->spotExp;}
void setSpotExp(float _spotExp){this->spotExp = _spotExp;}

float getAmbX(){return this->ambX;}
void setAmbX(float _ambX){this->ambX = _ambX;}

float getAmbY(){return this->ambY;}
void setAmbY(float _ambY){this->ambY = _ambY;}

float getAmbZ(){return this->ambZ;}
void setAmbZ(float _ambZ){this->ambZ = _ambZ;}

float getAmbW(){return this->ambW;}
void setAmbW(float _ambW){this->ambW = _ambW;}

float getDifX(){return this->difX;}
void setDifX(float _difX){this->difX = _difX;}

float getDifY(){return this->difY;}
void setDifY(float _difY){this->difY = _difY;}

float getDifZ(){return this->difZ;}
void setDifZ(float _difZ){this->difZ = _difZ;}

float getDifW(){return this->difW;}
void setDifW(float _difW){this->difW = _difW;}

float getSpeX(){return this->speX;}
void setSpeX(float _speX){this->speX = _speX;}

float getSpeY(){return this->speY;}
void setSpeY(float _speY){this->speY = _speY;}

float getSpeZ(){return this->speZ;}
void setSpeZ(float _speZ){this->speZ = _speZ;}

float getSpeW(){return this->speW;}
void setSpeW(float _speW){this->speW = _speW;}

float getEmiX(){return this->emiX;}
void setEmiX(float _emiX){this->emiX = _emiX;}

float getEmiY(){return this->emiY;}
void setEmiY(float _emiY){this->emiY = _emiY;}

float getEmiZ(){return this->emiZ;}
void setEmiZ(float _emiZ){this->emiZ = _emiZ;}

float getEmiW(){return this->emiW;}
void setEmiW(float _emiW){this->emiW = _emiW;}

float getShinin(){return this->shinin;}
void setShinin(float _shinin){this->shinin = _shinin;}

private:

std::string id;
int idtype;
float posX;
float posY;
float posZ;
float posW;

float dirX;
float dirY;
float dirZ;

float constAt;
float linAt;
float qaAt;

float cutOff;
float spotExp;

float ambX;
float ambY;
float ambZ;
float ambW;

float difX;
float difY;
float difZ;
float difW;

float speX;
float speY;
float speZ;
float speW;

float emiX;
float emiY;
float emiZ;
float emiW;

float shinin;

};

#endif // LIGHTRES_H_INCLUDED
