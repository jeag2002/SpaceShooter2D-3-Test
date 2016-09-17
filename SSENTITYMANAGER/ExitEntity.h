#ifndef EXITENTITY_H_INCLUDED
#define EXITENTITY_H_INCLUDED

#include "Stdafx.h"
#include "Entity.h"
#include "CoreString.h"

/*
TABLE ENT_EXIT
ID              INT
ID_TILE         INT         //ID_TILE asociado (2D)
ID_MESH         INT         //ID_MESH asociado (3D)
SCRIPT_ANIM     CHAR(20)
SCRIPT_AI       CHAR(20)
*/

class ExitEntity : public Entity{

public:

ExitEntity():Entity(EXIT_ENT){};
ExitEntity(uint32_t timestamp):Entity(EXIT_ENT, timestamp){};
ExitEntity(ExitEntity *exitRef, uint32_t timestamp):Entity(EXIT_ENT, timestamp){Entity::copyTo((Entity *)exitRef);};
void clear(){Entity::clear();};
~ExitEntity(){Entity::clear();};

};
#endif // EXITENTITY_H_INCLUDED
