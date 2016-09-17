#ifndef SOUNDRES_H_INCLUDED
#define SOUNDRES_H_INCLUDED

/*
TABLE RES_SOUNDDEF
ID          CHAR(20)        //identificador del script de sonido ("MUSIC_1","WAV_1")
PATH        CHAR(100)       //situacion del clip de sonido
EXT         CHAR(5)         //extension de sonido (WAV,OGG) ==> (identificador numerico?)
TYPE        INT             //0->clip musical. 1->efecto de sonido.
*/

#include "Stdafx.h"
#include "Resource.h"
#include "CoreString.h"

class SoundRes: public Resource{

public:

    SoundRes():Resource(false,0,SOUND_REF){
        this->id = "";
        this->path = "";
        this->ext = "";
        this->type = 0;
    };

    SoundRes(SoundRes *refSound):Resource(false,0,SOUND_REF){
        this->id = CoreString::copySafetyString(refSound->getId());
        this->path = CoreString::copySafetyString(refSound->getPath());
        this->ext = CoreString::copySafetyString(refSound->getExt());
        this->type = refSound->getType();
    };


    SoundRes(uint32_t timestamp):Resource(false,timestamp,SCRIPT_REF){
        this->id = "";
        this->path = "";
        this->ext = "";
        this->type = 0;
    };

    SoundRes(SoundRes *refSound, uint32_t timestamp):Resource(false,timestamp,SCRIPT_REF){
        this->id = CoreString::copySafetyString(refSound->getId());
        this->path = CoreString::copySafetyString(refSound->getPath());
        this->ext = CoreString::copySafetyString(refSound->getExt());
        this->type = refSound->getType();
    };

    ~SoundRes(){
        this->id = "";
        this->path = "";
        this->ext = "";
        this->type = 0;
    };

    void copyTo(SoundRes *refSound){
        this->id = CoreString::copySafetyString(refSound->getId());
        this->path = CoreString::copySafetyString(refSound->getPath());
        this->ext = CoreString::copySafetyString(refSound->getExt());
        this->type = refSound->getType();
    };

    //clear method
    void clear(){
        this->id = "";
        this->path = "";
        this->ext = "";
        this->type = 0;
    };

    std::string getId(){return id;}
    void setId(std::string _id){this->id = _id;}

    std::string getPath(){return path;}
    void setPath(std::string _path){this->path = _path;}

    std::string getExt(){return ext;}
    void setExt(std::string _ext){this->ext = _ext;}

    uint8_t getType(){return type;}
    void setType(uint8_t _type){type = _type;}

private:

    std::string id;
    std::string path;
    std::string ext;
    uint8_t type;
};

#endif // SOUNDRES_H_INCLUDED
