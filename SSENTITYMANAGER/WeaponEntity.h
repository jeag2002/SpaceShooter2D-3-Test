#ifndef WEAPONENTITY_H_INCLUDED
#define WEAPONENTITY_H_INCLUDED

#include "Stdafx.h"
#include "Entity.h"
#include "CoreString.h"
#include "WeaponBeanEntity.h"

/*
TABLE ENT_WEAPONS
ID             INT
ID_TILE        INT
SCRIPT_ANIM    CHAR(20)
SCRIPT_AI      CHAR(20)
*/

class WeaponEntity : public Entity{

public:

    WeaponEntity():Entity(WEAPON_ENT){
        weaponEfects.clear();
    };

    WeaponEntity(uint32_t timestamp):Entity(WEAPON_ENT, timestamp){
        weaponEfects.clear();
    };

    WeaponEntity(WeaponEntity *weaponEntityRef, uint32_t timestamp):Entity(WEAPON_ENT, timestamp){
        Entity::copyTo((Entity *)weaponEntityRef);
        copyWeaponsBean(weaponEntityRef);
    };


    void copyTo(WeaponEntity *weaponEntityRef){
        Entity::copyTo((Entity *)weaponEntityRef);
        copyWeaponsBean(weaponEntityRef);
    };

    void clear(){
        Entity::clear();
        weaponEfects.clear();
    };

    ~WeaponEntity(){
        Entity::clear();
        weaponEfects.clear();
    };

    void addWeaponBeanEntity(WeaponBeanEntity *beam){
        weaponEfects.push_back(beam);
    };

    int getWeaponBeanEntitySize(){return weaponEfects.size();}

    WeaponBeanEntity *getWeaponBeanEntity(int index){
            if ((index >= 0) && (index < weaponEfects.size())){
                return weaponEfects[index];
            }else{
                return NULL;
            }
    };

    void copyWeaponsBean(WeaponEntity *weaponEntityRef){
        weaponEfects.clear();
        for (int i=0; i<weaponEntityRef->getWeaponBeanEntitySize(); i++){
                WeaponBeanEntity *wBE = new WeaponBeanEntity(weaponEntityRef->getWeaponBeanEntity(i),0);
                weaponEfects.push_back(wBE);
        }
    };

private:

    std::vector<WeaponBeanEntity *>weaponEfects;

};

#endif // WEAPONENTITY_H_INCLUDED
