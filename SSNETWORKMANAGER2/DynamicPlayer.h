#ifndef DYNAMICPLAYER_H_INCLUDED
#define DYNAMICPLAYER_H_INCLUDED

#include "Observer.h"
#include "LogEngine.h"
#include "NetworkClientUDP.h"



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
    this->mapID = 0;
    this->sessionID = 0;
    this->sendToServer = 0;
    this->locked = false;
}

DynamicPlayer(LogEngine *_log, int _indexPlayer, NetworkClientUDP *_nClient):Observer(){
    this->x = 0.0f;
    this->y = 0.0f;
    this->width = 0.0f;
    this->height = 0.0f;
    this->log = _log;
    this->indexPlayer = _indexPlayer;
    this->actLevel = 0;
    this->mapID = 0;
    this->sessionID = 0;
    this->sendToServer = 0;
    this->locked = false;
    this->nClient = _nClient;
};

DynamicPlayer(DynamicPlayer *refEntity):Observer(){
    this->x = refEntity->getX();
    this->y = refEntity->getY();
    this->width = refEntity->getWidth();
    this->height = refEntity->getHeight();
    this->log = refEntity->getLog();
    this->indexPlayer = refEntity->getIndexPlayer();
    this->locked = refEntity->isLocked();
    this->mapID = 0;
    this->sessionID = 0;
    this->sendToServer = 0;
};

DynamicPlayer(remotePlayerType _rPType):Observer(){
    setDynamicPlayer(_rPType);
};

DynamicPlayer(playerDataType _pDType):Observer(){
    setDynamicPlayer(_pDType);
};


~DynamicPlayer(){
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->indexPlayer = 0;
    this->actLevel = 0;
    this->mapID = 0;
    this->sessionID = 0;
    this->sendToServer = 0;
    this->locked = false;
};

float getX(){return x;}
float getY(){return y;}
float getWidth(){return width;}
float getHeight(){return height;}
int getIndexPlayer(){return indexPlayer;}
int getActLevel(){return actLevel;}
bool isLocked(){return locked;}
int getMapID(){return mapID;}
int getSessionID(){return sessionID;}


void setX(float _x){this->x = _x;}
void setY(float _y){this->y = _y;}
void setWidth(float _width){this->width = _width;}
void setHeight(float _height){this->height = _height;}
void setIndexPlayer(int _indexPlayer){this->indexPlayer = _indexPlayer;}
void setActLevel(int _actLevel){this->actLevel = _actLevel;}
void setLocked(bool _locked){this->locked = _locked;}
void setMapId(int _mapID){this->mapID = _mapID;}
void setSessionID(int _sessionID){this->sessionID = _sessionID;}

void setDynamicPlayer(DynamicPlayer *refEntity){
    this->x = refEntity->getX();
    this->y = refEntity->getY();
    this->width = refEntity->getWidth();
    this->height = refEntity->getHeight();
    this->log = refEntity->getLog();
    this->indexPlayer = refEntity->getIndexPlayer();
    this->actLevel = refEntity->getActLevel();
    this->locked = refEntity->isLocked();
    this->mapID = refEntity->getMapID();
    this->sessionID = refEntity->getSessionID();
}

void setDynamicPlayer(remotePlayerType _rPType){
    this->x = _rPType.x_pos;
    this->y = _rPType.y_pos;
    this->width = float(_rPType.width);
    this->height = float(_rPType.height);
    this->actLevel = _rPType.lvl;
    this->indexPlayer = _rPType.idPlayer;
    this->mapID = _rPType.actMap;
    this->sessionID = _rPType.session;
}

void setDynamicPlayer(playerDataType _pDType){
    this->x = _pDType.x_pos;
    this->y = _pDType.y_pos;
    this->width = _pDType.width;
    this->height = _pDType.heigth;
    this->actLevel = _pDType.lvl;
    this->indexPlayer = _pDType.idPlayer;
    this->mapID = _pDType.actMap;
    this->sessionID = _pDType.session;
}

LogEngine *getLog(){return log;}

//herencia de Observer
/////////////////////////////////////
void update(EventMsg *msg, long timeMark);
/////////////////////////////////////

private:

int mapID;
int sessionID;

int sendToServer;

int actLevel;
float x;
float y;
float width;
float height;

int indexPlayer;
bool locked;

LogEngine *log;
NetworkClientUDP *nClient;

};

#endif // DYNAMICPLAYER_H_INCLUDED
