#include "PredictionEngine.h"

void PredictionEngine::processPrediction(){

    while(true){
        mTask->Run(mem->getEnemy_Lvl_1_Map());
        mTask->Run(mem->getDynElem_Lvl_1_Map());
        mTask->Run(mem->getEnemy_Lvl_2_Map());
        mTask->Run(mem->getDynElem_Lvl_2_Map());
        mTask->Run(mem->getEnemy_Lvl_3_Map());
        mTask->Run(mem->getDynElem_Lvl_3_Map());
        mTask->Run(mem->getRemPlayerMap());
    }
}
