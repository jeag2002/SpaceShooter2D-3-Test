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

    if (this->typeId != TYPE_REM_PLAYER_ELEMENT){

        bool DONE = false;

        if (!left){

            float x_aux = this->x+2.0f;
            if ((x_aux + float(this->width)) <= 1024){
                this->x = x_aux;
            }else{
                left = true;

                if (!down){
                    float y_aux = this->y+2.0f;
                    if ((y_aux + float(this->height)) <= 768){
                        this->y = y_aux;
                    }else{
                        down = true;
                    }
                }else{
                    float y_aux = this->y-2.0f;
                    if (y_aux  > 0){
                        this->y = y_aux;
                    }else{
                        down = false;
                    }
                }

            }
        }else{
            float x_aux = this->x-2.0f;
            if (x_aux > 0.0){
                this->x = x_aux;
            }else{
                left = false;

                if (!down){
                    float y_aux = this->y+2.0f;
                    if ((y_aux + float(this->height)) <= 768){
                        this->y = y_aux;
                    }else{
                        down = true;
                    }
                }else{
                    float y_aux = this->y-2.0f;
                    if (y_aux  > 0){
                        this->y = y_aux;
                    }else{
                        down = false;
                    }
                }
            }
        }

        if (this->typeId == TYPE_ACTIVE_ELEMENT){
            log->debug("[DYNAMICENTITY::VONUPDATE] NEW POSITION MAP[%d] SESSION[%d] ENEMY ID:[%d] (lvl:%d,x:%f,y:%f)", this->actMap, this->actSession, this->idDE,this->actLevel,this->x,this->y);
        }else if (this->typeId == TYPE_ACTIVEOTHER_ELEMENT){
            log->debug("[DYNAMICENTITY::VONUPDATE] NEW POSITION MAP[%d] SESSION[%d] ACTIVE ELEMENTS ID:[%d] (lvl:%d,x:%f,y:%f)", this->actMap, this->actSession, this->idDE,this->actLevel,this->x,this->y);
        }

    }else{
        log->debug("[DYNAMICENTITY::VONUPDATE] POSITION REMOTE PLAYER ID:[%d] (lvl:%d,x:%f,y:%f)",this->idDE,this->actLevel,this->x,this->y);
    }

    logPackets->debug("[DYNAMICENTITY:SETDYNAMICENTITY:CLIENT] HOME POS ENTITY ID:[%d] (ActMap:%d,Session:%d,lvl:%d,x:%f,y:%f)",
                        this->idDE,this->actMap,this->actSession,this->actLevel,this->x,this->y);
}
