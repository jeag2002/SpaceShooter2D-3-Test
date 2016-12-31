#include "PredictionEngine.h"

void PredictionEngine::processPrediction(int index){

    logger->debug("[PREDICTIONENGINE:PROCESSPREDICTION::CLIENT] PROCESS ENVIRONTMENT LEVEL [%d]",index);

    if (index == 1){
        mTask->Run(mem->getEnemy_Lvl_1_Map());
        mTask->Run(mem->getDynElem_Lvl_1_Map());
    }else if (index == 2){
        mTask->Run(mem->getEnemy_Lvl_2_Map());
        mTask->Run(mem->getDynElem_Lvl_2_Map());
    }else if (index == 3){
        mTask->Run(mem->getEnemy_Lvl_3_Map());
        mTask->Run(mem->getDynElem_Lvl_3_Map());
    }

    logger->debug("[PREDICTIONENGINE:PROCESSPREDICTION::CLIENT] PROCESS REMOTE PLAYER");
    mTask->Run(mem->getRemPlayerMap());
}


void PredictionEngine::processPredictionIter(){
    while(!getDONE()){
       processPrediction();
       if (!getDONE()){SDL_Delay(750);}
    }
    logger->debug("[PREDICTIONENGINE::PROCESSPREDICTIONITER::CLIENT] CLOSE PREDICTION ITERATOR");

};


void PredictionEngine::processPrediction(){
    mTask->Run(mem->getEnemy_Lvl_1_Map());
    mTask->Run(mem->getDynElem_Lvl_1_Map());
    mTask->Run(mem->getEnemy_Lvl_2_Map());
    mTask->Run(mem->getDynElem_Lvl_2_Map());
    mTask->Run(mem->getEnemy_Lvl_3_Map());
    mTask->Run(mem->getDynElem_Lvl_3_Map());
    mTask->Run(mem->getRemPlayerMap());
}
