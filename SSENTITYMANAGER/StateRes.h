#ifndef STATERES_H_INCLUDED
#define STATERES_H_INCLUDED

/*
TABLE RES_STATEDEF
ID          INT             //index del state
TYPE        INT             //TYPE of STATE 0->Game; 1->Menu; 2->Splash
PATH        CHAR(100)       //situacion de la definicion de un nivel.
STATE       INT             //0->START, 1->UPDATE, 2->RUN, 3->STOP, 4->CLEAR

map<id_action. referencia>  //referencias

(No veo la necesidad de cachear este resource. Ha de estar presente en cualquier momento del juego)
*/

#include "Stdafx.h"
#include "CoreString.h"
#include "StateDestinyRes.h"

class StateRes{

public:

    StateRes(){
        this->id = 0;
        this->type = 0;
        this->path = "";
        this->state = 0;
        StateDestinyMap.clear();

    }

    StateRes(StateRes *stateRef){
        this->id = stateRef->getId();
        this->type = stateRef->getType();
        this->path = CoreString::copySafetyString(stateRef->getPath());
        this->state = stateRef->getState();
    }

    ~StateRes(){
        this->id = 0;
        this->type = 0;
        this->path = "";
        this->state = 0;
        StateDestinyMap.clear();
    };

    void clear(){
        this->id = 0;
        this->type = 0;
        this->path = "";
        this->state = 0;
        StateDestinyMap.clear();
    }

    void copyto(StateRes *stateRef){
        this->id = stateRef->getId();
        this->type = stateRef->getType();
        this->path = CoreString::copySafetyString(stateRef->getPath());
        this->state = stateRef->getState();

    }

    uint32_t getId(){return id;}
    void setId(uint32_t _id){this->id = _id;}

    uint32_t getType(){return type;}
    void setType(uint32_t _type){this->type = _type;}

    std::string getPath(){return path;}
    void setPath(std::string _path){this->path = CoreString::copySafetyString(_path);}

    uint32_t getState(){return state;}
    void setState(uint32_t _state){this->state = _state;}

    //configuración de los estados futuros asociados a los estados de una accion
    std::map<uint32_t, StateDestinyRes *>getStateMap(){return this->StateDestinyMap;}

    StateDestinyRes *getStateDestinyResDefinition(uint32_t key){

        StateDestinyMapType::iterator it;
        it = StateDestinyMap.find(key);

        if (it!=StateDestinyMap.end()){
            return it->second;
        }else{
            return NULL;
        }
    }

    void addStateDestinyResDef(uint32_t key, StateDestinyRes *data){
        std::pair<int, StateDestinyRes *> node(key, data);
        StateDestinyMap.insert(node);
    }

    void copyStateDestinyRes(StateRes *stateRef){
        StateDestinyMapType StateDestinyCopy = stateRef->getStateMap();
        StateDestinyMap.clear();
    }


private:

    uint32_t id;
    uint32_t type;
    std::string path;
    uint32_t state;

    typedef std::map<uint32_t, StateDestinyRes *> StateDestinyMapType;
    StateDestinyMapType StateDestinyMap;

};



#endif // STATERES_H_INCLUDED
