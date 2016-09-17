#ifndef DYNAMICENTITY_H_INCLUDED
#define DYNAMICENTITY_H_INCLUDED

#include "SDL.h"
#include "Task.h"
#include "QueueManager.h"
#include "LogEngine.h"

class DynamicEntity : public Task
{

public:


    DynamicEntity():Task(){
        this->x = 0.0f;
        this->y = 0.0f;
        this->width = 0.0f;
        this->height = 0.0f;
        this->idDE = 0;
        this->actLevel = 0;
        this->typeEntity = 0;
        this->typeEntityId = 0;
    }

    DynamicEntity(LogEngine *_log, QueueManager *_qMem): Task(DynamicEntity::UNITIALIZED){
        this->x = 0.0f;
        this->y = 0.0f;
        this->width = 0.0f;
        this->height = 0.0f;
        this->qMem = _qMem;
        this->log = _log;
        this->idDE = 0;
        this->actLevel = 0;
        this->typeEntity = 0;
        this->typeEntityId = 0;
    };

    DynamicEntity(DynamicEntity *refEntity, QueueManager *_qMem): Task(DynamicEntity::UNITIALIZED){
        this->x = refEntity->getX();
        this->y = refEntity->getY();
        this->width = refEntity->getWidth();
        this->height = refEntity->getHeight();
        this->qMem = _qMem;
        this->log = refEntity->getLog();
        this->typeEntity = refEntity->getTypeEntity();
        this->typeEntityId = refEntity->getTypeEntityId();
        this->blocked = false;
        this->idDE = 0;
        this->actLevel = 0;
    };

    ~DynamicEntity(){
        this->x = 0;
        this->y = 0;
        this->width = 0;
        this->height = 0;
        this->idDE = 0;
        this->blocked = false;
        this->actLevel = 0;
        this->typeEntity = 0;
        this->typeEntityId = 0;
    };

    float getX(){return x;}
    float getY(){return y;}
    float getWidth(){return width;}
    float getHeight(){return height;}
    bool isBlocked(){return blocked;}
    int getIDDE(){return idDE;}
    int getActLevel(){return actLevel;}
    int getTypeEntity(){return typeEntity;}
    int getTypeEntityId(){return typeEntityId;}

    void setX(float _x){this->x = _x;}
    void setY(float _y){this->y = _y;}
    void setWidth(float _width){this->width = _width;}
    void setHeight(float _height){this->height = _height;}
    void setBlocked(bool _blocked){this->blocked = _blocked;}
    void setIDDE(int _idDE){this->idDE = _idDE;}
    void setActLevel(int _actLevel){this->actLevel = _actLevel;}
    void setTypeEntity(int _typeEntity){this->typeEntity = _typeEntity;}
    void setTypeEntityId(int _typeEntityId){this->typeEntityId = _typeEntityId;}


    void setDynamicEntity(DynamicEntity *refEntity){
        this->x = refEntity->getX();
        this->y = refEntity->getY();
        this->width = refEntity->getWidth();
        this->height = refEntity->getHeight();
        this->log = refEntity->getLog();
        this->idDE = refEntity->getIDDE();
        this->actLevel = refEntity->getActLevel();
        this->typeEntity = refEntity->getTypeEntity();
        this->typeEntityId = refEntity->getTypeEntityId();
    }

    LogEngine *getLog(){return log;}


    //herencia de Task
    /////////////////////////////////////
    void VOnInit(){
         setState(DynamicEntity::RUNNING);
    };

    void VOnUpdate(unsigned long deltaMs, pthread_t id_t);
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
    int idDE;
    int actLevel;

    int typeEntity;
    int typeEntityId;

    int randomValues(int min, int max);

    QueueManager *qMem;
    LogEngine *log;


};

#endif // DYNAMICENTITY_H_INCLUDED
