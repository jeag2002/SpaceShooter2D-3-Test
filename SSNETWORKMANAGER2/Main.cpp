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

SDL_mutex *nMainMutex;
SDL_cond *cond;


PredictionEngine *pEngine;
ClockEngine *nClock;
SDL_Window* window;
SDL_Renderer *render;

CollisionEntities *coll;
AnimationEntities *aEnt;
IAEntities *iAEnt;

TTF_Font *font;

//HEBRA RECUPERACION
SDL_Thread *hebra_1;
//HEBRA MEMORIA
SDL_Thread *hebra_Mem;
//HEBRA RENDER
SDL_Thread *hebra_Render;
//HEBRA PRDICTION
SDL_Thread *hebra_Pred;


void createEnvirontment();
void destroyAll();
void getEventSDL(playerDataType pDT);
void processLocalPlayer(int level);
void evalLocalPlayerAgainstEnv(DynamicPlayer *dPlayer);
int threadFunction( void* data );
void initSDLWindows();
void destroySDLWindows();
void processPlayerSession(EventMsg *msg);
void renderScenario();

void createShootElement(DynamicPlayer *player);

void sendPingAndResult();


Uint16 mapClient = 0;
Uint16 sessionClient = 0;

Uint16 numMsg = 0;

long serverSize = 0;
int lowTime = 0;

int indexElement = 0;

char *remoteHost = REMOTE_HOST;
Uint16 remport = REMOTE_PORT;
Uint16 port = LOCAL_PORT;
std::string remoteHostStr(remoteHost);


int threadFunction(void* ctx){
    QueueManager *qM = (QueueManager*)ctx;
    //qM->runRemoteData();
    qM->remoteRemoteProcessData();
    return 0;
};


int threadFunctionPred(void* ctx){
    PredictionEngine *pE = (PredictionEngine *)ctx;
    pE->processPredictionIter();
    return 0;
}


//MAIN
int main (int argc, char *argv[])
{
   logger = new LogEngine();
   logger->deleteLogFile();
   logger->startUp(1,0);
   logger->printLogFlag();
   logger->info("================ [SSNETWORKMANAGER-CLIENT - INI] ================");

   lowTime = 0;

   std::cout << "\r\n Enter remote host SSNETWORKMANAGER-CLIENT (IP v4 p.j 127.0.0.1): <push ENTER at the end> ";
   getline(std::cin, remoteHostStr);
   logger->info("[SSNETWORKMANAGER::Main] OPEN REMOTE HOST (%s)",remoteHostStr.c_str());
   //std::string remoteHostStr(remoteHost);

   std::cout << "\r\n Enter remote port SSNETWORKMANAGER-CLIENT: ";
   std::cin >> remport;
   logger->info("[SSNETWORKMANAGER::Main] OPEN REMOTE PORT (%d)",remport);

   std::cout << "\r\nEnter local port SSNETWORKMANAGER-CLIENT: ";
   std::cin >> port;

   logger->info("[SSNETWORKMANAGER::Main] OPEN PORT (%d)",port);


   std::cout << "\r\nEnter local map SSNETWORKMANAGER-CLIENT[1-2]: ";
   std::cin >> mapClient;

   logger->info("[SSNETWORKMANAGER::Main] OPEN MAP (%d)",mapClient);

   std::cout << "\r\nEnter local session SSNETWORKMANAGER-CLIENT[1-2]: ";
   std::cin >> sessionClient;

   logger->info("[SSNETWORKMANAGER::Main] OPEN SESSION (%d)",sessionClient);


   cond = SDL_CreateCond();

   createEnvirontment();
   initSDLWindows();

   //, remoteHostStr.c_str(), remport+1, port+1
   nClientUDP->initCommunicationUDP(remoteHost, remport, port, remport+1, port+1);

   nClientUDP->establishCommunicationUDP();
   nClientUDP->getListActiveSessions();

   int attemps = 100;
   bool DONE = false;
   playerDataType pDT;

   nClientUDP->registerToActiveSession(mapClient, sessionClient);

   while ((attemps >= 0) && (!DONE)){
        EventMsg *responseMsg =  nClientUDP->getMsgFromServer();

       if (responseMsg->getTypeMsg() == TRAMA_ACK_SESSION){
            uint16_t CRC16FromServer = responseMsg->getCRC16();
            uint16_t CRC16Calculated = UtilsProtocol::calculateCRC16_CCITT((const unsigned char *)responseMsg->serializeMsg().c_str(),responseMsg->serializeMsg().size());
            logger->debug("[SSNETWORKMANAGER::MAIN] CRC TRAMA_ACK_SESSION SENDTRAMA[%d] GETTRAMA[%d] COMM FROM SERVER [%d] COMM FROM CLIENT [%d]",responseMsg->getTramaSend(),responseMsg->getTramaGet(),CRC16FromServer,CRC16Calculated);
            pDT = responseMsg->getPlayerDataType();
            logger->debug("[SSNETWORKMANAGER::MAIN] SESSION PLAYER Map:%d Session:%d IdPlayer:%d lvl:%d pos:(%f,%f) width:%d, height:%d",
                          pDT.actMap,
                          pDT.session,
                          pDT.idPlayer,
                          pDT.lvl,
                          pDT.x_pos,
                          pDT.y_pos,
                          pDT.width,
                          pDT.heigth);

            if ((pDT.actMap == 0) || (pDT.session == 0) || (pDT.idPlayer == 0)){
                logger->error("[SSNETWORKMANAGER::MAIN] error al generar el idSession");
                attemps--;
                SDL_Delay(100);
                //delete nClientUDP;
                //exit(-1);
            }else{
                DynamicPlayer *player = mem->getActPlayer(mem->getPlayerIndex());
                player->setDynamicPlayer(pDT);
                mem->setActPlayer(mem->getPlayerIndex(),player);

                player = ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1));
                player->setDynamicPlayer(pDT);
                sub->setObserver(mem->getPlayerIndex()-1,player);
                DONE = true;
            }

       }else if (responseMsg->getTypeMsg() == TRAMA_NACK_SESSION){
           uint16_t CRC16FromServer = responseMsg->getCRC16();
           uint16_t CRC16Calculated = UtilsProtocol::calculateCRC16_CCITT((const unsigned char *)responseMsg->serializeMsg().c_str(),responseMsg->serializeMsg().size());
           logger->debug("[SSNETWORKMANAGER::MAIN] CRC TRAMA_NACK_SESSION SENDTRAMA[%d] GETTRAMA[%d] COMM FROM SERVER [%d] COMM FROM CLIENT [%d]",responseMsg->getTramaSend(),responseMsg->getTramaGet(),CRC16FromServer,CRC16Calculated);
           answerType aType = responseMsg->getAnswerType();
           logger->warn("[SSNETWORKMANAGER::MAIN] NACK::RESULT [%d]",aType.result);
           attemps--;
           SDL_Delay(100);
           //delete nClientUDP;
           //exit(-1);
       }else if (responseMsg->getTypeMsg() == TRAMA_SND_ORDER_TO_SERVER){
           msgType mT = responseMsg->getMsgType();
           if (mT.msgTypeID == TYPE_MSG_FROM_SERVER){
               logger->debug("[SSNETWORKMANAGER::MAIN] MSG FROM SERVER [%s]",mT.msg);
               mem->push(responseMsg);
               attemps--;
               SDL_Delay(100);
           }

       }else if (responseMsg->getTypeMsg() == TRAMA_NULL){
            logger->warn("[SSNETWORKMANAGER::MAIN] RESULT NULL");
            attemps--;
            SDL_Delay(100);
            //delete nClientUDP;
            //exit(-1);
       }else{
            logger->warn("[SSNETWORKMANAGER::MAIN] PACKET NOT RECOGNIZED");
            attemps--;
            SDL_Delay(100);
       }
   }

   if (DONE){
      sendPingAndResult();
      getEventSDL(pDT);
   }

   destroySDLWindows();
   destroyAll();


   logger->info("================ [SSNETWORKMANAGER-CLIENT - END] ================");
   return 0;
}

void sendPingAndResult(){
    resultPingType serverSize = nClientUDP->sendPingAndResult(mapClient,
                                                              sessionClient,
                                                              ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1))->getIndexPlayer());
    logger->info("[SSNETWORKMANAGER::GETIDPLAYER] GET SERVER TIMEMARK QOS [%d] SERVER INDEX [%d]", serverSize.millisping, serverSize.indexAuthServer);
    mem->setSizeTimeServer(serverSize.millisping);
    mem->setTimeStampServer(serverSize.indexAuthServer);
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

    //nClient = new NetworkClient(logger);
    nClientUDP = new NetworkClientUDP(logger);

    nClock = new ClockEngine();

    coll = new CollisionEntities(mem,logger);
    aEnt = new AnimationEntities(mem,logger);
    iAEnt = new IAEntities(mem,logger);

    pEngine = new PredictionEngine(logger,mem,coll,aEnt,iAEnt); //prediction Engine.

    DynamicPlayer *player_1 = new DynamicPlayer(logger,1, nClientUDP);
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
    DynamicEntity *DynElem_1_1 = new DynamicEntity(logger); DynElem_1_1->setActLevel(1); DynElem_1_1->setIDDE(14); DynElem_1_1->setEnabled(true); DynElem_1_1->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_1_1->setX(256); DynElem_1_1->setY(256); DynElem_1_1->setWidth(16); DynElem_1_1->setHeight(16);
    DynamicEntity *DynElem_2_1 = new DynamicEntity(logger); DynElem_2_1->setActLevel(1); DynElem_2_1->setIDDE(15); DynElem_2_1->setEnabled(true); DynElem_2_1->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_2_1->setX(256); DynElem_2_1->setY(64); DynElem_2_1->setWidth(16); DynElem_2_1->setHeight(16);
    DynamicEntity *DynElem_3_1 = new DynamicEntity(logger); DynElem_3_1->setActLevel(1); DynElem_3_1->setIDDE(16); DynElem_3_1->setEnabled(true); DynElem_3_1->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_3_1->setX(64); DynElem_3_1->setY(256); DynElem_3_1->setWidth(16); DynElem_3_1->setHeight(16);

    mem->addDynElemMap_lvl_1(14,DynElem_1_1);
    mem->addDynElemMap_lvl_1(15,DynElem_2_1);
    mem->addDynElemMap_lvl_1(16,DynElem_3_1);

    DynamicEntity *DynElem_1_2 = new DynamicEntity(logger); DynElem_1_2->setActLevel(2); DynElem_1_2->setIDDE(17); DynElem_1_2->setEnabled(true); DynElem_1_2->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_1_2->setX(256); DynElem_1_2->setY(256); DynElem_1_2->setWidth(16); DynElem_1_2->setHeight(16);
    DynamicEntity *DynElem_2_2 = new DynamicEntity(logger); DynElem_2_2->setActLevel(2); DynElem_2_2->setIDDE(18); DynElem_2_2->setEnabled(true); DynElem_2_2->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_2_2->setX(256); DynElem_2_2->setY(64); DynElem_2_2->setWidth(16); DynElem_2_2->setHeight(16);
    DynamicEntity *DynElem_3_2 = new DynamicEntity(logger); DynElem_3_2->setActLevel(2); DynElem_3_2->setIDDE(19); DynElem_3_2->setEnabled(true); DynElem_3_2->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_3_2->setX(64); DynElem_2_2->setY(256); DynElem_3_2->setWidth(16); DynElem_3_2->setHeight(16);

    mem->addDynElemMap_lvl_2(17,DynElem_1_2);
    mem->addDynElemMap_lvl_2(18,DynElem_2_2);
    mem->addDynElemMap_lvl_2(19,DynElem_3_2);

    DynamicEntity *DynElem_1_3 = new DynamicEntity(logger); DynElem_1_3->setActLevel(3); DynElem_1_3->setIDDE(20); DynElem_1_3->setEnabled(true); DynElem_1_3->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_1_3->setX(256); DynElem_1_3->setY(256); DynElem_1_3->setWidth(16); DynElem_1_3->setHeight(16);
    DynamicEntity *DynElem_2_3 = new DynamicEntity(logger); DynElem_2_3->setActLevel(3); DynElem_2_3->setIDDE(21); DynElem_2_3->setEnabled(true); DynElem_2_3->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_2_3->setX(256); DynElem_2_3->setY(64); DynElem_2_3->setWidth(16); DynElem_2_3->setHeight(16);
    DynamicEntity *DynElem_3_3 = new DynamicEntity(logger); DynElem_3_3->setActLevel(3); DynElem_3_3->setIDDE(22); DynElem_3_3->setEnabled(true); DynElem_3_3->setTypeId(TYPE_ACTIVEOTHER_ELEMENT); DynElem_3_3->setX(64); DynElem_3_3->setY(256); DynElem_3_3->setWidth(16); DynElem_3_3->setHeight(16);

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




void createShootElement(DynamicPlayer *player){

    DynamicEntity *DynElem_aux = new DynamicEntity(logger);
    DynElem_aux->setActLevel(1);

    int playerID = (player->getIndexPlayer() * 100) + indexElement;

    DynElem_aux->setIDDE(playerID);
    DynElem_aux->setEnabled(true);
    DynElem_aux->setTypeId(TYPE_ACTIVEOTHER_ELEMENT);
    DynElem_aux->setActMap(mapClient);
    DynElem_aux->setActSession(sessionClient);
    DynElem_aux->setX(player->getX()+player->getWidth()+2);
    DynElem_aux->setY(player->getY()+(player->getHeight()/2));
    DynElem_aux->setWidth(16);
    DynElem_aux->setHeight(16);

    if (player->getMapID() == 1){
        if (mem->getDynElemMapElem_lvl_1(playerID)==nullptr)
        {
            mem->addDynElemMap_lvl_1(playerID,DynElem_aux);
        }else{
            mem->getDynElemMapElem_lvl_1(playerID)->setDynamicEntity(DynElem_aux);
        }
    }else if (player->getMapID() == 2){
        if (mem->getDynElemMapElem_lvl_2(playerID)==nullptr)
        {
            mem->addDynElemMap_lvl_2(playerID,DynElem_aux);
        }else{
            mem->getDynElemMapElem_lvl_2(playerID)->setDynamicEntity(DynElem_aux);
        }
    }else{
        if (mem->getDynElemMapElem_lvl_3(playerID)==nullptr)
        {
            mem->addDynElemMap_lvl_3(playerID,DynElem_aux);
        }else{
            mem->getDynElemMapElem_lvl_3(playerID)->setDynamicEntity(DynElem_aux);
        }
    }


    logger->debug("[Main::createShootElement] Map[%d] Session[%d] created new element ID [%d] at (lvl:%d,x:%f,y:%f) width:%f height:%f",
                    player->getMapID(),
                    player->getSessionID(),
                    DynElem_aux->getIDDE(),
                    DynElem_aux->getActLevel(),
                    DynElem_aux->getX(),
                    DynElem_aux->getY(),
                    DynElem_aux->getWidth(),
                    DynElem_aux->getHeight());


    delete DynElem_aux;


    indexElement = indexElement + 1;

}





void destroyAll(){

    //nClient->closeClientSocket();

   delete coll;
   delete aEnt;
   delete iAEnt;

   //delete nClient;
   delete nClientUDP;

   delete mem;
   delete qMem;
   delete logger;

};


//PROCESS EVENTS
void getEventSDL(playerDataType pDT){

    SDL_Event event;

    bool DONE = false;
    bool PRESS = false;

    localActionType lATPlayer;
    msgType mType;
    OrderType oType;
    exitType eType;
    shotType sType;

    logger->info("MAIN -  EVENT_MSG] ACTIVATING QUEUE-MEM PROCESS");
    qMem = new QueueManager(logger,mem,nClientUDP,pEngine, pDT, cond, sub, window, render, font);
    hebra_1 = SDL_CreateThread(threadFunction,"QueueManager",qMem);
    hebra_Pred = SDL_CreateThread(threadFunctionPred,"PredManager",pEngine);


    long markSDL = 0;
    EventMsg *msg = NULL;
    float dX = 0;

    int indexCreateActiveElement = 0;
    int indexMovementElement = 0;


    while (!DONE){

        markSDL = SDL_GetTicks();

        while (SDL_PollEvent(&event)){
            switch (event.type){

                case SDL_WINDOWEVENT:
                    logger->debug("[MAIN - EVENT_MSG] WINDOWS EVENT");
                    if (event.window.event == SDL_WINDOWEVENT_CLOSE){

                        logger->debug("[WINDOWS EVENT CLOSE]");
                        eType.exitID =  TYPE_COMMAND_EXIT;
                        eType.idPlayer = ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1))->getIndexPlayer();
                        eType.actMap = mapClient;
                        eType.session = sessionClient;
                        eType.level = ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1))->getActLevel();
                        eType.x = 0.0f;
                        eType.y = 0.0f;
                        eType.reason = 0;

                        msg = new EventMsg(eType);
                        sub->setMsg(msg);
                        sub->notify(mem->getTimeStampServer());

                        qMem->setDONE(true);
                    }

                    break;

                case SDL_KEYDOWN:
                    logger->debug("[MAIN -  EVENT_MSG] KEY DOWN");

                    SDL_Keysym *keysym = &event.key.keysym;

                    if (keysym->sym == SDLK_LEFT){          //-> mover jugador actual a la izquierda
                        lATPlayer.idPlayer = ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1))->getIndexPlayer();
                        //mem->getActPlayer(mem->getPlayerIndex())->getIndexPlayer();
                        lATPlayer.typeMovement = LEFT;
                        lATPlayer._inc = 2.0;
                        lATPlayer._x = 0;
                        lATPlayer._y = 0;
                        lATPlayer.shot = 0;
                        lATPlayer._velocity = float(64) * (float(SDL_GetTicks()-dX)/1000.0f);
                        lATPlayer.oldWPN = 0;
                        lATPlayer.newWPN = 0;

                        dX = SDL_GetTicks();

                        logger->debug("[MAIN -  EVENT_MSG] SEND LEFT TO ACT PLAYER [%d]=REM_ID[%d]",mem->getPlayerIndex(),lATPlayer.idPlayer);
                        PRESS = true;
                    }

                    else if (keysym->sym == SDLK_RIGHT){    //-> mover jugador actual a la derecha

                        lATPlayer.idPlayer = ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1))->getIndexPlayer();
                        //mem->getActPlayer(mem->getPlayerIndex())->getIndexPlayer();
                        lATPlayer.typeMovement = RIGHT;
                        lATPlayer._inc = 2.0;
                        lATPlayer._x = 0;
                        lATPlayer._y = 0;
                        lATPlayer._velocity = float(64) * (float(SDL_GetTicks()-dX)/1000.0f);
                        lATPlayer.shot = 0;
                        lATPlayer.oldWPN = 0;
                        lATPlayer.newWPN = 0;

                        dX = SDL_GetTicks();

                        logger->debug("[MAIN -  EVENT_MSG] SEND RIGHT TO ACT PLAYER [%d]=REM_ID[%d]",mem->getPlayerIndex(),lATPlayer.idPlayer);

                        PRESS = true;
                    }

                    else if (keysym->sym == SDLK_UP){       //-> mover jugador actual arriba
                        lATPlayer.idPlayer = ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1))->getIndexPlayer();
                        //mem->getActPlayer(mem->getPlayerIndex())->getIndexPlayer();
                        lATPlayer.typeMovement = UP;
                        lATPlayer._inc = 2.0;
                        lATPlayer._x = 0;
                        lATPlayer._y = 0;
                        lATPlayer._velocity = float(64) * (float(SDL_GetTicks()-dX)/1000.0f);
                        lATPlayer.shot = 0;
                        lATPlayer.oldWPN = 0;
                        lATPlayer.newWPN = 0;

                        dX = SDL_GetTicks();

                        logger->debug("[MAIN -  EVENT_MSG] SEND UP TO ACT PLAYER[%d]=REM_ID[%d]",mem->getPlayerIndex(),lATPlayer.idPlayer);
                        PRESS = true;

                    }

                    else if (keysym->sym == SDLK_DOWN){     //-> mover jugador actual abajo
                        lATPlayer.idPlayer = ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1))->getIndexPlayer();
                        //mem->getActPlayer(mem->getPlayerIndex())->getIndexPlayer();
                        lATPlayer.typeMovement = DOWN;
                        lATPlayer._inc = 2.0;
                        lATPlayer._x = 0;
                        lATPlayer._y = 0;
                        lATPlayer._velocity = float(64) * (float(SDL_GetTicks()-dX)/1000.0f);;
                        lATPlayer.shot = 0;
                        lATPlayer.oldWPN = 0;
                        lATPlayer.newWPN = 0;

                        dX = SDL_GetTicks();

                        logger->debug("[MAIN -  EVENT_MSG] SEND DOWN TO ACT PLAYER[%d]=REM_ID[%d]",mem->getPlayerIndex(),lATPlayer.idPlayer);
                        PRESS = true;

                    }

                    else if (keysym->sym == SDLK_SPACE){
                        sType.shotID = TYPE_COMMAND_SHOOT;
                        sType.actMap = mapClient;
                        sType.session = sessionClient;
                        sType.idPlayer = ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1))->getIndexPlayer();
                        sType.ammo = 10;

                        logger->debug("[MAIN -  EVENT_MSG] SEND SHOOT TO ACT PLAYER[%d]=REM_ID[%d]",mem->getPlayerIndex(),sType.idPlayer);

                        if (indexCreateActiveElement < 10){
                            indexCreateActiveElement++;
                        }else{
                            //createShootElement(((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1)));
                            indexCreateActiveElement = 0;
                            msg = new EventMsg(sType);
                            sub->setMsg(msg);
                            sub->notify(mem->getTimeStampServer());
                        }
                    }

                    else if (keysym->sym == SDLK_w){
                        lATPlayer.idPlayer = ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1))->getIndexPlayer();
                        mem->getActPlayer(mem->getPlayerIndex())->getIndexPlayer();
                        lATPlayer.typeMovement = LVLUP;
                        lATPlayer._inc = 1.0;
                        lATPlayer._x = 0;
                        lATPlayer._y = 0;
                        lATPlayer._velocity = 0;
                        lATPlayer.shot = 0;
                        lATPlayer.oldWPN = 0;
                        lATPlayer.newWPN = 0;


                        logger->debug("[MAIN -  EVENT_MSG] SEND LEVELUP TO ACT PLAYER[%d]=REM_ID[%d]",mem->getPlayerIndex(),lATPlayer.idPlayer);
                        PRESS = true;
                    }

                    else if (keysym->sym == SDLK_s){
                        lATPlayer.idPlayer = ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1))->getIndexPlayer();
                        //mem->getActPlayer(mem->getPlayerIndex())->getIndexPlayer();
                        lATPlayer.typeMovement = LVLDOWN;
                        lATPlayer._inc = 1.0;
                        lATPlayer._x = 0;
                        lATPlayer._y = 0;
                        lATPlayer._velocity = 0;
                        lATPlayer.shot = 0;
                        lATPlayer.oldWPN = 0;
                        lATPlayer.newWPN = 0;


                        logger->debug("[MAIN -  EVENT_MSG] SEND LEVELDOWN TO ACT PLAYER[%d]=REM_ID[%d]",mem->getPlayerIndex(),lATPlayer.idPlayer);
                        PRESS = true;
                    }

                    else if (keysym->sym == SDLK_m){

                        mType.actMap = mapClient;
                        mType.session = sessionClient;
                        mType.originMsg = ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1))->getIndexPlayer();
                        mType.endMsg = 23;
                        mType.msgTypeID = TYPE_MSG_FROM_SERVER;

                        for(int i=0; i<SIZE_MSG; i++){
                            mType.msg[i] = '\0';
                        }

                        sprintf(mType.msg,"Msg - [%d] Hello [%d] from [%d]",numMsg,mType.endMsg,mType.originMsg);
                        logger->debug("[MAIN - EVENT_MSG] SEND MSG TO OTHER CLIENT SESSION [%s]",mType.msg);

                        msg = new EventMsg(mType);
                        sub->setMsg(msg);
                        sub->notify(mem->getTimeStampServer());
                        numMsg++;
                    }

                    else if (keysym->sym == SDLK_o){

                        oType.actMap = mapClient;
                        oType.session = sessionClient;
                        oType.height = 0;
                        oType.width = 0;
                        oType.level = 0;
                        oType.entityID = ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1))->getIndexPlayer();
                        oType.pos_x = 0.0f;
                        oType.pos_y = 0.0f;
                        oType.orderID = 0;
                        oType.orderType = 0;
                        oType.value = 0;

                        logger->debug("[MAIN - EVENT_MSG] SEND ORDER TO SERVER");

                        msg = new EventMsg(oType);
                        sub->setMsg(msg);
                        sub->notify(mem->getTimeStampServer());

                    }

                    else if (keysym->sym == SDLK_ESCAPE){   //-> salir de la aplicacion
                        logger->debug("[MAIN -  EVENT_MSG] ESCAPE KEY PRESSED");
                        DONE = true;
                        PRESS = true;
                    }

                    if (PRESS){
                        PRESS = false;

                        if (DONE){

                            eType.exitID =  TYPE_COMMAND_EXIT;
                            eType.idPlayer = ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1))->getIndexPlayer();
                            eType.actMap = mapClient;
                            eType.session = sessionClient;
                            eType.level = ((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1))->getActLevel();
                            eType.x = 0.0f;
                            eType.y = 0.0f;
                            eType.reason = 0;

                            msg = new EventMsg(eType);
                            sub->setMsg(msg);
                            sub->notify(mem->getTimeStampServer());

                            qMem->setDONE(true);

                            logger->warn("[MAIN -  EVENT_MSG] EXIT!!!! SSNETWORKMANAGER");
                        }else{
                            msg = new EventMsg(lATPlayer);
                            sub->setMsg(msg);
                            sub->notify(mem->getTimeStampServer());
                        }
                    }
                    break;
            }
        }

        try{
            processLocalPlayer(((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1))->getActLevel());
        }catch(...){
            logger->debug("[MAIN::getEventSDL] Exception when rendering element");
        }

        long sizeTimeServer = mem->getSizeTimeServer() * SIZE_REMOTE_ELEMS;
        logger->debug("[MAIN - EVENT_MSG] TIMEOUT SYSTEM [%d]",sizeTimeServer);
    }

    SDL_WaitThread(hebra_1, NULL );
    SDL_WaitThread(hebra_Pred, NULL);
}

//PROCESS ENVIRONMENT
void processLocalPlayer(int level){
    const Uint32 timeout = 10;
    evalLocalPlayerAgainstEnv((DynamicPlayer *)sub->getObserver(mem->getPlayerIndex()-1));
    renderScenario();
}

//COLISION, AI. ANIMACION LOCAL PLAYER
void evalLocalPlayerAgainstEnv(DynamicPlayer *dPlayer){
    bool isCollition = coll->isCollDynamicPlayer(dPlayer);
    if (!isCollition){
        aEnt->isAnimDynamicPlayer(dPlayer);
        iAEnt->isIADynamicPlayer(dPlayer);
    }
}


//RENDER

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

    //MESSAGES
    if (!mem->isEmpty()){


        SDL_Color yellow = {0xff, 0xff, 0x00, 0xff};

        EventMsg *inputMSG = mem->front();

        textSurface = TTF_RenderText_Solid( font, inputMSG->getMsgType().msg, yellow);
        textTexture = SDL_CreateTextureFromSurface( render, textSurface );

        SDL_Rect text;
        text.x = SCREEN_WIDTH - (SIZE_MSG*5) -10;
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

    logger->info("[SSNETWORKMANAGER::renderScenario]  Render Scenario -END");

};



