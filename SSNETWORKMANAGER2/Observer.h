#ifndef OBSERVER_H_INCLUDED
#define OBSERVER_H_INCLUDED

#include "EventMsg.h"
#include <stdlib.h>

class Observer{

public:

    Observer(){
    };

    ~Observer(){};

    virtual void update(EventMsg *msg, long timeMark)=0;
};



#endif // OBSERVER_H_INCLUDED
