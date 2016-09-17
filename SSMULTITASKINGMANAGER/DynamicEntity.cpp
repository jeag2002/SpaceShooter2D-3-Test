#include "DynamicEntity.h"


int DynamicEntity::randomValues(int min, int max)
{
    int range, result, cutoff;
    if (min >= max)
        return min;
    range = max-min+1;
    cutoff = (RAND_MAX / range) * range;
    do {
        result = rand();
    } while (result >= cutoff);

    return result % range + min;
}




void DynamicEntity::VOnUpdate(unsigned long deltaMs, pthread_t id_t){

    SDL_Delay(deltaMs);

    /*
    if (!qMem->isEmptyMessageOutput()){
        EventMsg *msg = qMem->getEmptyMessageOutput();
        log->debug("[DYNAMICENTITY] ENTITY ID[%d] GET TYPEMSG [%d]",this->idDE,msg->getTypeMsg());
    }
    */
    int _x = randomValues(0,15);
    int _y = randomValues(0,12);
    this->x = float(_x)*64.0f;
    this->y = float(_y)*64.0f;
    log->debug("[DYNAMICENTITY] NEW POSITION OF ENTITY ID[%d] - THREAD[%08x] (x:%f,y:%f)",this->idDE,id_t,this->x,this->y);

}
