#include "DynamicPlayer.h"

void DynamicPlayer::update(EventMsg *msg){

    //SDL_Delay(100);

    localActionType lAcType = msg->getLocalActionType();

    movementType mType;
    EventMsg *msgCopy = new EventMsg();

    if (lAcType.idPlayer == this->indexPlayer){
        this->setLocked(true);

        if (lAcType.typeMovement == LEFT){ //LEFT

            this->x = this->x - lAcType._inc;
            mType.idPlayer = this->indexPlayer;
            mType.movementID = MOVEMENT;
            mType.actMap = this->mapID;
            mType.session = this->sessionID;
            mType.x = this->x;
            mType.y = this->y;
            mType.lvl = this->actLevel;
            mType.width = this->width;
            mType.height = this->height;
            msgCopy->setMovementType(mType);

        }else if (lAcType.typeMovement == RIGHT){ //RIGHT

            this->x = this->x + lAcType._inc;
            mType.idPlayer = this->indexPlayer;
            mType.movementID = MOVEMENT;
            mType.x = this->x;
            mType.y = this->y;
            mType.lvl = this->actLevel;
            mType.width = this->width;
            mType.height = this->height;
            mType.actMap = this->mapID;
            mType.session = this->sessionID;
            msgCopy->setMovementType(mType);

        }else if (lAcType.typeMovement == UP){ //UP

            this->y = this->y - lAcType._inc;
            mType.idPlayer = this->indexPlayer;
            mType.movementID = MOVEMENT;
            mType.x = this->x;
            mType.y = this->y;
            mType.lvl = this->actLevel;
            mType.width = this->width;
            mType.height = this->height;
            mType.actMap = this->mapID;
            mType.session = this->sessionID;
            msgCopy->setMovementType(mType);

        }else if (lAcType.typeMovement == DOWN){ //DOWN

            this->y = this->y + lAcType._inc;
            mType.idPlayer = this->indexPlayer;
            mType.movementID = MOVEMENT;
            mType.x = this->x;
            mType.y = this->y;
            mType.lvl = this->actLevel;
            mType.width = this->width;
            mType.height = this->height;
            mType.actMap = this->mapID;
            mType.session = this->sessionID;
            msgCopy->setMovementType(mType);

        }else if (lAcType.typeMovement == LVLUP){ //LVLUP

            this->actLevel = this->actLevel + 1;
            if (this->actLevel > 3){this->actLevel = 3;}

            mType.idPlayer = this->indexPlayer;
            mType.movementID = MOVEMENT;
            mType.x = this->x;
            mType.y = this->y;
            mType.lvl = this->actLevel;
            mType.width = this->width;
            mType.height = this->height;
            mType.actMap = this->mapID;
            mType.session = this->sessionID;
            msgCopy->setMovementType(mType);


        }else if (lAcType.typeMovement == LVLDOWN){ //LVLDOWN

            this->actLevel = this->actLevel - 1;
            if (this->actLevel < 1){this->actLevel = 1;}

            mType.idPlayer = this->indexPlayer;
            mType.movementID = MOVEMENT;
            mType.x = this->x;
            mType.y = this->y;
            mType.lvl = this->actLevel;
            mType.width = this->width;
            mType.height = this->height;
            mType.actMap = this->mapID;
            mType.session = this->sessionID;
            msgCopy->setMovementType(mType);



        }else if (lAcType.typeMovement == MOUSE){

        }


        log->debug("[DYNAMIC PLAYER] ID_PLAYER NEW POSITION [%d] (lvl:%d, x:%f, y:%f)",this->indexPlayer,this->actLevel,this->x,this->y);
        msgCopy->setTypeMsg(TRAMA_COMMAND);
        msgCopy->setTramaGet(nClient->getActTrama());
        msgCopy->setTramaSend(nClient->getActTrama());
        msgCopy->setMore(NOK);
        nClient->sendMsgToServer(msgCopy);


        this->setLocked(false);
    }
};
