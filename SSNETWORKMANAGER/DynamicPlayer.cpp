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

        this->sendToServer++;

        if (sendToServer==10){

            int indexTramaSend = nClient->getIndexTramaSend();
            indexTramaSend++;
            nClient->setIndexTramaSend(indexTramaSend);


            msgCopy->setTypeMsg(TRAMA_COMMAND);
            msgCopy->setTramaGet(nClient->getIndexTramaGet());
            msgCopy->setTramaSend(nClient->getIndexTramaSend());
            msgCopy->setMore(NOK);
            msgCopy->setNumTrazas(1);
            msgCopy->setPacketUPD(nClient->getRemotePacket());

            log->debug("[DynamicPlayer::update] SENDTOSERVER ID_PLAYER[%d] TYPE_PACKET[%d] TYPE_MOVEMENT[%d] TRAMASEND[%d] TRAMAGET[%d] ",
                       this->indexPlayer,
                       msgCopy->getTypeMsg(),
                       msgCopy->getMovementType().movementID,
                       msgCopy->getTramaSend(),
                       msgCopy->getTramaGet()
                       );

            log->debug("[DynamicPlayer::update DATA] ID_PLAYER NEW POSITION [%d] (lvl:%d, x:%f, y:%f) SENT TO SERVER",this->indexPlayer,this->actLevel,this->x,this->y);

            nClient->sendMsgToServer(msgCopy);
            sendToServer = 0;
        }else{
            log->debug("[DynamicPlayer::update DATA] ID_PLAYER NEW POSITION [%d] (lvl:%d, x:%f, y:%f) NOT SENT TO SERVER",this->indexPlayer,this->actLevel,this->x,this->y);
        }


        this->setLocked(false);
    }
};
