#ifndef ANIMATIONENTITIES_H_INCLUDED
#define ANIMATIONENTITIES_H_INCLUDED

#include "MemManager.h"
#include "LogEngine.h"

class AnimationEntities{

public:
    AnimationEntities(MemManager *_mem, LogEngine *_log){
        mem = _mem;
        log = _log;
    }

    ~AnimationEntities(){
    }

    bool isAnimDynamicElement(DynamicEntity *ent){
        return false;
    }

private:

    LogEngine *log;
    MemManager *mem;

};




#endif // ANIMATIONENTITIES_H_INCLUDED
