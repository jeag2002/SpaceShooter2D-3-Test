#ifndef WEAPONBEANENTITY_H_INCLUDED
#define WEAPONBEANENTITY_H_INCLUDED

#include "Stdafx.h"
#include "Entity.h"
#include "CoreString.h"

/*
TABLE ENT_WEAPONS_BEAM
ID              INT
ID_PARTICLE     INT
ID_TILE         INT
DAMAGE          INT
SCRIPT_ANIM     CHAR(20)
SCRIPT_AI       CHAR(20)        //==>envia una señal a un estimulo programado
*/


class WeaponBeanEntity: public Entity{

public:

    WeaponBeanEntity():Entity(WEAPON_BEAM_ENT){
        Entity::clear();
        this->idparticle = 0;
        this->damage = 0;
    };

    WeaponBeanEntity(uint32_t timestamp):Entity(WEAPON_BEAM_ENT, timestamp){
        Entity::clear();
        this->idparticle = 0;
        this->damage = 0;
    };

    WeaponBeanEntity(WeaponBeanEntity *weaponBeanRef, uint32_t timestamp):Entity(WEAPON_BEAM_ENT, timestamp){
        Entity::copyTo((Entity *)weaponBeanRef);
        this->idparticle = weaponBeanRef->getIdParticle();
        this->damage = weaponBeanRef->getIdDamage();
    };

    void clear(){
        Entity::clear();
        this->idparticle = 0;
        this->damage = 0;
    };

    ~WeaponBeanEntity(){
        Entity::clear();
        this->idparticle = 0;
        this->damage = 0;
    };

    uint32_t getIdParticle(){return this->idparticle;}
    void setIdParticle(uint32_t _idparticle){this->idparticle = _idparticle;}

    uint32_t getIdDamage(){return this->damage;}
    void setIdDamage(uint32_t _damage){this->damage = _damage;}

private:

    uint32_t idparticle;
    uint32_t damage;

};

#endif // WEAPONBEANENTITY_H_INCLUDED
