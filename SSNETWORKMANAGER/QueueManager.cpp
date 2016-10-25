#include "QueueManager.h"


void QueueManager::runRemoteData(){

    bool DONE = false;
    bool DONE_INPUT_REMOTE_PACKETS = false;
    bool processRemote = false;

    log->debug("[QueueManager::RemoteData] processRemoteData");

    int refreshFromServer = 0;

    while(!DONE){


        refreshFromServer++;

        if (refreshFromServer == TIME_BETWEEN_ACT_SERVER){

            refreshFromServer = 0;

            //EMPTY BUFFER DATA
            int tramaIndexGet = nClientUDP->getIndexTramaGet();
            int tramaIndexSend = nClientUDP->getIndexTramaSend()+1;

            nClientUDP->setIndexTramaGet(tramaIndexGet);
            nClientUDP->setIndexTramaSend(tramaIndexSend);

            log->debug("[QueueManager::RemoteData] QRY DATA FROM DATA SERVER SENDPACKET[%d] GETPACKET[%d]",nClientUDP->getIndexTramaSend(),nClientUDP->getIndexTramaGet());

            nClientUDP->sendMsgToServer(new EventMsg(TRAMA_QRY_DATASERVER,nClientUDP->getIndexTramaSend(),nClientUDP->getIndexTramaGet(),0,1,(uint16_t)0,nClientUDP->getRemotePacket()));
            EventMsg **data = nClientUDP->getMsgsFromServer();

            //nClientQueue->sendMsgToServer(new EventMsg(TRAMA_QRY_DATASERVER,nClientUDP->getIndexTramaSend(),nClientUDP->getIndexTramaGet(),0,1,(uint16_t)0,nClientQueue->getRemotePacket(), pDT));
            //EventMsg **data = nClientQueue->getMsgsFromServer();

            for(int i=0; i<SIZE_REMOTE_ELEMS; i++){
                EventMsg *msg = data[i];
                if (msg->getTypeMsg() == TRAMA_GET_DATASERVER){
                    if (msg->getRemotePlayerType().typeTramaID != 0){
                        log->debug("[QueueManager::RemoteData] get RemoteInfo for IDActor [%d] IDType [%d] (lvl:%d,x:%f,y:%f)",
                                    msg->getRemotePlayerType().idPlayer,
                                    msg->getRemotePlayerType().typeID,
                                    msg->getRemotePlayerType().lvl,
                                    msg->getRemotePlayerType().x_pos,
                                    msg->getRemotePlayerType().y_pos);
                        dataFromServer.push(msg);
                    }
                }
            }
        }

        if (dataFromServer.size()<=0){

            log->warn("[QueueManager::RemoteData] NO RECOVE ALL THE INFORMATION. ACTIVE PREDICTION CLIENTSIDE ENGINE");
            pEngine->processPrediction();

        }else{
            log->info("[QueueManager::RemoteData] RECOVERING ALL THE INFORMATION DONE. ACTIVE INTERPOLATION CLIENT-SERVER ENGINE");

            //PROCESS SERVER DATA. INTERPOLATE WITH LOCAL DATA.
            while(!dataFromServer.empty()){
                EventMsg *data = dataFromServer.front();
                remotePlayerType rPT = data->getRemotePlayerType();

                int level = rPT.lvl;
                int idPlayer = rPT.idPlayer;

                //PROCESSING ENEMIES.
                if (rPT.typeID == TYPE_ACTIVE_ELEMENT){

                    if (mem->getEnemyMapByLevelAndId(level,idPlayer)!=NULL){
                        mem->getEnemyMapByLevelAndId(level,idPlayer)->setDynamicEntity(rPT);
                    }else{
                        DynamicEntity *entity = new DynamicEntity(rPT);
                        mem->addEnemyMapByLevelAndId(level,idPlayer,entity);
                    }

                //PROCESSING ACTIVE ELEMENTS
                }else if (rPT.typeID == TYPE_ACTIVEOTHER_ELEMENT){

                    if (mem->getDynElemMapByLevelAndId(level,idPlayer)!=NULL){
                        mem->getDynElemMapByLevelAndId(level,idPlayer)->setDynamicEntity(rPT);
                    }else{
                        DynamicEntity *entity = new DynamicEntity(rPT);
                        mem->addDynElementMapByLevelAndId(level,idPlayer,entity);
                    }

                //PROCESSING REMOTE PLAYERS
                }else if (rPT.typeID == TYPE_REM_PLAYER_ELEMENT){

                    if (mem->getRemPlayerMapElem(idPlayer)!=NULL){
                        mem->getRemPlayerMapElem(idPlayer)->setDynamicEntity(rPT);
                    }else{
                        //is local player data?
                        if (mem->getActPlayer(mem->getPlayerIndex())->getIndexPlayer() != idPlayer){
                            DynamicEntity *entity = new DynamicEntity(rPT);
                            mem->addRemPlayerMap(idPlayer,entity);
                        }
                    }
                }

                dataFromServer.pop();
            }
        }

        //EMPTY BUFFER DATA
        while (!dataFromServer.empty()){dataFromServer.pop();}
        while (!msgFromServer.empty()){msgFromServer.pop();}

    }//FINAL PROCESO DONE

};

void QueueManager::runLocalData(){
    //nClock->pause();
    pEngine->processPrediction();
    //nClock->unpause();
}

