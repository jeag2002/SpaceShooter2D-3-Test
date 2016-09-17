#include "QueueManager.h"


void QueueManager::runRemoteData(){
};

void QueueManager::runLocalData(){
    nClock->pause();
    pEngine->processPrediction();
    nClock->unpause();
}

