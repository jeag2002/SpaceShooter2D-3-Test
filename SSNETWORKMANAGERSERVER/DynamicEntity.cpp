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




void DynamicEntity::VOnUpdate(unsigned long deltaMs){

    //SDL_Delay(deltaMs);

    /*
    if (!qMem->isEmptyMessageOutput()){
        EventMsg *msg = qMem->getEmptyMessageOutput();
        log->debug("[DYNAMICENTITY] ENTITY ID[%d] GET TYPEMSG [%d]",this->idDE,msg->getTypeMsg());
    }
    */

    if (this->typeId != TYPE_REM_PLAYER_ELEMENT){
        int _x = randomValues(0,15);
        int _y = randomValues(0,12);
        this->x = float(_x)*64.0f;
        this->y = float(_y)*64.0f;
        if (this->typeId == TYPE_ACTIVE_ELEMENT){
            log->debug("[DYNAMICENTITY::VONUPDATE] NEW POSITION MAP[%d] SESSION[%d] ENEMY ID:[%d] (lvl:%d,x:%f,y:%f)", this->actMap, this->actSession, this->idDE,this->actLevel,this->x,this->y);
        }else if (this->typeId == TYPE_ACTIVEOTHER_ELEMENT){
            log->debug("[DYNAMICENTITY::VONUPDATE] NEW POSITION MAP[%d] SESSION[%d] ACTIVE ELEMENTS ID:[%d] (lvl:%d,x:%f,y:%f)", this->actMap, this->actSession, this->idDE,this->actLevel,this->x,this->y);
        }
    }else{
        log->debug("[DYNAMICENTITY::VONUPDATE] POSITION REMOTE PLAYER ID:[%d] (lvl:%d,x:%f,y:%f)",this->idDE,this->actLevel,this->x,this->y);
    }

}
