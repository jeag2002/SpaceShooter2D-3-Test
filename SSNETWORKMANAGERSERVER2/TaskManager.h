#ifndef TASKMANAGER_H_INCLUDED
#define TASKMANAGER_H_INCLUDED

#include "CollisionEntities.h"
#include "AnimationEntities.h"
#include "IAEntities.h"

class TaskManager{

public:

TaskManager(LogEngine *_log, MemManager *_mem, CollisionEntities *_coll, AnimationEntities *_anim, IAEntities *_ia){
    mem = _mem;
    log = _log;
    coll = _coll;
    anim = _anim;
    ia = _ia;
}

~TaskManager(){}

void ProcessEntity(DynamicEntity *dEntity);
void Run(std::vector<DynamicEntity *> eLvl, long actIndex);
void Run(std::map<int, DynamicEntity *> eLvl, long actIndex);


private:

MemManager *mem;
LogEngine *log;

CollisionEntities *coll;
AnimationEntities *anim;
IAEntities *ia;

};






#endif // TASKMANAGER_H_INCLUDED
