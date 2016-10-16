#include "QueueManager.h"


void QueueManager::runRemoteData(){

    bool DONE = false;
    bool processRemote = false;

    log->debug("[QueueManager::RemoteData] processRemoteData");

        int tramaIndexGet = nClientUDP->getIndexTramaGet();
        int tramaIndexSend = nClientUDP->getIndexTramaSend()+1;

        nClientUDP->setIndexTramaGet(tramaIndexGet);
        nClientUDP->setIndexTramaSend(tramaIndexSend);

        nClientUDP->sendMsgToServer(new EventMsg(TRAMA_QRY_DATASERVER,nClientUDP->getIndexTramaSend(),nClientUDP->getIndexTramaGet(),0,1,(uint16_t)0,nClientUDP->getRemotePacket()));
        processRemote = false;

        int mark_initial = SDL_GetTicks();

        while((SDL_GetTicks()-mark_initial) <= 2000){
            EventMsg *msg = nClientUDP->getMsgFromServer();
            if (msg->getTypeMsg() == TRAMA_GET_DATASERVER){
                if (msg->getRemotePlayerType().typeTramaID != 0){

                    log->debug("[QueueManager::RemoteData] get RemoteInfo for IDActor [%d] IDType [%d] (lvl:%d,x:%f,y:%f)",
                               msg->getRemotePlayerType().idPlayer,
                               msg->getRemotePlayerType().typeID,
                               msg->getRemotePlayerType().lvl,
                               msg->getRemotePlayerType().x_pos,
                               msg->getRemotePlayerType().y_pos);

                    dataFromServer.push(msg);
                }else if (msg->getMsgType().msgTypeID != 0){
                    msgFromServer.push(msg);
                }

                if (msg->getMore()!=OK){
                    break;
                    processRemote = true;
                }
            }
        }


        if (!processRemote){
            //CLEAN BUFFER OF SERVER AND IGNORE IT. ACTIVE PREDICTION CLIENTSIDE ENGINE
            log->warn("[QueueManager::RemoteData] NO RECOVE ALL THE INFORMATION. ACTIVE PREDICTION CLIENTSIDE ENGINE");

            while (!processRemote){
                 EventMsg *msg = nClientUDP->getMsgFromServer();
                 if (msg->getMsgType().msgTypeID!=0){
                    msgFromServer.push(msg);
                 }else if (msg->getRemotePlayerType().typeTramaID != 0){
                    log->debug("[QueueManager::RemoteData] (OUTOFDATA) get RemoteInfo for IDActor [%d] IDType [%d] (lvl:%d,x:%f,y:%f)",
                               msg->getRemotePlayerType().idPlayer,
                               msg->getRemotePlayerType().typeID,
                               msg->getRemotePlayerType().lvl,
                               msg->getRemotePlayerType().x_pos,
                               msg->getRemotePlayerType().y_pos);
                 }
                 if (msg->getMore()!=OK){processRemote = true;}
            }
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

};

void QueueManager::runLocalData(){
    nClock->pause();
    pEngine->processPrediction();
    nClock->unpause();
}

