#ifndef SHADERRES_H_INCLUDED
#define SHADERRES_H_INCLUDED


#include "Stdafx.h"
#include "Resource.h"
#include "CoreString.h"


/*
TABLE RES_SHADER
ID         CHAR(20)     //identificador del SHADER
PATH       CHAR(100)    //situacion de la fuente
TYPE       INT          //(0=>vertex shader, 1=fragment shader, 2=geometry shader)
*/


class ShaderRes : public Resource{

public:

    ShaderRes():Resource(false,0,SHADER_REF){
        this->id = "";
        this->id_compiled = 0;
        this->path = "";
        this->type = 0;
    }

    ShaderRes(uint32_t timestamp):Resource(false,timestamp,SHADER_REF){
        this->id = "";
        this->id_compiled = 0;
        this->path = "";
        this->type = 0;
    }

    ShaderRes(ShaderRes *shaderRef):Resource(false,0,SHADER_REF){
        this->id = CoreString::copySafetyString(shaderRef->getId());
        this->id_compiled = shaderRef->getIdCompiled();
        this->path = CoreString::copySafetyString(shaderRef->getPath());
        this->type = shaderRef->getType();
    }

    ShaderRes(ShaderRes *shaderRef,uint32_t timestamp):Resource(false,timestamp,SHADER_REF){
        this->id = CoreString::copySafetyString(shaderRef->getId());
        this->id_compiled = shaderRef->getIdCompiled();
        this->path = CoreString::copySafetyString(shaderRef->getPath());
        this->type = shaderRef->getType();
    }

    ~ShaderRes(){
        this->id = "";
        this->id_compiled = 0;
        this->path = "";
        this->type = 0;
    }

    void clear(){
        this->id = "";
        this->id_compiled = 0;
        this->path = "";
        this->type = 0;
    }

    void setId(std::string _id){this->id = CoreString::copySafetyString(_id);}
    std::string getId(){return this->id;}

    void setIdCompiled(uint32_t _id_compiled){this->id_compiled = _id_compiled;}
    uint32_t getIdCompiled(){return this->id_compiled;}

    void setPath(std::string _path){this->path = CoreString::copySafetyString(_path);}
    std::string getPath(){return this->path;}

    void setType(uint8_t _type){this->type = _type;}
    uint8_t setType(){return this->type;}

private:
    std::string id;
    uint32_t id_compiled;
    std::string path;
    uint8_t type;
};

#endif // SHADERRES_H_INCLUDED
