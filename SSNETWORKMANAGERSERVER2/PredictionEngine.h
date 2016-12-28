#ifndef PREDICTIONENGINE_H_INCLUDED
#define PREDICTIONENGINE_H_INCLUDED

#include "TaskManager.h"


class PredictionEngine{

public:

    PredictionEngine(LogEngine *_logger, MemManager *_mem, CollisionEntities *_coll, AnimationEntities *_aEnt, IAEntities *_iAEnt){
        logger = _logger;
        mem = _mem;
        mTask = new TaskManager(_logger,_mem,_coll,_aEnt, _iAEnt);
    }

    ~PredictionEngine(){}
    void processPrediction(long index);
    void processPhoto();

private:

    LogEngine *logger;
    MemManager *mem;
    CollisionEntities *coll;
    AnimationEntities *aEnt;
    IAEntities *iAEnt;
    TaskManager *mTask;

    void createNewPhoto();

};



#endif // PREDICTIONENGINE_H_INCLUDED
