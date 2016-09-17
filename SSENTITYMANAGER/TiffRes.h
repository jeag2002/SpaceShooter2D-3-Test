#ifndef TIFFRES_H_INCLUDED
#define TIFFRES_H_INCLUDED

#include "Stdafx.h"
#include "Resource.h"
#include "CoreString.h"
/*
TABLE RES_TIFFDEF
ID          CHAR(20)        //identificador del TIFF (fuente)
PATH        CHAR(100)       //situacion de la fuente
SIZE        FLOAT           //tamaño de la fuente
R_COLOR     INT
G_COLOR     INT
B_COLOR     INT
*/

class TiffRes : public Resource{

public:

    TiffRes():Resource(false,0,TIFF_REF){
        this->id = "";
        this->path = "";
        this->size = 0.0f;
        this->rcolor = 0;
        this->gcolor = 0;
        this->bcolor = 0;
    };

    TiffRes(uint32_t timestamp):Resource(false,timestamp,TIFF_REF){
        this->id = "";
        this->path = "";
        this->size = 0.0f;
        this->rcolor = 0;
        this->gcolor = 0;
        this->bcolor = 0;
    };

    TiffRes(TiffRes *tiffRef){
        this->id = CoreString::copySafetyString(tiffRef->getId());
        this->path = CoreString::copySafetyString(tiffRef->getPath());
        this->size = tiffRef->getSize();
        this->rcolor = tiffRef->getRColor();
        this->gcolor = tiffRef->getGColor();
        this->bcolor = tiffRef->getBColor();
    };

    void copyTo(TiffRes *tiffRef){
        this->id = CoreString::copySafetyString(tiffRef->getId());
        this->path = CoreString::copySafetyString(tiffRef->getPath());
        this->size = tiffRef->getSize();
        this->rcolor = tiffRef->getRColor();
        this->gcolor = tiffRef->getGColor();
        this->bcolor = tiffRef->getBColor();
    }

    void clear(){
        this->id = "";
        this->path = "";
        this->size = 0.0f;
        this->rcolor = 0;
        this->gcolor = 0;
        this->bcolor = 0;
    }

    std::string getId(){return id;}
    void setId(std::string _id){this->id = CoreString::copySafetyString(_id);}

    std::string getPath(){return path;}
    void setPath(std::string _path){this->path = CoreString::copySafetyString(_path);}

    float getSize(){return size;}
    void setSize(float _size){this->size = _size;}

    uint8_t getRColor(){return rcolor;}
    void setRColor(uint8_t _rcolor){this->rcolor = _rcolor;}

    uint8_t getGColor(){return gcolor;}
    void setGColor(uint8_t _gcolor){this->gcolor = _gcolor;}

    uint8_t getBColor(){return bcolor;}
    void setBColor(uint8_t _bcolor){this->bcolor = _bcolor;}


private:

    std::string id;
    std::string path;
    float size;
    uint8_t rcolor;
    uint8_t gcolor;
    uint8_t bcolor;
};

#endif // TIFFRES_H_INCLUDED
