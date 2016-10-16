#ifndef SUBJECT_H_INCLUDED
#define SUBJECT_H_INCLUDED

//class observable. distribuye los mensajes del thread principal a los demas threads.
//investigar si es mas interesante canalizar toda la info por aquí, o utilizar esta
//clase para los eventos locales; y una remote queue para los eventos remotos


#include "EventMsg.h"
#include <vector>
#include "Observer.h"
//#include "DynamicEntity.h"

class Observer;

class Subject{

private:

    EventMsg *msg;
    std::vector<Observer *>views;

public:

    Subject(){
        msg = new EventMsg();
    }

    ~Subject(){
        views.clear();
        delete msg;
    }

    void attachObserver(Observer *_entity){
        views.push_back(_entity);
    }

    void setObserver(int index, Observer *_entity){
        views[index] = _entity;
    }

    Observer *getObserver(int i){return views[i];}



    void setMsg(EventMsg *_remMsg){
        msg->setMsg(_remMsg);
    }

    EventMsg *getMsg(){
        return msg;
    }

    void notify(){
        for(int i=0; i<views.size(); i++){
           views[i]->update(msg);
        }
    }

};

#endif // SUBJECT_H_INCLUDED
