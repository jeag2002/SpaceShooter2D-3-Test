#include "PredictionEngine.h"

void PredictionEngine::processPrediction(){
    //if (mem->getRoofIndex() == 1){
    mTask->Run(mem->getEnemy_Lvl_1_Map());
    mTask->Run(mem->getDynElem_Lvl_1_Map());
    //}else if (mem->getRoofIndex() == 2){
    mTask->Run(mem->getEnemy_Lvl_2_Map());
    mTask->Run(mem->getDynElem_Lvl_2_Map());
    //}else if (mem->getRoofIndex() == 3){
    mTask->Run(mem->getEnemy_Lvl_3_Map());
    mTask->Run(mem->getDynElem_Lvl_3_Map());
    //}
    mTask->Run(mem->getRemPlayerMap());
}
