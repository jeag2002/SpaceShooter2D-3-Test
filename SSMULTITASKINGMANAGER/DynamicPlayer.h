#ifndef DYNAMICPLAYER_H_INCLUDED
#define DYNAMICPLAYER_H_INCLUDED

#include "Observer.h"
#include "LogEngine.h"



class DynamicPlayer : public Observer
{

public:

DynamicPlayer():Observer(){
    this->x = 0.0f;
    this->y = 0.0f;
    this->width = 0.0f;
    this->height = 0.0f;
    this->indexPlayer = 0;
    this->actLevel = 0;
    this->locked = false;
}

DynamicPlayer(LogEngine *_log, int _indexPlayer):Observer(){
    this->x = 0.0f;
    this->y = 0.0f;
    this->width = 0.0f;
    this->height = 0.0f;
    this->log = _log;
    this->indexPlayer = _indexPlayer;
    this->actLevel = 0;
    this->locked = false;
};

DynamicPlayer(DynamicPlayer *refEntity):Observer(){
    this->x = refEntity->getX();
    this->y = refEntity->getY();
    this->width = refEntity->getWidth();
    this->height = refEntity->getHeight();
    this->log = refEntity->getLog();
    this->indexPlayer = refEntity->getIndexPlayer();
    this->locked = refEntity->isLocked();
};

~DynamicPlayer(){
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->indexPlayer = 0;
    this->actLevel = 0;
    this->locked = false;
};

float getX(){return x;}
float getY(){return y;}
float getWidth(){return width;}
float getHeight(){return height;}
int getIndexPlayer(){return indexPlayer;}
int getActLevel(){return actLevel;}
bool isLocked(){return locked;}

void setX(float _x){this->x = _x;}
void setY(float _y){this->y = _y;}
void setWidth(float _width){this->width = _width;}
void setHeight(float _height){this->height = _height;}
void setIndexPlayer(int _indexPlayer){this->indexPlayer = _indexPlayer;}
void setActLevel(int _actLevel){this->actLevel = _actLevel;}
void setLocked(bool _locked){this->locked = _locked;}

void setDynamicPlayer(DynamicPlayer *refEntity){
    this->x = refEntity->getX();
    this->y = refEntity->getY();
    this->width = refEntity->getWidth();
    this->height = refEntity->getHeight();
    this->log = refEntity->getLog();
    this->indexPlayer = refEntity->getIndexPlayer();
    this->actLevel = refEntity->getActLevel();
    this->locked = refEntity->isLocked();
}

LogEngine *getLog(){return log;}

//herencia de Observer
/////////////////////////////////////
void update(EventMsg *msg);
/////////////////////////////////////

private:

float x;
float y;
float width;
float height;

int indexPlayer;
int actLevel;

bool locked;

LogEngine *log;

};

#endif // DYNAMICPLAYER_H_INCLUDED
