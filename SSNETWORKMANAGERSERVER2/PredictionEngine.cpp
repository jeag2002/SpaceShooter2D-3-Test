#include "PredictionEngine.h"

void PredictionEngine::processPrediction(long index){
    mTask->Run(mem->getEnemy_Lvl_1_Map(),index);
    mTask->Run(mem->getDynElem_Lvl_1_Map(),index);
    mTask->Run(mem->getEnemy_Lvl_2_Map(),index);
    mTask->Run(mem->getDynElem_Lvl_2_Map(),index);
    mTask->Run(mem->getEnemy_Lvl_3_Map(),index);
    mTask->Run(mem->getDynElem_Lvl_3_Map(),index);
    mTask->Run(mem->getRemPlayerMap(),index);

    mem->setTimeStampServer(index);
}

void PredictionEngine::processPhoto(){
    if (mem->getPhotoMap().size() > WORLD_PHOTO_SIZE){
        logger->debug("[PredictionEngine::processPhoto] DELETE PHOTO STEP OF THE SYSTEM [%d]",mem->getMinWorldIndex());
        mem->removeOldWorldPhoto();
    }
    createNewPhoto();
}

void PredictionEngine::createNewPhoto(){

    WorldPhoto *photo = new WorldPhoto();


    std::map<int, DynamicEntity *>enemyOfLevel1 = mem->getEnemy_Lvl_1_Map();
    std::map<int, DynamicEntity *>enemyOfLevel2 = mem->getEnemy_Lvl_2_Map();
    std::map<int, DynamicEntity *>enemyOfLevel3 = mem->getEnemy_Lvl_3_Map();

    std::map<int, DynamicEntity *>DynOfLevel1 = mem->getDynElem_Lvl_1_Map();
    std::map<int, DynamicEntity *>DynOfLevel2 = mem->getDynElem_Lvl_2_Map();
    std::map<int, DynamicEntity *>DynOfLevel3 = mem->getDynElem_Lvl_3_Map();

    std::map<int, DynamicEntity *>RemPlayers = mem->getRemPlayerMap();

    photo->EnemiesMap_lvl_1 = enemyOfLevel1;
    photo->EnemiesMap_lvl_2 = enemyOfLevel2;
    photo->EnemiesMap_lvl_3 = enemyOfLevel3;

    photo->DynElemMap_lvl_1 = DynOfLevel1;
    photo->DynElemMap_lvl_2 = DynOfLevel2;
    photo->DynElemMap_lvl_3 = DynOfLevel3;

    photo->remPlayerMap = RemPlayers;
    mem->addWorldPhotoMap(mem->getTimeStampServer(),photo);

    logger->debug("[PredictionEngine::createNewPhoto] CREATE A NEW PHOTO OF THE SYSTEM [%d]",mem->getTimeStampServer());

}
