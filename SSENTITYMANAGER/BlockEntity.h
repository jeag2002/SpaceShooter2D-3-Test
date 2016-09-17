#ifndef BLOCKENTITY_H_INCLUDED
#define BLOCKENTITY_H_INCLUDED


#include "Stdafx.h"
#include "Entity.h"
#include "CoreString.h"


/*
TABLE ENT_BLOCK
ID              INT
ID_TILE         INT         //ID_TILE asociado (2D)
ID_MESH         INT         //ID_MESH asociado (3D)
SCRIPT_ANIM     CHAR(20)
SCRIPT_AI       CHAR(20)
*/

class BlockEntity : public Entity{

public:

BlockEntity():Entity(BLOCK_ENT){};
BlockEntity(uint32_t timestamp):Entity(BLOCK_ENT, timestamp){};
BlockEntity(BlockEntity *exitRef, uint32_t timestamp):Entity(BLOCK_ENT, timestamp){Entity::copyTo((Entity *)exitRef);};
void clear(){Entity::clear();};
~BlockEntity(){Entity::clear();};

};

#endif // BLOCKENTITY_H_INCLUDED
