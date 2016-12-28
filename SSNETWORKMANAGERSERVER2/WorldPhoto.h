#ifndef WORLDPHOTO_H_INCLUDED
#define WORLDPHOTO_H_INCLUDED

#include "DynamicEntity.h"

class WorldPhoto{

public:

WorldPhoto(){
}

~WorldPhoto(){
    EnemiesMap_lvl_1.clear();
    EnemiesMap_lvl_2.clear();
    EnemiesMap_lvl_3.clear();

    DynElemMap_lvl_1.clear();
    DynElemMap_lvl_2.clear();
    DynElemMap_lvl_3.clear();

    remPlayerMap.clear();

}


///////////////////////////////////////////////////////


std::map<int, DynamicEntity *> EnemiesMap_lvl_1;
std::map<int, DynamicEntity *> EnemiesMap_lvl_2;
std::map<int, DynamicEntity *> EnemiesMap_lvl_3;

std::map<int, DynamicEntity *> DynElemMap_lvl_1;
std::map<int, DynamicEntity *> DynElemMap_lvl_2;
std::map<int, DynamicEntity *> DynElemMap_lvl_3;

std::map<int, DynamicEntity *> remPlayerMap;


private:


};


#endif // WORLDPHOTO_H_INCLUDED
