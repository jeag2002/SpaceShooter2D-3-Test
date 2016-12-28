#ifndef IAENTITIES_H_INCLUDED
#define IAENTITIES_H_INCLUDED

#include "MemManager.h"
#include "LogEngine.h"

class IAEntities{

public:
    IAEntities(MemManager *_mem, LogEngine *_log){
        mem = _mem;
        log = _log;
    }

    ~IAEntities(){
    }

    bool isIADynamicElement(DynamicEntity *ent){
        return false;
    }

private:

    MemManager *mem;
    LogEngine *log;
};



#endif // IAENTITIES_H_INCLUDED
