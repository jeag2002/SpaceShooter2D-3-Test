#include "TaskInputEvents.h"


bool TaskInputEvents::getEventPollsThreadSafe(SDL_Event *event){
     bool res = true;
     pthread_mutex_lock(&lock);
     SDL_PumpEvents();
     res = SDL_PollEvent(event);
     pthread_mutex_unlock(&lock);
     return res;
}


void TaskInputEvents::Run(){

    if (SDL_Init( SDL_INIT_EVERYTHING) < 0 ){exit(-1);}

    if (sem_wait(&OKToBuyMilk)==0){
        pthread_mutex_lock(&lock);
        iThread = pthread_self();
        int i=0;
        sem_getvalue(&OKToBuyMilk,&i);
        logger->debug("TaskInputEvents:: PID %d CreateThread [%08x] - SEMAPHOR [%d]", getpid(), iThread, i);
        sem_post(&Remote);
        sem_post(&OKToBuyMilk);
        pthread_mutex_unlock(&lock);
    }

    SDL_Event event;

    bool DONE = false;
    bool PRESS = false;

    pthread_mutex_lock(&lock);
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    pthread_mutex_unlock(&lock);

    while (!DONE){
        while (getEventPollsThreadSafe(&event)){
            switch (event.type){
                case SDL_KEYDOWN:
                    logger->debug("[TASKINPUTEVENTS -  EVENT_MSG] THREAD [%08x] KEY DOWN", iThread);
                    SDL_Keysym *keysym = &event.key.keysym;

                    //if (keys[SDL_SCANCODE_LEFT]){          //-> mover jugador actual a la izquierda
                    if (keysym->sym == SDLK_LEFT){
                        sub->setMsg(new EventMsg(1,1.0f,mem->getPlayerIndex()));
                        logger->debug("[TASKINPUTEVENTS -  EVENT_MSG] THREAD [%08x] SEND LEFT TO ACT PLAYER [%d]",iThread,mem->getPlayerIndex());
                        PRESS = true;
                    }

                    //else if (keys[SDL_SCANCODE_RIGHT]){    //-> mover jugador actual a la derecha
                    else if (keysym->sym == SDLK_RIGHT){
                        sub->setMsg(new EventMsg(2,1.0f,mem->getPlayerIndex()));
                        logger->debug("[TASKINPUTEVENTS -  EVENT_MSG] THREAD [%08x] SEND RIGHT TO ACT PLAYER [%d]",iThread,mem->getPlayerIndex());
                        PRESS = true;
                    }

                    //else if (keys[SDL_SCANCODE_UP]){       //-> mover jugador actual arriba
                    else if (keysym->sym == SDLK_UP){
                        sub->setMsg(new EventMsg(3,1.0f,mem->getPlayerIndex()));
                        logger->debug("[TASKINPUTEVENTS -  EVENT_MSG] THREAD [%08x] SEND UP TO ACT PLAYER [%d]",iThread,mem->getPlayerIndex());
                        PRESS = true;
                    }

                    //else if (keys[SDL_SCANCODE_DOWN]){     //-> mover jugador actual abajo
                    else if (keysym->sym == SDLK_DOWN){
                        sub->setMsg(new EventMsg(4,1.0f,mem->getPlayerIndex()));
                        logger->debug("[TASKINPUTEVENTS -  EVENT_MSG] THREAD [%08x] SEND DOWN TO ACT PLAYER [%d]",iThread,mem->getPlayerIndex());
                        PRESS = true;
                    }

                    //else if (keys[SDL_SCANCODE_A]){        //-> cambiar jugador
                    else if (keysym->sym == SDLK_a){
                        logger->debug("[TASKINPUTEVENTS -  EVENT_MSG] THREAD [%08x] CHANGE PLAYER. ACT PLAYER [%d]",iThread,mem->getPlayerIndex());
                        pthread_mutex_lock(&lock);
                        int indexPlayer = mem->getPlayerIndex();
                        int indexPlayer_new = indexPlayer + 1;
                        if (indexPlayer_new > 3){indexPlayer_new = 1;}
                        mem->setPlayerIndex(indexPlayer_new);
                        logger->debug("[TASKINPUTEVENTS -  EVENT_MSG] THREAD [%08x] before player [%d] after player [%d]",iThread,indexPlayer,indexPlayer_new);
                        pthread_mutex_unlock(&lock);
                        PRESS = true;
                    }


                    //else if (keys[SDL_SCANCODE_D]){        //-> cambiar nivel
                    else if (keysym->sym == SDLK_d){
                        logger->debug("[TASKINPUTEVENTS -  EVENT_MSG] THREAD [%08x] CHANGE LEVEL. ACT LEVEL [%d]",iThread,mem->getPlayerIndex());
                        pthread_mutex_lock(&lock);
                        int indexPlayer = mem->getPlayerIndex();
                        DynamicPlayer *player = mem->getActPlayer(indexPlayer);
                        int indexLevel = player->getActLevel();
                        int indexLevel_new = indexLevel + 1;
                        if (indexLevel_new > 3){indexLevel_new = 1;}
                        player->setActLevel(indexLevel_new);
                        mem->setActPlayer(indexPlayer, player);
                        mem->setRoofIndex(indexLevel_new);
                        logger->debug("[TASKINPUTEVENTS -  EVENT_MSG] THREAD [%08x] player [%d] before level [%d] after level [%d]",iThread,indexPlayer,indexLevel,indexLevel_new);
                        pthread_mutex_unlock(&lock);
                        PRESS = true;
                    }

                    //else if (keys[SDL_SCANCODE_ESCAPE]){   //-> salir de la aplicacion
                    else if (keysym->sym == SDLK_ESCAPE){
                        logger->debug("[TASKINPUTEVENTS -  EVENT_MSG] THREAD [%08x] LOGOUT SSMULTITASKINGMANAGER!!!",iThread);
                        DONE = true;
                        PRESS = true;
                    }

                    if (PRESS){
                        sub->notify();
                        processLocalPlayer();
                        if (DONE){
                            pthread_mutex_lock(&lock);
                            struct timespec ts;
                            ts.tv_sec = 100 / 1000;
                            ts.tv_nsec = (100 % 1000) * 1000000;
                            pthread_cond_timedwait(&dataNotConsumed, &lock, &ts);
                            logger->debug("[TASKINPUTEVENTS -  EVENT_MSG] THREAD [%08x] Wait consumers signals",iThread);
                            if (!qMem->isEmptyMessageOutput()){qMem->popMessageOutputQueue();}
                            int index_data = 0;
                            EventMsg *msg = new EventMsg(6,0.0,0,index_data);
                            qMem->setMessageOutput(msg);
                            logger->debug("[TASKINPUTEVENTS -  EVENT_MSG] THREAD [%08x] Send DONE MSG [%d] index [%d]",iThread,msg->getTypeMsg(),index_data);
                            index_data=index_data+1;
                            logger->debug("[TASKINPUTEVENTS -  EVENT_MSG] THREAD [%08x] Broadcasting Produced",iThread);
                            pthread_cond_broadcast(&dataNotProduced);
                            pthread_mutex_unlock(&lock);
                        }
                    }

                    break;
            }
        }
        SDL_Delay(100);
    }
}

void TaskInputEvents::processLocalPlayer(){

    if (mem->getPlayerIndex()==1){
        evalLocalPlayerAgainstEnv(mem->getPlayer_1());
    }else if(mem->getPlayerIndex()==2){
        evalLocalPlayerAgainstEnv(mem->getPlayer_2());
    }else{
        evalLocalPlayerAgainstEnv(mem->getPlayer_3());
    }

}

void TaskInputEvents::evalLocalPlayerAgainstEnv(DynamicPlayer *dPlayer){
    bool isCollition = coll->isCollDynamicPlayer(dPlayer,iThread);

    if (!isCollition){
        anim->isAnimDynamicPlayer(dPlayer,iThread);
        ia->isIADynamicPlayer(dPlayer,iThread);
    }
}

