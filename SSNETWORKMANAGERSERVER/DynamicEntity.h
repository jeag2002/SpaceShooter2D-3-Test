#ifndef DYNAMICENTITY_H_INCLUDED
#define DYNAMICENTITY_H_INCLUDED

#include "SDL.h"
#include "Task.h"
#include "LogEngine.h"
#include "Constants.h"

#define REGRESION_DATA 4

class DynamicEntity : public Task
{

public:

    DynamicEntity():Task(){
        this->x = 0.0f;
        this->y = 0.0f;
        this->width = 64;
        this->height = 64;

        this->idDE = 0;
        this->actLevel = 0;
        this->typeId = 0;
        this->typeEntityId = 0;
        this->actMap = 1;
        this->actSession = 1;

        this->blocked = false;
        this->enabled = false;

    }

    DynamicEntity(LogEngine *_log): Task(DynamicEntity::UNITIALIZED){
        this->x = 0.0f;
        this->y = 0.0f;
        this->width = 64;
        this->height = 64;
        this->log = _log;
        this->blocked = false;
        this->enabled = false;

        this->idDE = 0;
        this->actLevel = 0;
        this->typeId = 0;
        this->typeEntityId = 0;
        this->actMap = 1;
        this->actSession = 1;

    };

    DynamicEntity(DynamicEntity *refEntity): Task(DynamicEntity::UNITIALIZED){
        this->x = refEntity->getX();
        this->y = refEntity->getY();
        this->width = refEntity->getWidth();
        this->height = refEntity->getHeight();
        this->log = refEntity->getLog();
        this->blocked = false;
        this->enabled = false;

        this->idDE = 0;
        this->actLevel = 0;
        this->actMap = 1;
        this->actSession = 1;

        this->typeId = refEntity->getTypeId();
        this->typeEntityId = refEntity->getTypeEntityId();
    };

    DynamicEntity(remotePlayerType _rPType): Task(DynamicEntity::UNITIALIZED){
    };

    DynamicEntity(playerDataType _pDType): Task(DynamicEntity::UNITIALIZED){
    };


    ~DynamicEntity(){
        this->x = 0;
        this->y = 0;
        this->width = 0;
        this->height = 0;
        this->idDE = 0;
        this->blocked = false;
        this->enabled = false;
        this->actLevel = 0;
        this->typeId = 0;
        this->typeEntityId = 0;
        this->actMap = 1;
        this->actSession = 1;
    };

    float getX(){return x;}
    float getY(){return y;}
    float getWidth(){return width;}
    float getHeight(){return height;}

    bool isBlocked(){return blocked;}
    bool isEnabled(){return enabled;}

    int getIDDE(){return idDE;}
    int getActLevel(){return actLevel;}

    int getTypeId(){return typeId;}
    int getTypeEntityId(){return typeEntityId;}

    int getActMap(){return actMap;}
    int getActSession(){return actSession;}


    void setX(float _x){this->x = _x;}
    void setY(float _y){this->y = _y;}
    void setWidth(float _width){this->width = _width;}
    void setHeight(float _height){this->height = _height;}

    void setBlocked(bool _blocked){this->blocked = _blocked;}
    void setEnabled(bool _enabled){this->enabled = _enabled;}

    void setIDDE(int _idDE){this->idDE = _idDE;}
    void setActLevel(int _actLevel){this->actLevel = _actLevel;}

    void setTypeId(int _typeId){this->typeId = _typeId;}
    void setTypeEntityId(int _typeEntityId){this->typeEntityId = _typeEntityId;}

    void setActMap(int _actMap){this->actMap = _actMap;}
    void setActSession(int _actSession){this->actSession = _actSession;}

    void setDynamicEntity(DynamicEntity *refEntity){
        this->x = refEntity->getX();
        this->y = refEntity->getY();
        this->width = refEntity->getWidth();
        this->height = refEntity->getHeight();
        this->log = refEntity->getLog();
        this->idDE = refEntity->getIDDE();
        this->actLevel = refEntity->getActLevel();
        this->typeId = refEntity->getTypeId();
        this->typeEntityId = refEntity->getTypeEntityId();
        this->blocked = refEntity->isBlocked();
        this->enabled = refEntity->isEnabled();
        this->actMap = refEntity->getActMap();
        this->actSession = refEntity->getActSession();
    }

    void setDynamicEntity(remotePlayerType _rPType){
        this->x = _rPType.x_pos;
        this->y = _rPType.y_pos;
        this->width = _rPType.width;
        this->height = _rPType.height;
        this->actLevel = _rPType.lvl;
        this->actMap = _rPType.actMap;
        this->actSession = _rPType.session;
        this->typeId = _rPType.typeID;
        this->idDE = _rPType.idPlayer;
    }

    void setDynamicEntity(playerDataType _pDType){
        this->actLevel = _pDType.lvl;
        this->x = _pDType.x_pos;
        this->y = _pDType.y_pos;
        this->width = _pDType.width;
        this->height = _pDType.heigth;
    }

    void setRemoteMovement(movementType _mType){
        this->x = _mType.x;
        this->y = _mType.y;
        this->width = _mType.width;
        this->height = _mType.height;
        this->actLevel = _mType.lvl;
        this->actMap = _mType.actMap;
        this->actSession = _mType.session;
        log->debug("[DynamicEntity::setRemoteMovement] SET REMOTE PLAYER ID:[%d]-MAP[%d]-SESSION[%d] NEW SITUATION lvl:[%d] x:[%f] y:[%f] width:[%d] height:[%d]",
                   idDE,
                   actMap,
                   actSession,
                   actLevel,x,y,width,height);
    }

    void setRemoteShot(shotType _sType){
        log->debug("[DynamicEntity::setRemoteShot] SET REMOTE PLAYER ID:[%d] SHOT AMMO:[%d]",idDE,_sType.ammo);
    }

    void setRemoteChangeWpn(changeWeaponType _cWType){
        log->debug("[DynamicEntity::setRemoteChangeWpn] SET REMOTE PLAYER ID:[%d] CHGWPN OLD_WPN_ID[%d] NEW_WPN_ID[%d]",idDE,_cWType.oldWeaponId,_cWType.newWeaponId);
    }

    void setRemoteExit(exitType _eType){
        log->debug("[DynamicEntity::setRemoteExit] SET REMOTE PLAYER ID:[%d] MAP:[%d] SESSION:[%d] (LEVEL:%d X:%f Y:%f) REASON:[%d]",idDE, _eType.actMap, _eType.session, _eType.level, _eType.x, _eType.y, _eType.reason);
    }


    remotePlayerType getDynamicEntityRPT(){
        remotePlayerType rPType;

        //rPType.typeTramaID = TYPE_SERVER_DATA_ID;
        rPType.typeTramaID = TYPE_ACTIVE_ELEMENT;
        rPType.typeID = this->getTypeId();
        rPType.entityID = this->getTypeEntityId();
        rPType.actMap = this->getActMap();
        rPType.session = this->getActSession();
        rPType.idPlayer = this->getIDDE();
        rPType.idParPlayer = 0;
        rPType.lvl = this->getActLevel();
        rPType.x_pos = this->getX();
        rPType.y_pos = this->getY();
        rPType.width = int(this->getWidth());
        rPType.height = int(this->getHeight());
        rPType.life = 1;
        rPType.live = 999;
        rPType.shd = 100;
        rPType.act_wpn = 1;
        rPType.wpn_1 = 1;
        rPType.ammo_wpn_1 = 100;
        rPType.wpn_2 = 0;
        rPType.ammo_wpn_2 = 0;
        rPType.wpn_3 = 0;
        rPType.ammo_wpn_3 = 0;
        rPType.wpn_4 = 0;
        rPType.ammo_wpn_4 = 0;
        rPType.item_1 = 0;
        rPType.item_1_val = 0;
        rPType.item_2 = 0;
        rPType.item_2_val = 0;
        rPType.item_3 = 0;
        rPType.item_3_val = 0;
        rPType.item_4 = 0;
        rPType.item_4_val = 0;
        rPType.score = 20;
        rPType.die = 0;
        rPType.animIndex = 1;
        if (this->enabled){rPType.enabled = 1;}
        else{rPType.enabled = 0;}

        log->debug("[DynamicEntity::setRemoteExit] SEND REMOTE DATA ID:[%d] MAP:[%d] SESSION [%d] (lvl:%d x:%f y:%f width:%d height:%d) enabled? [%d]",
                   rPType.idPlayer, rPType.actMap, rPType.session, rPType.lvl, rPType.x_pos, rPType.y_pos, rPType.width, rPType.height, rPType.enabled);

        return rPType;
    };

    playerDataType getDynamicEntityPDT(){
        playerDataType pDType;
        return pDType;
    };

    LogEngine *getLog(){return log;}


    //herencia de Task
    /////////////////////////////////////
    void VOnInit(){
         setState(DynamicEntity::RUNNING);
    };

    void VOnUpdate(unsigned long deltaMs);
    void VOnSuccess(){};
    void VOnFail(){};
    void VOnAbort(){};
    /////////////////////////////////////

private:

    float x;
    float y;
    int width;
    int height;

    bool blocked;
    bool enabled;

    int idDE;
    int actLevel;
    int typeId;
    int typeEntityId;

    int actMap;
    int actSession;

    int randomValues(int min, int max);

    LogEngine *log;

    std::queue<positionXY> regresionLine;



};

#endif // DYNAMICENTITY_H_INCLUDED
