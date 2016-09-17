#include "DynamicPlayer.h"

void DynamicPlayer::update(EventMsg *msg){

    SDL_Delay(100);

    if (msg->getTO() == this->indexPlayer){
        this->setLocked(true);
        float value = msg->getValue();
        if (msg->getTypeMsg() == 1){ //LEFT
            this->x = this->x - value;
        }else if (msg->getTypeMsg() == 2){ //RIGHT
            this->x = this->x + value;
        }else if (msg->getTypeMsg() == 3){ //UP
            this->y = this->y - value;
        }else if (msg->getTypeMsg() == 4){ //DOWN
            this->y = this->y + value;
        }
        log->debug("[DYNAMIC PLAYER] ID_PLAYER NEW POSITION [%d] (%f,%f)",this->indexPlayer,this->x,this->y);
        this->setLocked(false);
    }
};
