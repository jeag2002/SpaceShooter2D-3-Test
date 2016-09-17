#ifndef TILECOMPONENT_H_INCLUDED
#define TILECOMPONENT_H_INCLUDED

#include "Stdafx.h"
#include "Resource.h"
#include "CoreString.h"
#include "TileComponentCoord.h"

/*
TABLE ENT_TILE_COMP        //-->Definicion componentes de un tile.

IDCOMP          INT        //identificador COMPONENTE TILE
ID              INT        //identificador TILE asociado.
POS_X_COMP      FLOAT
POS_Y_COMP      FLOAT      //situacion x,y referencial del componente
WIDTH_COMP      FLOAT
HEIGHT_COMP     FLOAT      //width x height del componente
IMAGE           CHAR(20)   //identificador IMAGE componente
IMAGE_CMB       CHAR(20)
MASK            CHAR(20)   //identificador MASK componente
MASK_CMB        CHAR(20)
LIGHTMAP        CHAR(20)   //identificador LIGHTMAP componente
LIGHTMAP_CMB    CHAR(20)
BUMPMAP         CHAR(20)   //identificador BUMPMAP componente
BUMPMAP_CMB     CHAR(20)
*/

class TileComponent{

private:

uint32_t idcomp;
uint32_t id;
float posXComponent;
float posYComponent;
float widthComponent;
float heightComponent;

std::string image;
std::string imageCMB;

std::string mask;
std::string maskCMB;

std::string lightMap;
std::string lightMapCMB;

std::string bumpMap;
std::string bumpMapCMB;

std::vector<TileComponentCoord *>coordinates;

public:

TileComponent(){
    this->idcomp = 0;
    this->id = 0;
    this->posXComponent = 0;
    this->posYComponent = 0;
    this->widthComponent = 0;
    this->heightComponent = 0;

    this->image = "";
    this->imageCMB = "";

    this->mask = "";
    this->maskCMB = "";

    this->lightMap = "";
    this->lightMapCMB = "";

    this->bumpMap = "";
    this->bumpMapCMB = "";

    coordinates.clear();
}

TileComponent(TileComponent *tileComponentRef){

    this->id = tileComponentRef->getId();
    this->idcomp = tileComponentRef->getIdComp();
    this->posXComponent = tileComponentRef->getPosXComponent();
    this->posYComponent = tileComponentRef->getPosYComponent();
    this->widthComponent = tileComponentRef->getWidthComponent();
    this->heightComponent = tileComponentRef->getHeightComponent();

    this->image = CoreString::copySafetyString(tileComponentRef->getImage());
    this->imageCMB = CoreString::copySafetyString(tileComponentRef->getImageCMB());
    this->mask = CoreString::copySafetyString(tileComponentRef->getMask());
    this->maskCMB = CoreString::copySafetyString(tileComponentRef->getMaskCMB());
    this->lightMap = CoreString::copySafetyString(tileComponentRef->getLightMap());
    this->lightMapCMB = CoreString::copySafetyString(tileComponentRef->getLightMapCMB());
    this->bumpMap = CoreString::copySafetyString(tileComponentRef->getBumpMap());
    this->bumpMapCMB = CoreString::copySafetyString(tileComponentRef->getBumpMapCMB());

}

~TileComponent(){
    this->idcomp = 0;
    this->id = 0;
    this->posXComponent = 0;
    this->posYComponent = 0;
    this->widthComponent = 0;
    this->heightComponent = 0;

    this->image = "";
    this->imageCMB = "";

    this->mask = "";
    this->maskCMB = "";

    this->lightMap = "";
    this->lightMapCMB = "";

    this->bumpMap = "";
    this->bumpMapCMB = "";

    coordinates.clear();
}

void clear(){
    this->idcomp = 0;
    this->id = 0;
    this->posXComponent = 0;
    this->posYComponent = 0;
    this->widthComponent = 0;
    this->heightComponent = 0;

    this->image = "";
    this->imageCMB = "";

    this->mask = "";
    this->maskCMB = "";

    this->lightMap = "";
    this->lightMapCMB = "";

    this->bumpMap = "";
    this->bumpMapCMB = "";

    coordinates.clear();
}

void copyTo(TileComponent *tileComponentRef){
    this->id = tileComponentRef->getId();
    this->idcomp = tileComponentRef->getIdComp();
    this->posXComponent = tileComponentRef->getPosXComponent();
    this->posYComponent = tileComponentRef->getPosYComponent();
    this->widthComponent = tileComponentRef->getWidthComponent();
    this->heightComponent = tileComponentRef->getHeightComponent();

    this->image = CoreString::copySafetyString(tileComponentRef->getImage());
    this->imageCMB = CoreString::copySafetyString(tileComponentRef->getImageCMB());
    this->mask = CoreString::copySafetyString(tileComponentRef->getMask());
    this->maskCMB = CoreString::copySafetyString(tileComponentRef->getMaskCMB());
    this->lightMap = CoreString::copySafetyString(tileComponentRef->getLightMap());
    this->lightMapCMB = CoreString::copySafetyString(tileComponentRef->getLightMapCMB());
    this->bumpMap = CoreString::copySafetyString(tileComponentRef->getBumpMap());
    this->bumpMapCMB = CoreString::copySafetyString(tileComponentRef->getBumpMapCMB());
}


uint32_t getIdComp(){return idcomp;}
void setIdComp(uint32_t _idcomp){this->idcomp = _idcomp;}

uint32_t getId(){return id;}
void setId(uint32_t _id){this->id = _id;}

float getPosXComponent(){return posXComponent;}
void setPosXComponent(float _posXComponent){this->posXComponent = _posXComponent;}

float getPosYComponent(){return posYComponent;}
void setPosYComponent(float _posYComponent){this->posYComponent = _posYComponent;}

float getWidthComponent(){return widthComponent;}
void setWidthComponent(float _widthComponent){this->widthComponent = _widthComponent;}

float getHeightComponent(){return heightComponent;}
void setHeightComponent(float _heightComponent){this->heightComponent = _heightComponent;}

std::string getImage(){return image;}
void setImage(std::string _image){this->image = CoreString::copySafetyString(_image);}

std::string getImageCMB(){return imageCMB;}
void setImageCMB(std::string _imageCMB){this->imageCMB = CoreString::copySafetyString(_imageCMB);}

std::string getMask(){return mask;}
void setMask(std::string _mask){this->mask = CoreString::copySafetyString(_mask);}

std::string getMaskCMB(){return maskCMB;}
void setMaskCMB(std::string _maskCMB){this->maskCMB = CoreString::copySafetyString(_maskCMB);}

std::string getLightMap(){return lightMap;}
void setLightMap(std::string _lightMap){this->lightMap = CoreString::copySafetyString(_lightMap);}

std::string getLightMapCMB(){return lightMapCMB;}
void setLightMapCMB(std::string _lightMapCMB){this->lightMapCMB = CoreString::copySafetyString(_lightMapCMB);}

std::string getBumpMap(){return bumpMap;}
void setBumpMap(std::string _bumpMap){this->bumpMap = CoreString::copySafetyString(_bumpMap);}

std::string getBumpMapCMB(){return bumpMapCMB;}
void setBumpMapCMB(std::string _bumpMapCMB){this->bumpMapCMB = CoreString::copySafetyString(_bumpMapCMB);}

std::vector<TileComponentCoord *> getCoordinatesVector(){return coordinates;}
int getCoordinatesVectorSize(){return coordinates.size();}

TileComponentCoord *getCoordinateByIndex(int index){return coordinates[index];}

void copyCoordinates(TileComponent *tileComponentRef){
    int sizeComponents = tileComponentRef->getCoordinatesVectorSize();
    coordinates.clear();
    for(int i=0; i<sizeComponents; i++){
        TileComponentCoord *tCC = new TileComponentCoord(tileComponentRef->getCoordinateByIndex(i));
        coordinates.push_back(tCC);
    }
}




};



#endif // TILECOMPONENT_H_INCLUDED
