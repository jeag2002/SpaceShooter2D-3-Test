#include "Stdafx.h"
#include "LogEngine.h"
#include "Subject.h"
#include "MemManager.h"
#include "QueueManager.h"

#include "NetworkClient.h"
#include "NetworkClientUDP.h"

#include "PredictionEngine.h"
#include "ClockEngine.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

LogEngine *logger;
Subject *sub;
MemManager *mem;
QueueManager *qMem;
NetworkClient *nClient;
NetworkClientUDP *nClientUDP;

PredictionEngine *pEngine;
ClockEngine *nClock;
SDL_Window* window;
SDL_Renderer *render;

CollisionEntities *coll;
AnimationEntities *aEnt;
IAEntities *iAEnt;

SDL_mutex* gBufferLock = NULL; //bloquea el uso de memoria
SDL_mutex* gSocketLock = NULL; //bloquea el uso del socket

//The conditions
SDL_cond* gCanProduceMem = NULL;
SDL_cond* gCanConsumeMem = NULL;

SDL_cond* gCanProduceSock = NULL;
SDL_cond* gCanConsumeSock = NULL;

TTF_Font *font;



void createEnvirontment();
void destroyAll();
void getEventSDL();
void processLocalPlayer();
void evalLocalPlayerAgainstEnv(DynamicPlayer *dPlayer);
int threadFunction( void* data );
void initSDLWindows();
void destroySDLWindows();
void processPlayerSession(EventMsg *msg);
void renderScenario();


int main (int argc, char *argv[])
{
   logger = new LogEngine();
   logger->deleteLogFile();
   logger->startUp(1,0);
   logger->printLogFlag();
   logger->info("================ [SSNETWORKMANAGER-CLIENT - INI] ================");

   createEnvirontment();

   nClientUDP->initCommunicationUDP();
   nClientUDP->establishCommunicationUDP();
   nClientUDP->getListActiveSessions();
   EventMsg *responseMsg =  nClientUDP->registerToActiveSession();

   if (responseMsg->getTypeMsg() == TRAMA_ACK_SESSION){
        uint16_t CRC16FromServer = responseMsg->getCRC16();
        uint16_t CRC16Calculated = UtilsProtocol::calculateCRC16_CCITT((const unsigned char *)responseMsg->serializeMsg().c_str(),responseMsg->serializeMsg().size());
        logger->debug("[SSNETWORKMANAGER::MAIN] CRC TRAMA_ACK_SESSION COMM FROM SERVER [%d] COMM FROM CLIENT [%d]",CRC16FromServer,CRC16Calculated);
        playerDataType pDT = responseMsg->getPlayerDataType();
        logger->debug("[SSNETWORKMANAGER::MAIN] SESSION PLAYER Map:%d Session:%d IdPlayer:%d lvl:%d pos:(%f,%f) width:%d, height:%d",
                      pDT.actMap,
                      pDT.session,
                      pDT.idPlayer,
                      pDT.lvl,
                      pDT.x_pos,
                      pDT.y_pos,
                      pDT.width,
                      pDT.heigth);


   }else if (responseMsg->getTypeMsg() == TRAMA_NACK_SESSION){
       uint16_t CRC16FromServer = responseMsg->getCRC16();
       uint16_t CRC16Calculated = UtilsProtocol::calculateCRC16_CCITT((const unsigned char *)responseMsg->serializeMsg().c_str(),responseMsg->serializeMsg().size());
       logger->debug("[SSNETWORKMANAGER::MAIN] CRC TRAMA_NACK_SESSION COMM FROM SERVER [%d] COMM FROM CLIENT [%d]",CRC16FromServer,CRC16Calculated);
       answerType aType = responseMsg->getAnswerType();
       logger->warn("[SSNETWORKMANAGER::MAIN] NACK::RESULT [%d]",aType.result);
       delete nClientUDP;
       exit(-1);

   }else if (responseMsg->getTypeMsg() == TRAMA_NULL){
        logger->warn("[SSNETWORKMANAGER::MAIN] RESULT NULL");
        delete nClientUDP;
        exit(-1);
   }else{
        logger->warn("[SSNETWORKMANAGER::MAIN] PACKET NOT RECOGNIZED");
   }

   /*
   initSDLWindows();

   nClient->initCommunication();
   nClient->establishCommunication();

   //establecer session actual jugador
   nClient->getListActiveSessions();
   EventMsg *responseMsg = nClient->getRemoteIdPlayer();

   if (responseMsg->getTypeMsg() != TRAMA_NACK_SESSION){
        processPlayerSession(responseMsg);
        getEventSDL();
   }else if (responseMsg->getTypeMsg() == TRAMA_NULL){
        logger->warn("[SSNETWORKMANAGER::MAIN] NO FREE SPACE FOR MORE PLAYERS IN MAP [1] SESSION [1]. LOGOUT OF SYSTEM");
        nClient->closeClientSocket();
   }

   nClient->endCommunication();

   destroySDLWindows();
   */

   destroyAll();
   logger->info("================ [SSNETWORKMANAGER-CLIENT - END] ================");
   return 0;
}

void processPlayerSession(EventMsg *msg){
    if (msg->getTypeMsg() == TRAMA_ACK_SESSION){
        playerDataType pDTypeOutput = msg->getPlayerDataType();
        logger->info("[SSNETWORKMANAGER::GETIDPLAYER] MAP_ID [%d] MAP_SESSION [%d] PLAYER_ID [%d] LVL [%d] X_POS [%f] Y_POS [%f]",pDTypeOutput.actMap,pDTypeOutput.session,pDTypeOutput.idPlayer,pDTypeOutput.lvl,pDTypeOutput.x_pos, pDTypeOutput.y_pos);
        mem->getActPlayer(mem->getPlayerIndex())->setDynamicPlayer(pDTypeOutput);
       ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1))->setDynamicPlayer(pDTypeOutput);
    }
}


void initSDLWindows(){
     window = NULL;
     if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ){
        logger->info("[SSNETWORKMANAGER-CLIENT] Error SDL_Init %s",SDL_GetError());
        exit(-1);
     }

     if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
        logger->warn( "[SSNETWORKMANAGER-CLIENT] Warning: Linear texture filtering not enabled!" );
     }

      window = SDL_CreateWindow( "Console SSNETWORKMANAGER-CLIENT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
      if( window == NULL ){
         logger->info("[SSNETWORKMANAGER-CLIENT] Error Create SDL Windows %s", SDL_GetError() );
         exit(-1);
      }

      if( TTF_Init() == -1 )
      {
        logger->warn("[SSNETWORKMANAGER-CLIENT] SDL_ttf could not initialize! SDL_ttf Error: %s", TTF_GetError() );
        exit(-1);
      }

      font = TTF_OpenFont("FreeSans.ttf", 10);
      if (font == NULL){
        logger->info( "[SSNETWORKMANAGER-CLIENT] TrueType Font FreeSans error %s", TTF_GetError());
        exit(-1);
      }

      TTF_SetFontStyle(font, TTF_STYLE_BOLD);

      render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

      if (render == NULL){
        logger->info("[SSNETWORKMANAGER-CLIENT] render error %s",SDL_GetError());
        exit(-1);
      }
}

void destroySDLWindows(){

    TTF_CloseFont(font);
    font = NULL;

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow( window );

    window = NULL;
    render = NULL;

    TTF_Quit();
    SDL_Quit();
}

void createEnvirontment(){

    sub = new Subject();
    mem = new MemManager();

    nClient = new NetworkClient(logger);
    nClientUDP = new NetworkClientUDP(logger);

    nClock = new ClockEngine();

    coll = new CollisionEntities(mem,logger);
    aEnt = new AnimationEntities(mem,logger);
    iAEnt = new IAEntities(mem,logger);

    pEngine = new PredictionEngine(logger,mem,coll,aEnt,iAEnt); //prediction Engine.

    //define threads
    gBufferLock = SDL_CreateMutex();
    gSocketLock = SDL_CreateMutex();

    //define semaphores
    gCanProduceMem = SDL_CreateCond();
    gCanConsumeMem = SDL_CreateCond();

    gCanProduceSock = SDL_CreateCond();
    gCanConsumeSock = SDL_CreateCond();


    qMem = new QueueManager(logger,mem,nClient,pEngine,gBufferLock,gSocketLock,gCanProduceMem,gCanConsumeMem,gCanProduceSock,gCanConsumeSock);

    DynamicPlayer *player_1 = new DynamicPlayer(logger,1, nClient);
    player_1->setActLevel(1);
    player_1->setX(0);
    player_1->setY(0);
    player_1->setWidth(64);
    player_1->setHeight(64);
    player_1->setMapId(1);
    player_1->setSessionID(1);

    mem->setPlayer_1(player_1);
    sub->attachObserver(player_1);
    mem->setPlayerIndex(1);

    //enemigos
    ///////////////////////////////
    DynamicEntity *enemy_1_1 = new DynamicEntity(logger); enemy_1_1->setActLevel(1); enemy_1_1->setIDDE(4); enemy_1_1->setEnabled(true); enemy_1_1->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_1_1->setX(128); enemy_1_1->setY(128);
    DynamicEntity *enemy_2_1 = new DynamicEntity(logger); enemy_2_1->setActLevel(1); enemy_2_1->setIDDE(5); enemy_2_1->setEnabled(true); enemy_2_1->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_2_1->setX(64); enemy_2_1->setY(64);
    DynamicEntity *enemy_3_1 = new DynamicEntity(logger); enemy_3_1->setActLevel(1); enemy_3_1->setIDDE(6); enemy_3_1->setEnabled(true); enemy_3_1->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_3_1->setX(128); enemy_3_1->setY(64);

    mem->addEnemiesMap_lvl_1(4,enemy_1_1);
    mem->addEnemiesMap_lvl_1(5,enemy_2_1);
    mem->addEnemiesMap_lvl_1(6,enemy_3_1);

    DynamicEntity *enemy_1_2 = new DynamicEntity(logger); enemy_1_2->setActLevel(2); enemy_1_2->setIDDE(7); enemy_1_2->setEnabled(true); enemy_1_2->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_1_2->setX(128); enemy_1_2->setY(128);
    DynamicEntity *enemy_2_2 = new DynamicEntity(logger); enemy_2_2->setActLevel(2); enemy_2_2->setIDDE(8); enemy_2_2->setEnabled(true); enemy_2_2->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_2_2->setX(64); enemy_2_2->setY(64);
    DynamicEntity *enemy_3_2 = new DynamicEntity(logger); enemy_3_2->setActLevel(2); enemy_3_2->setIDDE(9); enemy_3_2->setEnabled(true); enemy_3_2->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_3_2->setX(128); enemy_3_2->setY(64);

    mem->addEnemiesMap_lvl_2(7,enemy_1_2);
    mem->addEnemiesMap_lvl_2(8,enemy_2_2);
    mem->addEnemiesMap_lvl_2(9,enemy_3_2);

    DynamicEntity *enemy_1_3 = new DynamicEntity(logger); enemy_1_3->setActLevel(3); enemy_1_3->setIDDE(10); enemy_1_3->setEnabled(true); enemy_1_3->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_1_3->setX(128); enemy_1_3->setY(128);
    DynamicEntity *enemy_2_3 = new DynamicEntity(logger); enemy_2_3->setActLevel(3); enemy_2_3->setIDDE(11); enemy_2_3->setEnabled(true); enemy_2_3->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_2_3->setX(64); enemy_2_3->setY(64);
    DynamicEntity *enemy_3_3 = new DynamicEntity(logger); enemy_3_3->setActLevel(3); enemy_3_3->setIDDE(12); enemy_3_3->setEnabled(true); enemy_3_3->setTypeId(TYPE_ACTIVE_ELEMENT); enemy_3_3->setX(128); enemy_3_3->setY(64);

    mem->addEnemiesMap_lvl_3(10,enemy_1_3);
    mem->addEnemiesMap_lvl_3(11,enemy_2_3);
    mem->addEnemiesMap_lvl_3(12,enemy_3_3);
    ///////////////////////////////

    //elementos dinamicos
    ///////////////////////////////
    DynamicEntity *DynElem_1_1 = new DynamicEntity(logger); DynElem_1_1->setActLevel(1); DynElem_1_1->setIDDE(14); DynElem_1_1->setEnabled(true); DynElem_1_1->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_1_1->setX(256); DynElem_1_1->setY(256);
    DynamicEntity *DynElem_2_1 = new DynamicEntity(logger); DynElem_2_1->setActLevel(1); DynElem_2_1->setIDDE(15); DynElem_2_1->setEnabled(true); DynElem_2_1->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_2_1->setX(256); DynElem_2_1->setY(64);
    DynamicEntity *DynElem_3_1 = new DynamicEntity(logger); DynElem_3_1->setActLevel(1); DynElem_3_1->setIDDE(16); DynElem_3_1->setEnabled(true); DynElem_3_1->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_3_1->setX(64); DynElem_3_1->setY(256);

    mem->addDynElemMap_lvl_1(14,DynElem_1_1);
    mem->addDynElemMap_lvl_1(15,DynElem_2_1);
    mem->addDynElemMap_lvl_1(16,DynElem_3_1);

    DynamicEntity *DynElem_1_2 = new DynamicEntity(logger); DynElem_1_2->setActLevel(2); DynElem_1_2->setIDDE(17); DynElem_1_2->setEnabled(true); DynElem_1_2->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_1_2->setX(256); DynElem_1_2->setY(256);
    DynamicEntity *DynElem_2_2 = new DynamicEntity(logger); DynElem_2_2->setActLevel(2); DynElem_2_2->setIDDE(18); DynElem_2_2->setEnabled(true); DynElem_2_2->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_2_2->setX(256); DynElem_2_2->setY(64);
    DynamicEntity *DynElem_3_2 = new DynamicEntity(logger); DynElem_3_2->setActLevel(2); DynElem_3_2->setIDDE(19); DynElem_3_2->setEnabled(true); DynElem_3_2->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_3_2->setX(64); DynElem_2_2->setY(256);

    mem->addDynElemMap_lvl_2(17,DynElem_1_2);
    mem->addDynElemMap_lvl_2(18,DynElem_2_2);
    mem->addDynElemMap_lvl_2(19,DynElem_3_2);

    DynamicEntity *DynElem_1_3 = new DynamicEntity(logger); DynElem_1_3->setActLevel(3); DynElem_1_3->setIDDE(20); DynElem_1_3->setEnabled(true); DynElem_1_3->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_1_3->setX(256); DynElem_1_3->setY(256);
    DynamicEntity *DynElem_2_3 = new DynamicEntity(logger); DynElem_2_3->setActLevel(3); DynElem_2_3->setIDDE(21); DynElem_2_3->setEnabled(true); DynElem_2_3->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_2_3->setX(256); DynElem_2_3->setY(64);
    DynamicEntity *DynElem_3_3 = new DynamicEntity(logger); DynElem_3_3->setActLevel(3); DynElem_3_3->setIDDE(22); DynElem_3_3->setEnabled(true); DynElem_3_3->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_3_3->setX(64); DynElem_3_3->setY(256);

    mem->addDynElemMap_lvl_3(20,DynElem_1_3);
    mem->addDynElemMap_lvl_3(21,DynElem_2_3);
    mem->addDynElemMap_lvl_3(22,DynElem_3_3);

    ///////////////////////////////
    //remote player
    ///////////////////////////////
    DynamicEntity *rem_player_1 = new DynamicEntity(logger); rem_player_1->setActLevel(1); rem_player_1->setIDDE(23); rem_player_1->setEnabled(false);
    DynamicEntity *rem_player_2 = new DynamicEntity(logger); rem_player_2->setActLevel(1); rem_player_2->setIDDE(24); rem_player_2->setEnabled(false);
    DynamicEntity *rem_player_3 = new DynamicEntity(logger); rem_player_3->setActLevel(1); rem_player_3->setIDDE(25); rem_player_3->setEnabled(false);
    DynamicEntity *rem_player_4 = new DynamicEntity(logger); rem_player_4->setActLevel(1); rem_player_4->setIDDE(26); rem_player_4->setEnabled(false);

    mem->addRemPlayerMap(23,rem_player_1);
    mem->addRemPlayerMap(24,rem_player_2);
    mem->addRemPlayerMap(25,rem_player_3);
    mem->addRemPlayerMap(26,rem_player_4);
    ///////////////////////////////

    mem->setRoofIndex(1);           //planta-1
    mem->setPlayerIndex(1);         //jugador-1

    logger->debug("[SSNETWORKMANAGER::createEnvirontment] -- SET VARIABLES ON");
};

void destroyAll(){

    nClient->closeClientSocket();

   //define threads
   SDL_DestroyMutex(gBufferLock);
   SDL_DestroyMutex(gSocketLock);

   //define semaphores
   SDL_DestroyCond(gCanProduceMem);
   SDL_DestroyCond(gCanConsumeMem);

   SDL_DestroyCond(gCanProduceSock);
   SDL_DestroyCond(gCanConsumeSock);

   delete coll;
   delete aEnt;
   delete iAEnt;

   delete nClient;
   delete nClientUDP;

   delete mem;
   delete qMem;
   delete logger;

};

void getEventSDL(){

    SDL_Event event;

    bool DONE = false;
    bool PRESS = false;

    //nClock->start();

    //SDL_Thread* threadID = SDL_CreateThread( threadFunction, "threadFunction", (void*)NULL );

    localActionType lATPlayer;

    while (!DONE){
        while (SDL_PollEvent(&event)){
            switch (event.type){

                case SDL_KEYDOWN:
                    logger->debug("[MAIN -  EVENT_MSG] KEY DOWN");

                    SDL_Keysym *keysym = &event.key.keysym;

                    if (keysym->sym == SDLK_LEFT){          //-> mover jugador actual a la izquierda
                        lATPlayer.idPlayer = mem->getActPlayer(mem->getPlayerIndex())->getIndexPlayer();
                        lATPlayer.typeMovement = LEFT;
                        lATPlayer._inc = 1.0;
                        lATPlayer._x = 0;
                        lATPlayer._y = 0;
                        lATPlayer.shot = 0;
                        lATPlayer.oldWPN = 0;
                        lATPlayer.newWPN = 0;

                        logger->debug("[MAIN -  EVENT_MSG] SEND LEFT TO ACT PLAYER [%d]=REM_ID[%d]",mem->getPlayerIndex(),lATPlayer.idPlayer);
                        PRESS = true;
                    }

                    else if (keysym->sym == SDLK_RIGHT){    //-> mover jugador actual a la derecha

                        lATPlayer.idPlayer = mem->getActPlayer(mem->getPlayerIndex())->getIndexPlayer();
                        lATPlayer.typeMovement = RIGHT;
                        lATPlayer._inc = 1.0;
                        lATPlayer._x = 0;
                        lATPlayer._y = 0;
                        lATPlayer.shot = 0;
                        lATPlayer.oldWPN = 0;
                        lATPlayer.newWPN = 0;

                        logger->debug("[MAIN -  EVENT_MSG] SEND RIGHT TO ACT PLAYER [%d]=REM_ID[%d]",mem->getPlayerIndex(),lATPlayer.idPlayer);
                        PRESS = true;
                    }

                    else if (keysym->sym == SDLK_UP){       //-> mover jugador actual arriba
                        //sub->setMsg(new EventMsg(3,1.0f,mem->getPlayerIndex()));

                        lATPlayer.idPlayer = mem->getActPlayer(mem->getPlayerIndex())->getIndexPlayer();
                        lATPlayer.typeMovement = UP;
                        lATPlayer._inc = 1.0;
                        lATPlayer._x = 0;
                        lATPlayer._y = 0;
                        lATPlayer.shot = 0;
                        lATPlayer.oldWPN = 0;
                        lATPlayer.newWPN = 0;

                        logger->debug("[MAIN -  EVENT_MSG] SEND UP TO ACT PLAYER[%d]=REM_ID[%d]",mem->getPlayerIndex(),lATPlayer.idPlayer);
                        PRESS = true;
                    }

                    else if (keysym->sym == SDLK_DOWN){     //-> mover jugador actual abajo
                        //sub->setMsg(new EventMsg(4,1.0f,mem->getPlayerIndex()));

                        lATPlayer.idPlayer = mem->getActPlayer(mem->getPlayerIndex())->getIndexPlayer();
                        lATPlayer.typeMovement = DOWN;
                        lATPlayer._inc = 1.0;
                        lATPlayer._x = 0;
                        lATPlayer._y = 0;
                        lATPlayer.shot = 0;
                        lATPlayer.oldWPN = 0;
                        lATPlayer.newWPN = 0;


                        logger->debug("[MAIN -  EVENT_MSG] SEND DOWN TO ACT PLAYER[%d]=REM_ID[%d]",mem->getPlayerIndex(),lATPlayer.idPlayer);
                        PRESS = true;
                    }

                    else if (keysym->sym == SDLK_w){

                        lATPlayer.idPlayer = mem->getActPlayer(mem->getPlayerIndex())->getIndexPlayer();
                        lATPlayer.typeMovement = LVLUP;
                        lATPlayer._inc = 1.0;
                        lATPlayer._x = 0;
                        lATPlayer._y = 0;
                        lATPlayer.shot = 0;
                        lATPlayer.oldWPN = 0;
                        lATPlayer.newWPN = 0;


                        logger->debug("[MAIN -  EVENT_MSG] SEND LEVELUP TO ACT PLAYER[%d]=REM_ID[%d]",mem->getPlayerIndex(),lATPlayer.idPlayer);
                        PRESS = true;
                    }

                    else if (keysym->sym == SDLK_s){

                        lATPlayer.idPlayer = mem->getActPlayer(mem->getPlayerIndex())->getIndexPlayer();
                        lATPlayer.typeMovement = LVLDOWN;
                        lATPlayer._inc = 1.0;
                        lATPlayer._x = 0;
                        lATPlayer._y = 0;
                        lATPlayer.shot = 0;
                        lATPlayer.oldWPN = 0;
                        lATPlayer.newWPN = 0;


                        logger->debug("[MAIN -  EVENT_MSG] SEND LEVELDOWN TO ACT PLAYER[%d]=REM_ID[%d]",mem->getPlayerIndex(),lATPlayer.idPlayer);
                        PRESS = true;
                    }


                    else if (keysym->sym == SDLK_ESCAPE){   //-> salir de la aplicacion
                        logger->debug("[MAIN -  EVENT_MSG] LOGOUT SSNETWORKMANAGER!!!");
                        DONE = true;
                        PRESS = true;
                    }

                    if (PRESS){
                        EventMsg *msg = new EventMsg(lATPlayer);
                        sub->setMsg(msg);

                        //const Uint32 timeout = 10;

                        //SDL_LockMutex(gSocketLock);
                        //SDL_CondWaitTimeout(gCanConsumeSock, gSocketLock,timeout);

                        sub->notify();
                        if (DONE){}

                        //SDL_UnlockMutex(gSocketLock);
                        //SDL_CondSignal(gCanProduceSock);

                    }
                    break;
            }
        }

        qMem->runRemoteData();
        processLocalPlayer();
        //SDL_Delay(16);
    }

    //SDL_WaitThread( threadID, NULL );
    //nClock->stop();
}

void processLocalPlayer(){
    const Uint32 timeout = 10;

    //SDL_LockMutex(gBufferLock);
    //SDL_CondWaitTimeout( gCanConsumeMem, gBufferLock,timeout);

    //nClock->pause();
    evalLocalPlayerAgainstEnv(mem->getPlayer_1());
    renderScenario();

    //nClock->unpause();

    //SDL_UnlockMutex(gBufferLock);
    //SDL_CondSignal( gCanProduceMem );
}

void evalLocalPlayerAgainstEnv(DynamicPlayer *dPlayer){
    bool isCollition = coll->isCollDynamicPlayer(dPlayer);
    if (!isCollition){
        aEnt->isAnimDynamicPlayer(dPlayer);
        iAEnt->isIADynamicPlayer(dPlayer);
    }
}


void renderScenario(){

    logger->info("[SSNETWORKMANAGER::renderScenario]  Render Scenario - INI");

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

        logger->debug("[SSNETWORKMANAGER::renderScenario] ENEMY[%d] (lvl:%d,x:%f,y:%f)==>rect(%d,%d,%d,%d)",dEntity->getIDDE(),dEntity->getActLevel(),dEntity->getX(),dEntity->getY(),en.x,en.y,en.w,en.h);

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

        logger->debug("[SSNETWORKMANAGER::renderScenario] DYN_ELEM[%d] (lvl:%d,x:%f,y:%f)==>rect(%d,%d,%d,%d)",dEntity->getIDDE(),dEntity->getActLevel(),dEntity->getX(),dEntity->getY(),de.x,de.y,de.w,de.h);

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
        if ((dEntity->getActLevel() == player->getActLevel()) &&
           (dEntity->getIDDE() != player->getIndexPlayer()) &&
           (dEntity->isEnabled())){

            SDL_Rect rp;
            rp.x = int(dEntity->getX());
            rp.y = int(dEntity->getY());
            rp.w = int(dEntity->getWidth());
            rp.h = int(dEntity->getHeight());

            SDL_SetRenderDrawColor(render,0,255,255,255);
            SDL_RenderFillRect(render, &rp);

            logger->debug("[SSNETWORKMANAGER::renderScenario] REM_PLAYER[%d] (lvl:%d,x:%f,y:%f)==>rect(%d,%d,%d,%d)",dEntity->getIDDE(),dEntity->getActLevel(),dEntity->getX(),dEntity->getY(),rp.x,rp.y,rp.w,rp.h);


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

    SDL_RenderPresent( render );

    logger->info("[SSNETWORKMANAGER::renderScenario]  Render Scenario -END");

};




int threadFunction( void* data ){
    qMem->runRemoteData();
    return 0;
}


