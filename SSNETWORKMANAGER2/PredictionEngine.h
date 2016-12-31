#ifndef PREDICTIONENGINE_H_INCLUDED
#define PREDICTIONENGINE_H_INCLUDED

#include "TaskManager.h"


class PredictionEngine{

public:

    PredictionEngine(LogEngine *_logger, MemManager *_mem, CollisionEntities *_coll, AnimationEntities *_aEnt, IAEntities *_iAEnt){
        logger = _logger;
        mem = _mem;
        DONE = false;
        mTask = new TaskManager(_logger,_mem,_coll,_aEnt, _iAEnt);
    }

    ~PredictionEngine(){}
    void processPrediction(int level);
    void processPrediction();
    void processPredictionIter();

    bool getDONE(){return DONE;}
    void setDONE(bool _DONE){DONE = _DONE;}

private:

    LogEngine *logger;
    MemManager *mem;
    CollisionEntities *coll;
    AnimationEntities *aEnt;
    IAEntities *iAEnt;
    TaskManager *mTask;
    bool DONE;

};



#endif // PREDICTIONENGINE_H_INCLUDED
