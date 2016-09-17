#ifndef SCRIPTPARAMRES_H_INCLUDED
#define SCRIPTPARAMRES_H_INCLUDED

/*
TABLE RES_SCRIPTDEFPARAM    //evaluar si es necesario crear esta dependencia
ID          CHAR(20)        //script lua
FUNCTION    CHAR(50)        //nombre de la funcion a ejecutarse
IO          BYTE            //0(INPUT); 1(OUTPUT)
NAME        CHAR(10)        //nombre del parametro
TYPEPAR     CHAR(6)         //tipo del parametro ("INT","CHAR","STRING","FLOAT","DOUBLE") ==> (identificador numérico?)
VALUE       CHAR(6)         //valor por defecto del script

(defino como un elemento compositor del ScriptRes. Acepto duplicados de objetos aunque esto haga que aumente el footprint de memoria)
*/

#include "Stdafx.h"

class ScriptParamRes{

public:

ScriptParamRes(){
    idScript = "";
    functionScript = "";
    input = false;
    param = "";
    type_param = 0;
};

ScriptParamRes(ScriptParamRes *refParamScript){
    this->idScript = refParamScript->getIdScript();
    this->functionScript = refParamScript->getFunctionScript();
    this->input = refParamScript->isInput();
    this->param = refParamScript->getParam();
    this->type_param = refParamScript->getTypeParam();
};

~ScriptParamRes(){
    idScript = "";
    functionScript = "";
    input = false;
    param = "";
    type_param = 0;
};

std::string getIdScript(){return idScript;}
void setIdScript(std::string _idScript){this->idScript = _idScript;}

std::string getFunctionScript(){return functionScript;}
void setIdFunctionScript(std::string _functionScript){this->functionScript = _functionScript;}

bool isInput(){return input;}
void setInput(bool _input){this->input = _input;}

std::string getParam(){return param;}
void setParam(std::string _param){this->param = _param;}

uint16_t getTypeParam(){return type_param;}
void setTypeParam(uint16_t _type_param){this->type_param = _type_param;}

private:

std::string idScript;
std::string functionScript;
bool input;
std::string param;
uint16_t type_param;

};

#endif // SCRIPTPARAMRES_H_INCLUDED
