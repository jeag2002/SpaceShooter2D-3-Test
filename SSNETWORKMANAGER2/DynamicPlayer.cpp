#include "DynamicPlayer.h"

void DynamicPlayer::update(EventMsg *msg, long timeMark){

    //SDL_Delay(100);

    localActionType lAcType = msg->getLocalActionType();
    msgType msgType = msg->getMsgType();
    OrderType oType = msg->getOrderType();
    exitType eType = msg->getExitType();
    shotType sType = msg->getShotType();

    EventMsg *msgCopy = new EventMsg();
    if (lAcType.idPlayer == this->indexPlayer){

        movementType mType;
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
            mType.velocity = lAcType._velocity;
            mType.x_next = 0;
            mType.y_next = 0;
            mType.velocity_next = 0;
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
            mType.velocity = lAcType._velocity;
            mType.x_next = 0;
            mType.y_next = 0;
            mType.velocity_next = 0;

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
            mType.velocity = lAcType._velocity;
            mType.x_next = 0;
            mType.y_next = 0;
            mType.velocity_next = 0;
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
            mType.velocity = lAcType._velocity;
            mType.x_next = 0;
            mType.y_next = 0;
            mType.velocity_next = 0;
            msgCopy->setMovementType(mType);

        }else if (lAcType.typeMovement == MOUSE){

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
            mType.velocity = lAcType._velocity;
            mType.x_next = 0;
            mType.y_next = 0;
            mType.velocity_next = 0;

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
            mType.velocity = lAcType._velocity;
            mType.x_next = 0;
            mType.y_next = 0;
            mType.velocity_next = 0;

            msgCopy->setMovementType(mType);
        }

        msgCopy->setTypeMsg(TRAMA_COMMAND);
        this->setLocked(false);


        if ((lAcType.typeMovement == LVLUP) || (lAcType.typeMovement == LVLDOWN)){

            ////////////////////////
            int indexTramaSend = nClient->getIndexTramaSend();
            indexTramaSend++;
            nClient->setIndexTramaSend(indexTramaSend);
            msgCopy->setTramaGet(timeMark);
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
            ////////////////////////
        }else{

            if (sendToServer < 10){
                sendToServer++;
            }else{

                int indexTramaSend = nClient->getIndexTramaSend();
                indexTramaSend++;
                nClient->setIndexTramaSend(indexTramaSend);
                msgCopy->setTramaGet(timeMark);
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
        }


    }else if (msgType.originMsg == this->indexPlayer){

        this->setLocked(true);
        msgCopy->setMsgType(msgType);
        msgCopy->setTypeMsg(TRAMA_SND_ORDER_TO_SERVER);
        this->setLocked(false);

        ////////////////////////
        int indexTramaSend = nClient->getIndexTramaSend();
        indexTramaSend++;
        nClient->setIndexTramaSend(indexTramaSend);
        msgCopy->setTramaGet(timeMark);
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
        ////////////////////////

    }else if (oType.entityID == this->indexPlayer){

        this->setLocked(true);
        msgCopy->setOrderType(oType);
        msgCopy->setTypeMsg(TRAMA_SND_ORDER_TO_SERVER);
        this->setLocked(false);

        ////////////////////////
        int indexTramaSend = nClient->getIndexTramaSend();
        indexTramaSend++;
        nClient->setIndexTramaSend(indexTramaSend);
        msgCopy->setTramaGet(timeMark);
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
        ////////////////////////

    }else if (eType.idPlayer == this->indexPlayer){

        this->setLocked(true);
        msgCopy->setExitType(eType);
        msgCopy->setTypeMsg(TRAMA_COMMAND);
        this->setLocked(false);

        ////////////////////////
        int indexTramaSend = nClient->getIndexTramaSend();
        indexTramaSend++;
        nClient->setIndexTramaSend(indexTramaSend);
        msgCopy->setTramaGet(timeMark);
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
        ////////////////////////

    }else if (sType.idPlayer == this->indexPlayer){
        this->setLocked(true);
        msgCopy->setShotType(sType);
        msgCopy->setTypeMsg(TRAMA_COMMAND);
        this->setLocked(false);


        ////////////////////////
        int indexTramaSend = nClient->getIndexTramaSend();
        indexTramaSend++;
        nClient->setIndexTramaSend(indexTramaSend);
        msgCopy->setTramaGet(timeMark);
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
        ////////////////////////

    }



    delete msgCopy;

};
