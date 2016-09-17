#include "DynamicPlayer.h"

void DynamicPlayer::update(EventMsg *msg){

    SDL_Delay(100);

    localActionType lAcType = msg->getLocalActionType();
    movementType mType;
    EventMsg *msgCopy = new EventMsg();

    if (lAcType.idPlayer == this->indexPlayer){
        this->setLocked(true);

        if (lAcType.typeMovement == LEFT){ //LEFT

            this->x = this->x - lAcType._inc;
            mType.idPlayer = this->indexPlayer;
            mType.movementID = MOVEMENT;
            mType.x = this->x;
            mType.y = this->y;
            msgCopy->setMovementType(mType);

        }else if (lAcType.typeMovement == RIGHT){ //RIGHT

            this->x = this->x + lAcType._inc;
            mType.idPlayer = this->indexPlayer;
            mType.movementID = MOVEMENT;
            mType.x = this->x;
            mType.y = this->y;
            msgCopy->setMovementType(mType);

        }else if (lAcType.typeMovement == UP){ //UP

            this->y = this->y - lAcType._inc;
            mType.idPlayer = this->indexPlayer;
            mType.movementID = MOVEMENT;
            mType.x = this->x;
            mType.y = this->y;
            msgCopy->setMovementType(mType);

        }else if (lAcType.typeMovement == DOWN){ //DOWN

            this->y = this->y + lAcType._inc;
            mType.idPlayer = this->indexPlayer;
            mType.movementID = MOVEMENT;
            mType.x = this->x;
            mType.y = this->y;
            msgCopy->setMovementType(mType);
        }

        log->debug("[DYNAMIC PLAYER] ID_PLAYER NEW POSITION [%d] (%f,%f)",this->indexPlayer,this->x,this->y);
        msgCopy->setTypeMsg(TRAMA_COMMAND);
        msg->setMsg(msgCopy);
        nClient->sendMsgToServer(msg);

        this->setLocked(false);
    }
};
