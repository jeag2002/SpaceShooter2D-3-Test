#include "DynamicPlayer.h"

void DynamicPlayer::update(EventMsg *msg){

    //SDL_Delay(100);

    localActionType lAcType = msg->getLocalActionType();
    msgType msgType = msg->getMsgType();
    OrderType oType = msg->getOrderType();

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
        msgCopy->setTypeMsg(TRAMA_COMMAND);
        this->setLocked(false);

    }else if (msgType.originMsg == this->indexPlayer){
        this->setLocked(true);
        msgCopy->setMsgType(msgType);
        msgCopy->setTypeMsg(TRAMA_SND_ORDER_TO_SERVER);
        this->setLocked(false);
    }else if (oType.entityID == this->indexPlayer){
        this->setLocked(true);
        msgCopy->setOrderType(oType);
        msgCopy->setTypeMsg(TRAMA_SND_ORDER_TO_SERVER);
        this->setLocked(false);
    }


    if (msgCopy->getTypeMsg()==TRAMA_COMMAND){
        this->sendToServer++;
        if (sendToServer==10){

            int indexTramaSend = nClient->getIndexTramaSend();
            indexTramaSend++;
            nClient->setIndexTramaSend(indexTramaSend);


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
            nClient->sendMsgToServer(msgCopy);
            sendToServer = 0;
        }
    }else{

        int indexTramaSend = nClient->getIndexTramaSend();
        indexTramaSend++;
        nClient->setIndexTramaSend(indexTramaSend);


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
        nClient->sendMsgToServer(msgCopy);
        sendToServer = 0;
    }

};
