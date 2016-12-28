#ifndef COLLISIONENTITIES_H_INCLUDED
#define COLLISIONENTITIES_H_INCLUDED

#include "MemManager.h"
#include "LogEngine.h"

class CollisionEntities{

public:
    CollisionEntities(MemManager *_mem, LogEngine *_log){
        mem = _mem;
        logger = _log;
    }

    ~CollisionEntities(){}

    bool isCollDynamicElement(DynamicEntity *ent);

private:

    MemManager *mem;
    LogEngine *logger;

};


#endif // COLLISIONENTITIES_H_INCLUDED
