#include "DynamicEntity.h"
#include "UtilsProtocol.h"


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

positionXY  DynamicEntity::processMovement(float x_data, float y_data){

    positionXY  result;

    result.x = x_data;
    result.y = y_data;
    result.order = 0;

    if (!left){

        float x_aux = x_data+2.0f;
        if ((x_aux + float(this->width)) <= 1024){
            result.x = x_aux;
        }else{
            left = true;
            if (!down){
                float y_aux = y_data+2.0f;
                if ((y_aux + float(this->height)) <= 768){
                    result.y = y_aux;
                }else{
                    down = true;
                }
            }else{
                float y_aux = y_data-2.0f;
                if (y_aux  > 0){
                    result.y = y_aux;
                }else{
                    down = false;
                }
            }
        }
    }else{
        float x_aux = x_data-2.0f;
        if (x_aux > 0.0){
            result.x = x_aux;
        }else{
            left = false;
            if (!down){
                float y_aux = y_data+2.0f;
                if ((y_aux + float(this->height)) <= 768){
                    result.y = y_aux;
                }else{
                    down = true;
                }
            }else{
                float y_aux = y_data-2.0f;
                if (y_aux  > 0){
                    result.y = y_aux;
                }else{
                    down = false;
                }
            }
        }
    }

    return result;
}




void DynamicEntity::VOnUpdate(unsigned long deltaMs){


    if ((this->typeId == TYPE_ACTIVE_ELEMENT) || (this->typeId == TYPE_ACTIVEOTHER_ELEMENT)){

        positionXY xy = processMovement(this->x, this->y);
        this->x = xy.x;
        this->y = xy.y;
        this->indexCoord = this->indexCoord+1;

        if (this->typeId == TYPE_ACTIVE_ELEMENT){
            //log->debug("[DYNAMICENTITY::VOUPDATE] POSITION OF ENTITY ENEMY ID[%d] (lvl:%d, x:%f,y:%f)",this->idDE, this->actLevel, this->x,this->y);
        }else if (this->typeId == TYPE_ACTIVEOTHER_ELEMENT){
            //log->debug("[DYNAMICENTITY::VOUPDATE] POSITION OF ENTITY DYNAMIC-ELEM ID[%d] (lvl:%d, x:%f,y:%f)",this->idDE, this->actLevel, this->x,this->y);
        }
    }else{
        //log->debug("[DYNAMICENTITY::VOUPDATE] POSITION OF ENTITY REMOTE-PLAYER ID[%d] (lvl:%d, x:%f,y:%f)",this->idDE, this->actLevel, this->x,this->y);
    }

    /*
    logPackets->debug("[DYNAMICENTITY:SETDYNAMICENTITY:CLIENT] HOME POS INDEXCOORD TIMESTAMP [%d] ENTITY ID:[%d] (ActMap:%d,Session:%d,lvl:%d,x:%f,y:%f)",
                        this->indexCoord,this->idDE,this->actMap,this->actSession,this->actLevel,this->x,this->y);
    */
}
