#include "QueueManager.h"


void QueueManager::processRemoteMsg(EventMsg *inputMsg){

    remotePlayerType rPT = inputMsg->getRemotePlayerType();
    int level = rPT.lvl;
    int idPlayer = rPT.idPlayer;

    //PROCESSING ENEMIES.
    if (rPT.typeID == TYPE_ACTIVE_ELEMENT){
        if (mem->getEnemyMapByLevelAndId(level,idPlayer)!=NULL){
            mem->getEnemyMapByLevelAndId(level,idPlayer)->setDynamicEntity(rPT,inputMsg->getTramaSend());
        }else{
            DynamicEntity *entity = new DynamicEntity(rPT);
            mem->addEnemyMapByLevelAndId(level,idPlayer,entity);
        }
        //PROCESSING ACTIVE ELEMENTS
    }else if (rPT.typeID == TYPE_ACTIVEOTHER_ELEMENT){
        if (mem->getDynElemMapByLevelAndId(level,idPlayer)!=NULL){
            mem->getDynElemMapByLevelAndId(level,idPlayer)->setDynamicEntity(rPT,inputMsg->getTramaSend());
        }else{
            DynamicEntity *entity = new DynamicEntity(rPT);
            mem->addDynElementMapByLevelAndId(level,idPlayer,entity);
        }
        //PROCESSING REMOTE PLAYERS
    }else if (rPT.typeID == TYPE_REM_PLAYER_ELEMENT){
        if (mem->getRemPlayerMapElem(idPlayer)!=NULL){
            mem->getRemPlayerMapElem(idPlayer)->setDynamicEntity(rPT,inputMsg->getTramaSend());
        }else{
            //is local player data?
            if (mem->getActPlayer(mem->getPlayerIndex())->getIndexPlayer() != idPlayer){
                DynamicEntity *entity = new DynamicEntity(rPT);
                mem->addRemPlayerMap(idPlayer,entity);
            }
        }
    }
}



void QueueManager::renderScenario(){

    log->info("[SSNETWORKMANAGER::renderScenario]  Render Scenario - INI");

    SDL_SetRenderDrawColor(render,100,100,100,255);

    SDL_RenderClear(render);

    //-->LOCAL PLAYER (BLUE)
    DynamicPlayer *player = ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1));
    char buffer[200]; for(int i=0; i<200; i++){buffer[i]='\0';}
    sprintf(buffer,"player id:[%d] map:%d session:%d lvl:%d x:%f y:%f",
            player->getIndexPlayer(),
            player->getMapID(),
            player->getSessionID(),
            player->getActLevel(),
            player->getX(),
            player->getY());
    SDL_SetWindowTitle(window,(const char *)buffer);

    SDL_Rect r;
    r.x = int(player->getX());
    r.y = int(player->getY());
    r.w = int(player->getWidth());
    r.h = int(player->getHeight());

    SDL_SetRenderDrawColor(render,0,0,255,255);
    SDL_RenderFillRect(render, &r);


    SDL_Color white = {0xff, 0xff, 0xff, 0xff};
    SDL_Surface* textSurface = NULL;
    SDL_Texture* textTexture = NULL;

    //////////////////////////////////////////
    for(int i=0; i<200; i++){buffer[i]='\0';}
    sprintf(buffer,"PLY ID:[%d]",player->getIndexPlayer());

    textSurface = TTF_RenderText_Solid( font, (const char *)buffer, white);
    textTexture = SDL_CreateTextureFromSurface( render, textSurface );

    SDL_Rect text;
    text.x = int(player->getX());
    text.y = int(player->getY())-10;
    text.w = int(player->getWidth());
    text.h = 10;

    SDL_RenderCopyEx(render,textTexture, NULL, &text, 0, NULL, SDL_FLIP_NONE);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    //////////////////////////////////////////


    //-->ENEMIES (GREEN)
    std::map<int, DynamicEntity *>enemyOfLevel = mem->getEnemyMapByLevel(player->getActLevel());

    for(auto iterator = enemyOfLevel.begin(); iterator != enemyOfLevel.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        SDL_Rect en;
        en.x = int(dEntity->getX());
        en.y = int(dEntity->getY());
        en.w = int(dEntity->getWidth());
        en.h = int(dEntity->getHeight());

        log->debug("[SSNETWORKMANAGER::renderScenario] ENEMY[%d] (lvl:%d,x:%f,y:%f)==>rect(%d,%d,%d,%d)",dEntity->getIDDE(),dEntity->getActLevel(),dEntity->getX(),dEntity->getY(),en.x,en.y,en.w,en.h);

        SDL_SetRenderDrawColor(render,0,255,0,255);
        SDL_RenderFillRect(render, &en);

        //////////////////////////////////////////

        char buffer[200]; for(int i=0; i<200; i++){buffer[i]='\0';}
        sprintf(buffer,"ENMY ID:[%d]",dEntity->getIDDE());

        textSurface = TTF_RenderText_Solid( font, (const char *)buffer, white);
        textTexture = SDL_CreateTextureFromSurface( render, textSurface );

        SDL_Rect text;
        text.x = int(dEntity->getX());
        text.y = int(dEntity->getY())-10;
        text.w = int(dEntity->getWidth());
        text.h = 10;

        SDL_RenderCopyEx(render,textTexture, NULL, &text, 0, NULL, SDL_FLIP_NONE);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        //////////////////////////////////////////
    }

    //-->ACTIVE ELEMENTS (RED)
    std::map<int, DynamicEntity *>dynElemOfLevel = mem->getDynElemMapByLevel(player->getActLevel());

    for(auto iterator = dynElemOfLevel.begin(); iterator != dynElemOfLevel.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        SDL_Rect de;
        de.x = int(dEntity->getX());
        de.y = int(dEntity->getY());
        de.w = int(dEntity->getWidth());
        de.h = int(dEntity->getHeight());

        log->debug("[SSNETWORKMANAGER::renderScenario] DYN_ELEM[%d] (lvl:%d,x:%f,y:%f)==>rect(%d,%d,%d,%d)",dEntity->getIDDE(),dEntity->getActLevel(),dEntity->getX(),dEntity->getY(),de.x,de.y,de.w,de.h);

        SDL_SetRenderDrawColor(render,255,0,0,255);
        SDL_RenderFillRect(render, &de);

        //////////////////////////////////////////

        char buffer[200]; for(int i=0; i<200; i++){buffer[i]='\0';}
        sprintf(buffer,"ACTEL ID:[%d]",dEntity->getIDDE());

        textSurface = TTF_RenderText_Solid( font, (const char *)buffer, white);
        textTexture = SDL_CreateTextureFromSurface( render, textSurface );

        SDL_Rect text;
        text.x = int(dEntity->getX());
        text.y = int(dEntity->getY())-10;
        text.w = int(dEntity->getWidth());
        text.h = 10;

        SDL_RenderCopyEx(render,textTexture, NULL, &text, 0, NULL, SDL_FLIP_NONE);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        //////////////////////////////////////////
    }

    //-->REMOTEPLAYERS (YELLOW)
    std::map<int, DynamicEntity *>remPlayerMap = mem->getRemPlayerMap();

    for(auto iterator = remPlayerMap.begin(); iterator != remPlayerMap.end(); iterator++){
        int i = iterator->first;
        DynamicEntity *dEntity = iterator->second;
        if (
           (dEntity->getActLevel() == player->getActLevel()) &&
           (dEntity->getIDDE() != player->getIndexPlayer()) &&
           (dEntity->isEnabled())
            ){

            SDL_Rect rp;
            rp.x = int(dEntity->getX());
            rp.y = int(dEntity->getY());
            rp.w = int(dEntity->getWidth());
            rp.h = int(dEntity->getHeight());

            SDL_SetRenderDrawColor(render,255,255,0,255);
            SDL_RenderFillRect(render, &rp);

            log->debug("[SSNETWORKMANAGER::renderScenario] REM_PLAYER[%d] (lvl:%d,x:%f,y:%f)==>rect(%d,%d,%d,%d)",dEntity->getIDDE(),dEntity->getActLevel(),dEntity->getX(),dEntity->getY(),rp.x,rp.y,rp.w,rp.h);


            //////////////////////////////////////////

            char buffer[200]; for(int i=0; i<200; i++){buffer[i]='\0';}
            sprintf(buffer,"REMPLY ID:[%d]",dEntity->getIDDE());

            textSurface = TTF_RenderText_Solid( font, (const char *)buffer, white);
            textTexture = SDL_CreateTextureFromSurface( render, textSurface );

            SDL_Rect text;
            text.x = int(dEntity->getX());
            text.y = int(dEntity->getY())-10;
            text.w = int(dEntity->getWidth());
            text.h = 10;

            SDL_RenderCopyEx(render,textTexture, NULL, &text, 0, NULL, SDL_FLIP_NONE);
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);

            //////////////////////////////////////////

        }
    }

    //MESSAGES
    if (!mem->isEmpty()){


        SDL_Color yellow = {0xff, 0xff, 0x00, 0xff};

        EventMsg *inputMSG = mem->front();

        textSurface = TTF_RenderText_Solid( font, inputMSG->getMsgType().msg, yellow);
        textTexture = SDL_CreateTextureFromSurface( render, textSurface );

        SDL_Rect text;
        text.x = 1024 - (SIZE_MSG*5) -10;
        text.y = 0;
        text.w = (SIZE_MSG*5);
        text.h = 40;

        SDL_RenderCopyEx(render,textTexture, NULL, &text, 0, NULL, SDL_FLIP_NONE);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        int data = (SDL_GetTicks() - lowTime);

        if (data >= 5000){
           lowTime = SDL_GetTicks();
           if (mem->sizeQueue() > 1){
                mem->pop();
           }
        }
    }

    SDL_RenderPresent( render );

    log->info("[SSNETWORKMANAGER::renderScenario]  Render Scenario -END");

};





void QueueManager::remoteRemoteProcessData(){

    //std::string ip(host);
    //log->debug("[QueueManager::RemoteData] HOST[%s] REMPORT[%d] LOCALPORT[%d]",ip.c_str(),remPort,localPort);


        //nClientQueue->initCommunicationUDP(ip, remPort, localPort);

        lowTime = SDL_GetTicks();

        while (!getDONE()){

            try{

                long mark = 0;
                mark = SDL_GetTicks();
                long sizeTemp = mem->getSizeTimeServer();

               //do{
                EventMsg *msg = nClientUDP->getMsgFromServerQueue();
                if (msg->getTypeMsg() == TRAMA_GET_DATASERVER){
                        long indexData = msg->getTramaSend();
                        if (indexData >= mem->getTimeStampServer()){
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
                            mem->setTimeStampServer(indexData);
                        }
                }else if (msg->getTypeMsg() == TRAMA_SND_ORDER_TO_SERVER){
                    msgType mType = msg->getMsgType();
                    if (mType.msgTypeID == TYPE_MSG_FROM_SERVER){
                        log->debug("[QUEUEMANAGER::REMOTEDATA] GET REMOTE MSG [%s]",mType.msg);
                        mem->push(msg);
                    }
                }else if (msg->getTypeMsg() == TRAMA_RESULT_TEST){
                    resultPingType rPType = msg->getResultPingType();
                    mem->setSizeTimeServer(rPType.millisping);
                    mem->setTimeStampServer(rPType.indexAuthServer);
                    log->debug("[QUEUEMANAGER::REMOTEDATA] GET TIMESERVER [%d] GET TIMESTAMPSERVER [%d]",rPType.millisping,rPType.indexAuthServer);
                }
                //pEngine->processPrediction();
            }catch(...){
              log->error("[QUEUEMANAGER::REMOTEDATA] Exception when get data from server");
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


