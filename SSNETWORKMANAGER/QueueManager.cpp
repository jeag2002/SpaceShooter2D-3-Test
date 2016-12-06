#include "QueueManager.h"


void QueueManager::processRemoteMsg(EventMsg *inputMsg){

    remotePlayerType rPT = inputMsg->getRemotePlayerType();
    int level = rPT.lvl;
    int idPlayer = rPT.idPlayer;

    //PROCESSING ENEMIES.
    if (rPT.typeID == TYPE_ACTIVE_ELEMENT){
        if (mem->getEnemyMapByLevelAndId(level,idPlayer)!=NULL){
            mem->getEnemyMapByLevelAndId(level,idPlayer)->setDynamicEntity(rPT,inputMsg->getTramaGet());
        }else{
            DynamicEntity *entity = new DynamicEntity(rPT);
            mem->addEnemyMapByLevelAndId(level,idPlayer,entity);
        }
        //PROCESSING ACTIVE ELEMENTS
    }else if (rPT.typeID == TYPE_ACTIVEOTHER_ELEMENT){
        if (mem->getDynElemMapByLevelAndId(level,idPlayer)!=NULL){
            mem->getDynElemMapByLevelAndId(level,idPlayer)->setDynamicEntity(rPT,inputMsg->getTramaGet());
        }else{
            DynamicEntity *entity = new DynamicEntity(rPT);
            mem->addDynElementMapByLevelAndId(level,idPlayer,entity);
        }
        //PROCESSING REMOTE PLAYERS
    }else if (rPT.typeID == TYPE_REM_PLAYER_ELEMENT){
        if (mem->getRemPlayerMapElem(idPlayer)!=NULL){
            mem->getRemPlayerMapElem(idPlayer)->setDynamicEntity(rPT,inputMsg->getTramaGet());
        }else{
            //is local player data?
            if (mem->getActPlayer(mem->getPlayerIndex())->getIndexPlayer() != idPlayer){
                DynamicEntity *entity = new DynamicEntity(rPT);
                mem->addRemPlayerMap(idPlayer,entity);
            }
        }
    }


}


void QueueManager::runRemoteData(){

    bool DONE = false;
    bool DONE_INPUT_REMOTE_PACKETS = false;
    bool processRemote = false;

    log->debug("[QueueManager::RemoteData] processRemoteData");

    int refreshFromServer = 0;
    int numTramas  = 0;

    while(!DONE){


        refreshFromServer++;
        numTramas = 0;

        if (refreshFromServer == TIME_BETWEEN_ACT_SERVER){

            refreshFromServer = 0;

            //EMPTY BUFFER DATA
            int tramaIndexGet = nClientUDP->getIndexTramaGet();
            int tramaIndexSend = nClientUDP->getIndexTramaSend()+1;

            nClientUDP->setIndexTramaGet(tramaIndexGet);
            nClientUDP->setIndexTramaSend(tramaIndexSend);

            log->debug("[QUEUEMANAGER::REMOTEDATA] QRY DATA FROM DATA SERVER SENDPACKET[%d] GETPACKET[%d]",nClientUDP->getIndexTramaSend(),nClientUDP->getIndexTramaGet());

            EventMsg *iMsg = new EventMsg(TRAMA_QRY_DATASERVER,nClientUDP->getIndexTramaSend(),nClientUDP->getIndexTramaGet(),0,1,(uint16_t)0,nClientUDP->getRemotePacket(),pDT);
            nClientUDP->sendMsgToServer(iMsg);

            bool DONE = false;

            int ticks = SDL_GetTicks();

            while (!DONE){
                EventMsg *msg = nClientUDP->getMsgFromServer();

                if (msg->getTypeMsg() == TRAMA_GET_DATASERVER){

                    if (msg->getTramaSend() < iMsg->getTramaSend()){

                        log->debug("[QUEUEMANAGER::REMOTEDATA] GET REMOTE INFO FOR TypeTramaID:[%d] IDType:[%d] EntityID:[%d] IDActor:[%d] (actMap:%d,session:%d,lvl:%d,x:%f,y:%f,width:%d,height:%d) score[%d] die[%d] animId[%d] enabled [%d]",
                                    msg->getRemotePlayerType().typeTramaID,
                                    msg->getRemotePlayerType().typeID,
                                    msg->getRemotePlayerType().entityID,
                                    msg->getRemotePlayerType().idPlayer,
                                    msg->getRemotePlayerType().actMap,
                                    msg->getRemotePlayerType().session,
                                    msg->getRemotePlayerType().lvl,
                                    msg->getRemotePlayerType().x_pos,
                                    msg->getRemotePlayerType().y_pos,
                                    msg->getRemotePlayerType().width,
                                    msg->getRemotePlayerType().height,
                                    msg->getRemotePlayerType().score,
                                    msg->getRemotePlayerType().die,
                                    msg->getRemotePlayerType().animIndex,
                                    msg->getRemotePlayerType().enabled);

                        processRemoteMsg(msg);
                    }


                    numTramas++;
                }else if (msg->getTypeMsg() == TRAMA_SND_ORDER_TO_SERVER){

                    msgType mType = msg->getMsgType();
                    if (mType.msgTypeID == TYPE_MSG_FROM_SERVER){
                        log->debug("[QUEUEMANAGER::REMOTEDATA] GET MSG FROM SERVER [%s]",mType.msg);
                        mem->push(msg);
                    }
                }

                DONE = (numTramas >= SIZE_REMOTE_ELEMS);
                if (!DONE){
                    DONE = ((SDL_GetTicks()-ticks) >= TIMEOUT);
                }
            }
        }
    }//FINAL PROCESO DONE

};


