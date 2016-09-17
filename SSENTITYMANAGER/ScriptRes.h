#ifndef SCRIPTRES_H_INCLUDED
#define SCRIPTRES_H_INCLUDED

/*
TABLE RES_SCRIPTDEF
ID          CHAR(20)                    //identificador del script lua ("GAMEPLAY_1","IA_1")
PATH        CHAR(100)                   //situacion del fichero de script lua
FUNCTION    CHAR(50)                    //nombre de la funcion a ejecutarse ("FUNCTION_1","FUNCTION_2")
BINARY      INT                         //identificador binario del script lua compilado. (el identificador puede cambiar)

Vector <ScriptParamRes> inputParams     //parametros de entrada
Vector <ScriptParamRes> outputParams    //parametros de salida.
*/

#include "Stdafx.h"
#include "Resource.h"
#include "ScriptParamRes.h"

class ScriptRes: public Resource{

public:


ScriptRes():Resource(false,0,SCRIPT_REF){
    this->id = "";
    this->path = "";
    this->functionLua = "";
    this->idLuaBinaryCompiled = 0;
};

ScriptRes(ScriptRes *refScript):Resource(false, 0, SCRIPT_REF){
    this->id = refScript->getId();
    this->path = refScript->getPath();
    this->functionLua = refScript->getFunctionLua();
    this->idLuaBinaryCompiled = refScript->getIdLuaBinaryCompiled();
    this->copyInputParams(refScript);
    this->copyOutputParam(refScript);
};

ScriptRes(uint32_t timestamp):Resource(false,timestamp,SCRIPT_REF){
    this->id = "";
    this->path = "";
    this->functionLua = "";
    this->idLuaBinaryCompiled = 0;
};

ScriptRes(ScriptRes *refScript,uint32_t timestamp):Resource(false, timestamp, SCRIPT_REF){
    this->id = refScript->getId();
    this->path = refScript->getPath();
    this->functionLua = refScript->getFunctionLua();
    this->idLuaBinaryCompiled = 0;
    this->copyInputParams(refScript);
    this->copyOutputParam(refScript);
};


~ScriptRes(){
    this->id = "";
    this->path = "";
    this->functionLua = "";
    this->idLuaBinaryCompiled = 0;
};

void copyTo(ScriptRes *refScript){
    this->id = refScript->getId();
    this->path = refScript->getPath();
    this->functionLua = refScript->getFunctionLua();
    this->idLuaBinaryCompiled = refScript->getIdLuaBinaryCompiled();
    this->copyInputParams(refScript);
    this->copyOutputParam(refScript);
};

//clear method
void clear(){
   this->id = "";
   this->path = "";
   this->functionLua = "";
   this->idLuaBinaryCompiled = 0;
   this->inputParams.clear();
   this->outputParams.clear();
};


std::string getId(){return this->id;}
void setId(std::string _id){this->id = _id;}

std::string getPath(){return this->path;}
void setPath(std::string _path){this->path = _path;}

std::string getFunctionLua(){return this->functionLua;}
void setFunctionLua(std::string _functionLua){this->functionLua = _functionLua;}

uint32_t getIdLuaBinaryCompiled(){return this->idLuaBinaryCompiled;}
void setIdLuaBinaryCompiled(uint32_t _idLuaBinaryCompiled){this->idLuaBinaryCompiled = _idLuaBinaryCompiled;}

//get-set params.
int getInputParamsSize(){return this->inputParams.size();}
int getOutputParamsSize(){return this->outputParams.size();}

std::vector<ScriptParamRes *> getInputParams(){return this->inputParams;}
std::vector<ScriptParamRes *> getOutputParams(){return this->outputParams;}

void setInputParam(ScriptParamRes *data){this->inputParams.push_back(data);}
void setOutputParam(ScriptParamRes *data){this->outputParams.push_back(data);}

ScriptParamRes *getInputParamByIndex(int index){
    return this->inputParams[index];
}

ScriptParamRes *getOutputParamByIndex(int index){
    return this->outputParams[index];
}

void copyInputParams(ScriptRes *refScript){
    std::vector<ScriptParamRes *> inputVectorCopy = refScript->getInputParams();
    this->inputParams.clear();

    for(unsigned int i=0; i<inputVectorCopy.size(); i++){
        this->inputParams.push_back(inputVectorCopy[i]);
    }
}

void copyOutputParam(ScriptRes *refScript){
    std::vector<ScriptParamRes *> outputVectorCopy = refScript->getOutputParams();
    this->outputParams.clear();

    for(unsigned int i=0; i<outputVectorCopy.size(); i++){
        this->outputParams.push_back(outputVectorCopy[i]);
    }
}

private:

std::string id;
std::string path;
std::string functionLua;
uint32_t idLuaBinaryCompiled;

typedef std::vector<ScriptParamRes *> ParamsType;

ParamsType inputParams;
ParamsType outputParams;

};


#endif // SCRIPTRES_H_INCLUDED
