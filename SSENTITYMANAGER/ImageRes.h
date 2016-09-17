#ifndef IMAGERES_H_INCLUDED
#define IMAGERES_H_INCLUDED

#include "Stdafx.h"
#include "Resource.h"

/*
DEFINITION
TABLE RES_IMAGEDEF
ID          CHAR(20)        //identificador de la imagen ("BURN_1","PLAYER_1")
ID_GL       UINT            //identificador OPENGL ES
PATH        CHAR(100)       //situacion de la imagen
TYPE        CHAR(5)         //tipo de la imagen ("BMP","JPG","PNG","ETC") ==> (identificador numérico?)
WIDTH       FLOAT
HEIGHT      FLOAT           //tamanyo en pixeles de la imagen (width x height)
PARALLAX    BYTE            //trato como parallax (0 = NO; 1 = SI)
BRG_CONV    BYTE            //conversion imagen de BRG a RGB (Error carga imagenes OPENGL ES)
LIN_NEAR    BYTE            //habilitado LINEAL_NEAREST (OPENGL ES) (Alineacion LINEAL (0); al objeto mas cercano NEAREST (1))
CLAMP       BYTE            //habilitado CLAMP (OPENGL ES) (En caso de no ser suitable; REPEAT-Repetir (0), CLAMP-Expandir (1))
MIPMAP      BYTE            //habilitado MIPMAPPING (OPENGL ES)
POWER2      BYTE            //conversion imagen a tamanyo multiplo de 2
TRANSPARENT BYTE            //añadir canal ALPHA (Solo para BMP RGB 888)

(incorporate assetts methods)

*/

class ImageRes : public Resource{

private:

std::string id;
uint16_t id_gl;
std::string path;
std::string type;
uint16_t width;
uint16_t height;
bool parallax;
bool brg_conv;
bool lin_near;
bool clamp;
bool mipmap;
bool power2;
bool transparent;


public:


void setId(std::string _id){this->id = _id;}
std::string getId(){return this->id;}

void setIdGl(uint16_t _id_gl){this->id_gl = _id_gl;}
uint16_t getIdGl(){return this->id_gl;}

void setPath(std::string _path){this->path = _path;}
std::string getPath(){return this->path;}

void setWidth(uint16_t _width){this->width = _width;}
uint16_t getWidth(){return this->width;}

void setHeight(uint16_t _height){this->height = _height;}
uint16_t getHeight(){return this->height;}

void setParallax(bool _parallax){this->parallax = _parallax;}
bool isParallax(){return this->parallax;}

void setBrgConv(bool _brg_conv){this->brg_conv = _brg_conv;}
bool isBrgConv(){return this->brg_conv;}

void setClamp(bool _clamp){this->clamp = _clamp;}
bool isClamp(){return this->clamp;}

void setLinNear(bool _is_lin_near){this->lin_near = _is_lin_near;}
bool isLinNear(){return this->lin_near;}

void setMipmap(bool _mipmap){this->mipmap = _mipmap;}
bool isMipmap(){return this->mipmap;}

void setPower2(bool _power2){this->power2 = _power2;}
bool isPower2(){return this->power2;}

void setTransparent(bool _transparent){this->transparent = _transparent;}
bool isTransparent(){return this->transparent;}


//constructor
ImageRes():Resource(false,0,IMAGE_REF){
    this->id = "";
    this->id_gl = -1;
    this->path = "";
    this->width = 0;
    this->height = 0;
    this->parallax = false;
    this->brg_conv = false;
    this->lin_near = false;
    this->clamp = false;
    this->mipmap = false;
    this->power2 = false;
    this->transparent = false;
};

//constructor by copy
ImageRes(ImageRes *refImage):Resource(false,0,IMAGE_REF){
    this->id = refImage->getId();
    this->id_gl = refImage->getIdGl();
    this->path = refImage->getPath();
    this->width = refImage->getWidth();
    this->height = refImage->getHeight();
    this->parallax = refImage->isParallax();
    this->brg_conv = refImage->isBrgConv();
    this->lin_near = refImage->isLinNear();
    this->clamp = refImage->isClamp();
    this->mipmap = refImage->isMipmap();
    this->power2 = refImage->isPower2();
    this->transparent = refImage->isTransparent();
};

ImageRes(uint32_t timestamp):Resource(false,timestamp,IMAGE_REF){
    this->id = "";
    this->id_gl = -1;
    this->path = "";
    this->width = 0;
    this->height = 0;
    this->parallax = false;
    this->brg_conv = false;
    this->lin_near = false;
    this->clamp = false;
    this->mipmap = false;
    this->power2 = false;
    this->transparent = false;
};

//constructor by copy
ImageRes(ImageRes *refImage, uint32_t timestamp):Resource(false,timestamp,IMAGE_REF){
    this->id = refImage->getId();
    this->id_gl = refImage->getIdGl();
    this->path = refImage->getPath();
    this->width = refImage->getWidth();
    this->height = refImage->getHeight();
    this->parallax = refImage->isParallax();
    this->brg_conv = refImage->isBrgConv();
    this->lin_near = refImage->isLinNear();
    this->clamp = refImage->isClamp();
    this->mipmap = refImage->isMipmap();
    this->power2 = refImage->isPower2();
    this->transparent = refImage->isTransparent();
};



//destructor
~ImageRes(){
    this->id = "";
    this->id_gl = -1;
    this->path = "";
    this->width = 0;
    this->height = 0;
    this->parallax = false;
    this->brg_conv = false;
    this->lin_near = false;
    this->clamp = false;
    this->mipmap = false;
    this->power2 = false;
    this->transparent = false;
};

//copy method
void copyTo(ImageRes *refImage){
    this->id = refImage->getId();
    this->id_gl = refImage->getIdGl();
    this->path = refImage->getPath();
    this->width = refImage->getWidth();
    this->height = refImage->getHeight();
    this->parallax = refImage->isParallax();
    this->brg_conv = refImage->isBrgConv();
    this->lin_near = refImage->isLinNear();
    this->clamp = refImage->isClamp();
    this->mipmap = refImage->isMipmap();
    this->power2 = refImage->isPower2();
    this->transparent = refImage->isTransparent();
};

//clear method
void clear(){
    this->id = "";
    this->id_gl = -1;
    this->path = "";
    this->width = 0;
    this->height = 0;
    this->parallax = false;
    this->brg_conv = false;
    this->lin_near = false;
    this->clamp = false;
    this->mipmap = false;
    this->power2 = false;
    this->transparent = false;
};



};

#endif // IMAGERES_H_INCLUDED
