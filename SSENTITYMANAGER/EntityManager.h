#ifndef ENTITYMANAGER_H_INCLUDED
#define ENTITYMANAGER_H_INCLUDED

#include "Stdafx.h"
#include "DBConnection.h"
#include "MemManagerRes.h"
#include "ProfileEngine.h"

class EntityManager{

public:

    EntityManager(DBConnection *_dbConn, MemManagerRes *_mem, LogEngine *_log, ProfileEngine *_pEngine){
        dbConn = _dbConn;
        mem = _mem;
        log = _log;
        pEngine = _pEngine;
    }

    Entity *getEntity(int key);

private:

    DBConnection *dbConn;
    MemManagerRes *mem;
    LogEngine *log;
    ProfileEngine *pEngine;

    ActorEntity *getActorEntity(int key);

};



#endif // ENTITYMANAGER_H_INCLUDED
