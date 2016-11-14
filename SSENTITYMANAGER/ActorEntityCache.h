#ifndef ACTORENTITYCACHE_H_INCLUDED
#define ACTORENTITYCACHE_H_INCLUDED

#include "MRUCacheTemplate.h"
#include "ActorEntity.h"

class ActorEntityCache : public MRUCacheTemplate<int, ActorEntity*>
{
public:
    ActorEntityCache(int iMaxLength) : MRUCacheTemplate<int, ActorEntity*>(iMaxLength) { }
protected:

    virtual void HandleItemRelease(int key, ActorEntity* value)
    {
    }

    virtual ActorEntity* HandleNonExistingKeyFetch(int key)
    {
        return NULL;
    }
};

#endif // ACTORENTITYCACHE_H_INCLUDED
