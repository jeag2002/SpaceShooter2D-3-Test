#ifndef ACTORENTITYLRU_H_INCLUDED
#define ACTORENTITYLRU_H_INCLUDED

#include "LRUCache.h"
#include "ActorEntity.h"

class ActorEntityLRU: public LRUCache<int, ActorEntity *>{

public:

    ActorEntityLRU(int capacity){
    }

    void

    ~ActorEntityLRU(){};

private:


};

#endif // ACTORENTITYLRU_H_INCLUDED
