#ifndef PARTICLERES_H_INCLUDED
#define PARTICLERES_H_INCLUDED

#include "Stdafx.h"
#include "Resource.h"
#include "CoreString.h"

/*
TABLE RES_PARTICLEDEF
ID          CHAR(20)       //identificador PARTICULA
ID_IMAGE    CHAR(20)       //identificador IMAGEN_ASOCIADA
X_1         FLOAT
Y_1         FLOAT
SCALE       INT
MAX         INT
ALPHA_INF   INT
ALPHA_SUP   INT
R_COLOR_INF INT
G_COLOR_INF INT
B_COLOR_INF INT
R_COLOR_SUP INT
G_COLOR_SUP INT
B_COLOR_SUP INT
VELOCITY    FLOAT
DIRECTION   FLOAT
SPREAD      INT
LENGTH      INT
*/

class ParticleRes : public Resource{

public:

ParticleRes():Resource(false,0,PARTICLE_REF){

   this->id = "";
   this->idimage = "";
   this->x = 0;
   this->y = 0;
   this->scale = 0;
   this->maximum = 0;
   this->alphain = 0;
   this->alphasup = 0;
   this->rcolorinf = 0;
   this->bcolorinf = 0;
   this->gcolorinf = 0;
   this->rcolorsup = 0;
   this->bcolorsup = 0;
   this->gcolorsup = 0;
   this->velocity = 0;
   this->direction = 0;
   this->spread = 0;
   this->lenght = 0;
}

ParticleRes(ParticleRes *particleRef):Resource(false,0,PARTICLE_REF){

   this->id = CoreString::copySafetyString(particleRef->getId());
   this->idimage = CoreString::copySafetyString(particleRef->getIdImage());
   this->x = particleRef->getX();
   this->y = particleRef->getY();
   this->scale = particleRef->getScale();
   this->maximum = particleRef->getMaximum();
   this->alphain = particleRef->getAlphaIn();
   this->alphasup = particleRef->getAlphaSup();
   this->rcolorinf = particleRef->getRColorInf();
   this->bcolorinf = particleRef->getBColorInf();
   this->gcolorinf = particleRef->getGColorInf();
   this->rcolorsup = particleRef->getRColorSup();
   this->bcolorsup = particleRef->getBColorSup();
   this->gcolorsup = particleRef->getGColorSup();
   this->velocity = particleRef->getVelocity();
   this->direction = particleRef->getDirection();
   this->spread = particleRef->getSpread();
   this->lenght = particleRef->getLenght();
}



ParticleRes(uint32_t timestamp):Resource(false,timestamp,PARTICLE_REF){

   this->id = "";
   this->idimage = "";
   this->x = 0;
   this->y = 0;
   this->scale = 0;
   this->maximum = 0;
   this->alphain = 0;
   this->alphasup = 0;
   this->rcolorinf = 0;
   this->bcolorinf = 0;
   this->gcolorinf = 0;
   this->rcolorsup = 0;
   this->bcolorsup = 0;
   this->gcolorsup = 0;
   this->velocity = 0;
   this->direction = 0;
   this->spread = 0;
   this->lenght = 0;
}

ParticleRes(ParticleRes *particleRef,uint32_t timestamp):Resource(false,timestamp,PARTICLE_REF){

   this->id = CoreString::copySafetyString(particleRef->getId());
   this->idimage = CoreString::copySafetyString(particleRef->getIdImage());
   this->x = particleRef->getX();
   this->y = particleRef->getY();
   this->scale = particleRef->getScale();
   this->maximum = particleRef->getMaximum();
   this->alphain = particleRef->getAlphaIn();
   this->alphasup = particleRef->getAlphaSup();
   this->rcolorinf = particleRef->getRColorInf();
   this->bcolorinf = particleRef->getBColorInf();
   this->gcolorinf = particleRef->getGColorInf();
   this->rcolorsup = particleRef->getRColorSup();
   this->bcolorsup = particleRef->getBColorSup();
   this->gcolorsup = particleRef->getGColorSup();
   this->velocity = particleRef->getVelocity();
   this->direction = particleRef->getDirection();
   this->spread = particleRef->getSpread();
   this->lenght = particleRef->getLenght();
}


~ParticleRes(){
   this->id = "";
   this->idimage = "";
   this->x = 0;
   this->y = 0;
   this->scale = 0;
   this->maximum = 0;
   this->alphain = 0;
   this->alphasup = 0;
   this->rcolorinf = 0;
   this->bcolorinf = 0;
   this->gcolorinf = 0;
   this->rcolorsup = 0;
   this->bcolorsup = 0;
   this->gcolorsup = 0;
   this->velocity = 0;
   this->direction = 0;
   this->spread = 0;
   this->lenght = 0;
}

void copyTo(ParticleRes *particleRef){
   this->id = CoreString::copySafetyString(particleRef->getId());
   this->idimage = CoreString::copySafetyString(particleRef->getIdImage());
   this->x = particleRef->getX();
   this->y = particleRef->getY();
   this->scale = particleRef->getScale();
   this->maximum = particleRef->getMaximum();
   this->alphain = particleRef->getAlphaIn();
   this->alphasup = particleRef->getAlphaSup();
   this->rcolorinf = particleRef->getRColorInf();
   this->bcolorinf = particleRef->getBColorInf();
   this->gcolorinf = particleRef->getGColorInf();
   this->rcolorsup = particleRef->getRColorSup();
   this->bcolorsup = particleRef->getBColorSup();
   this->gcolorsup = particleRef->getGColorSup();
   this->velocity = particleRef->getVelocity();
   this->direction = particleRef->getDirection();
   this->spread = particleRef->getSpread();
   this->lenght = particleRef->getLenght();
}

void clear(){
   this->id = "";
   this->idimage = "";
   this->x = 0;
   this->y = 0;
   this->scale = 0;
   this->maximum = 0;
   this->alphain = 0;
   this->alphasup = 0;
   this->rcolorinf = 0;
   this->bcolorinf = 0;
   this->gcolorinf = 0;
   this->rcolorsup = 0;
   this->bcolorsup = 0;
   this->gcolorsup = 0;
   this->velocity = 0;
   this->direction = 0;
   this->spread = 0;
   this->lenght = 0;
}

std::string getId(){return this->id;}
void setId(std::string _id){this->id = CoreString::copySafetyString(_id);}

std::string getIdImage(){return this->idimage;}
void setIdImage(std::string _idimage){this->idimage = CoreString::copySafetyString(_idimage);}

float getX(){return this->x;}
void setX(float _x){this->x = _x;}

float getY(){return this->y;}
void setY(float _y){this->y = _y;}

uint8_t getScale(){return this->scale;}
void setScale(uint8_t _scale){this->scale = _scale;}

uint8_t getMaximum(){return this->maximum;}
void setMaximum(uint8_t _maximum){this->maximum = _maximum;}

uint8_t getAlphaIn(){return this->alphain;}
void setAlphaIn(uint8_t _alphain){this->alphain = _alphain;}

uint8_t getAlphaSup(){return this->alphasup;}
void setAlphaSup(uint8_t _alphasup){this->alphasup = _alphasup;}

uint8_t getRColorInf(){return this->rcolorinf;}
void setRColorInf(uint8_t _rcolorinf){this->rcolorinf = _rcolorinf;}

uint8_t getBColorInf(){return this->bcolorinf;}
void setBColorInf(uint8_t _bcolorinf){this->bcolorinf = _bcolorinf;}

uint8_t getGColorInf(){return this->gcolorinf;}
void setGColorInf(uint8_t _gcolorinf){this->gcolorinf = _gcolorinf;}

uint8_t getRColorSup(){return this->rcolorsup;}
void setRColorSup(uint8_t _rcolorsup){this->rcolorsup = _rcolorsup;}

uint8_t getBColorSup(){return this->bcolorsup;}
void setBColorSup(uint8_t _bcolorsup){this->bcolorsup = _bcolorsup;}

uint8_t getGColorSup(){return this->gcolorsup;}
void setGColorSup(uint8_t _gcolorsup){this->gcolorsup = _gcolorsup;}

float getVelocity(){return this->velocity;}
void setVelocity(float _velocity){this->velocity = _velocity;}

float getDirection(){return this->direction;}
void setDirection(float _direction){this->direction = _direction;}

uint8_t getSpread(){return this->spread;}
void setSpread(uint8_t _spread){this->spread = _spread;}

uint8_t getLenght(){return this->lenght;}
void setLenght(float _lenght){this->lenght = _lenght;}

private:

std::string id;
std::string idimage;
float x;
float y;
uint8_t scale;
uint8_t maximum;
uint8_t alphain;
uint8_t alphasup;
uint8_t rcolorinf;
uint8_t bcolorinf;
uint8_t gcolorinf;
uint8_t rcolorsup;
uint8_t bcolorsup;
uint8_t gcolorsup;
float velocity;
float direction;
uint8_t spread;
uint8_t lenght;

};

#endif // PARTICLERES_H_INCLUDED
