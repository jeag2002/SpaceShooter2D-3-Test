#ifndef DYNAMICENTITY_H_INCLUDED
#define DYNAMICENTITY_H_INCLUDED

#include "SDL.h"
#include "Task.h"
#include "LogEngine.h"
#include "Constants.h"

#define REGRESION_DATA 10

class DynamicEntity : public Task
{

public:


    DynamicEntity():Task(){
        this->x = 0.0f;
        this->y = 0.0f;
        this->width = 64.0f;
        this->height = 64.0f;
        this->idDE = 0;
        this->actLevel = 0;
        this->blocked = false;
        this->enabled = false;
        this->left = false;
        this->down = false;
        this->typeId = 0;
        this->typeEntityId = 0;
        this->actMap = 1;
        this->actSession = 1;
        this->num_data = 0;
        this->indexCoord = 0;

    }

    DynamicEntity(LogEngine *_log): Task(DynamicEntity::UNITIALIZED){
        this->x = 0.0f;
        this->y = 0.0f;
        this->width = 64.0f;
        this->height = 64.0f;
        this->log = _log;

        logPackets = new LogEngine();
        logPackets->setOwnFile("DYNAMICENTITYCLIENT.log");
        logPackets->deleteLogFile();
        logPackets->startUp(1,0);


        this->idDE = 0;
        this->actLevel = 0;
        this->blocked = false;
        this->enabled = false;
        this->left = false;
        this->down = false;

        this->typeId = 0;
        this->typeEntityId = 0;
        this->actMap = 1;
        this->actSession = 1;
        this->num_data = 0;
        this->indexCoord = 0;

    };

    DynamicEntity(DynamicEntity *refEntity): Task(DynamicEntity::UNITIALIZED){
        this->x = refEntity->getX();
        this->y = refEntity->getY();
        this->width = refEntity->getWidth();
        this->height = refEntity->getHeight();
        this->log = refEntity->getLog();

        this->blocked = false;
        this->enabled = false;
        this->left = false;
        this->down = false;

        this->idDE = 0;
        this->actLevel = 0;
        this->typeId = 0;
        this->typeEntityId = 0;
        this->actMap = 1;
        this->actSession = 1;
        this->num_data = 0;
        this->indexCoord = 0;
    };

    DynamicEntity(remotePlayerType _rPType): Task(DynamicEntity::UNITIALIZED){
        this->width = float(_rPType.width);
        this->height = float(_rPType.height);
        this->actLevel = _rPType.lvl;
        this->actMap = _rPType.actMap;
        this->actSession = _rPType.session;
        this->typeId = _rPType.typeID;
        this->idDE = _rPType.idPlayer;
        this->x = _rPType.x_pos;
        this->y = _rPType.y_pos;


    };


    DynamicEntity(playerDataType _pDType): Task(DynamicEntity::UNITIALIZED){
        setDynamicEntity(_pDType);
    };


    ~DynamicEntity(){
        this->x = 0;
        this->y = 0;
        this->width = 0;
        this->height = 0;
        this->idDE = 0;
        this->blocked = false;
        this->enabled = false;
        this->left = false;
        this->down = false;

        delete logPackets;

        this->indexCoord = 0;
        this->actLevel = 0;
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

    void setDynamicEntity(remotePlayerType _rPType,int getIndex){

        if (getIndex > this->indexCoord){

            this->width = float(_rPType.width);
            this->height = float(_rPType.height);
            this->actLevel = _rPType.lvl;
            this->actMap = _rPType.actMap;
            this->actSession = _rPType.session;
            this->typeId = _rPType.typeID;
            this->idDE = _rPType.idPlayer;
            this->x = _rPType.x_pos;
            this->y = _rPType.y_pos;



            log->debug("[DYNAMICENTITY::SETDYNAMICENTITY] SET REMOTE DATA FOR ENTITY ID:[%d] (ActMap:%d,Session:%d,lvl:%d,x:%f,y:%f,width:%f,height:%f)",
                          this->idDE,this->actMap,this->actSession,this->actLevel,this->x,this->y,this->width,this->height);

            logPackets->debug("[DYNAMICENTITY:SETDYNAMICENTITY:CLIENT] REMOTE TIMESTAMP:(%d) INDEXCOORD TIMESTAMP (%d) ENTITY ID:[%d] (ActMap:%d,Session:%d,lvl:%d,x:%f,y:%f)",
                              getIndex, this->indexCoord, this->idDE,this->actMap,this->actSession,this->actLevel,this->x,this->y);

            this->indexCoord = getIndex;
        }


    }

    void setDynamicEntity(playerDataType _pDType){
        this->x = _pDType.x_pos;
        this->y = _pDType.y_pos;
        this->width = _pDType.width;
        this->height = _pDType.heigth;
        this->actLevel = _pDType.lvl;
    }

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
    float width;
    float height;

    bool blocked;
    bool enabled;

    int idDE;
    int actLevel;

    int typeId;
    int typeEntityId;

    int actMap;
    int actSession;

    int randomValues(int min, int max);

    positionXY processMovement(float x_data, float y_data);

    LogEngine *log;
    LogEngine *logPackets;

    int indexCoord;

    std::deque<positionXY> regresionLine;
    int num_data;
    bool left;
    bool down;


};

#endif // DYNAMICENTITY_H_INCLUDED
