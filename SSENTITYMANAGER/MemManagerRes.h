#ifndef MEMMANAGERRES_H_INCLUDED
#define MEMMANAGERRES_H_INCLUDED

#include "Stdafx.h"

//RECURSOS
#include "ImageRes.h"       //--> fuente imagenes
#include "ScriptRes.h"      //--> script lua
#include "SoundRes.h"       //--> sonidos
#include "StateRes.h"       //--> estados
#include "TiffRes.h"        //--> fuentes de sonido
#include "ParticleRes.h"    //--> particulas
#include "LightRes.h"       //--> luces
#include "ShaderRes.h"      //--> shader

//ENTIDADES.
#include "TileEntity.h"     //--> Tiles
#include "MeshEntity.h"     //--> Mesh
#include "ActorEntity.h"    //--> Actor (Entity)
#include "BlockEntity.h"    //--> Block
#include "WeaponEntity.h"   //--> Weapon
#include "ItemEntity.h"     //--> Item
#include "ExitEntity.h"     //--> Exit

#include "LRUCache.h"

class MemManagerRes{

public:

    MemManagerRes(){
        actorEntityCache = new LRUCache<int, ActorEntity *>((unsigned int)20);
    };

    ~MemManagerRes(){
        delete actorEntityCache;
    };

    void setActorEntity(int key, ActorEntity *data){
        actorEntityCache->put(key,data);
    }

    ActorEntity *getActorEntity(int key){
        return actorEntityCache->get(key);
    }

    long getActorEntityCapacity(){
        return actorEntityCache->capacity();
    }


private:
    LRUCache<int, ActorEntity *> *actorEntityCache;


};


#endif // MEMMANAGERRES_H_INCLUDED
