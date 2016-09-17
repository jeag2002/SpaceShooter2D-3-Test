#include "TaskManager.h"


void TaskManager::ProcessEntity(DynamicEntity *dEntity){
    bool isCollision = coll->isCollDynamicElement(dEntity);
    if (!isCollision){
        anim->isAnimDynamicElement(dEntity);
        ia->isIADynamicElement(dEntity);
    }
}


void TaskManager::Run(std::map<int, DynamicEntity *> eLvl){

    bool DONE = false;
    DynamicEntity *dEntity;

    for(auto iterator = eLvl.begin(); iterator != eLvl.end(); iterator++){

               int i = iterator->first;
               dEntity = iterator->second;

               if (dEntity->isEnabled()){

                   dEntity->setBlocked(true);

                   if (dEntity->GetState() == DynamicEntity::UNITIALIZED){
                        dEntity->VOnInit();
                   }

                   if (dEntity->GetState() == DynamicEntity::RUNNING){
                        dEntity->VOnUpdate(100);
                        ProcessEntity(dEntity);
                   }

                   if (dEntity->isDead()){

                       switch(dEntity->GetState()){
                            case DynamicEntity::SUCCEED:
                                dEntity->VOnSuccess();
                            break;

                            case DynamicEntity::FAILED:
                                dEntity->VOnFail();
                            break;

                            case DynamicEntity::ABORTED:
                                dEntity->VOnAbort();
                            break;

                       }
                   }

                   eLvl[i]->setDynamicEntity(dEntity);
                   eLvl[i]->setBlocked(false);
               }

    }// end for
}


void TaskManager::Run(std::vector<DynamicEntity *> eLvl){


    bool DONE = false;
    DynamicEntity *dEntity;

    for(int i=0; i<eLvl.size(); i++){

               dEntity = eLvl[i];
               eLvl[i]->setBlocked(true);

               if (dEntity->GetState() == DynamicEntity::UNITIALIZED){
                    dEntity->VOnInit();
               }

               if (dEntity->GetState() == DynamicEntity::RUNNING){
                    dEntity->VOnUpdate(100);
                    ProcessEntity(dEntity);
               }

               if (dEntity->isDead()){

                   switch(dEntity->GetState()){
                        case DynamicEntity::SUCCEED:
                            dEntity->VOnSuccess();
                        break;

                        case DynamicEntity::FAILED:
                            dEntity->VOnFail();
                        break;

                        case DynamicEntity::ABORTED:
                            dEntity->VOnAbort();
                        break;

                   }
               }

               eLvl[i]->setDynamicEntity(dEntity);
               eLvl[i]->setBlocked(false);
    }// end for
}
