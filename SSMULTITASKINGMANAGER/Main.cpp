/*

MULTITASKING

http://www.drdobbs.com/cpp/cooperative-multitasking-in-c/184408532
http://aigamedev.com/open/article/round-robin-multi-tasking/
http://collaboration.cmc.ec.gc.ca/science/rpn/biblio/ddj/Website/articles/DDJ/1991/9104/9104f/9104f.htm

https://libgdx.badlogicgames.com/features.html

http://www.gamedev.net/page/resources/_/technical/game-programming/enginuity-part-iv-r1973
http://www.drdobbs.com/cpp/cooperative-multitasking-in-c/184408532
http://aigamedev.com/open/article/round-robin-multi-tasking/
http://collaboration.cmc.ec.gc.ca/science/rpn/biblio/ddj/Website/articles/DDJ/1991/9104/9104f/9104f.htm

https://www.codehosting.net/blog/BlogEngine/post/Lightweight-Cooperative-Multitasking-in-C.aspx

https://www.reddit.com/r/gamedev/comments/2yew3p/parallelizing_the_naughty_dog_engine_using_fibers/
https://msdn.microsoft.com/en-us/library/ms682661.aspx

http://gamedev.stackexchange.com/questions/2116/multi-threaded-game-engine-design-resources

THREADING

http://gamedev.stackexchange.com/questions/2116/multi-threaded-game-engine-design-resources
http://www.gamasutra.com/view/feature/130873/threading_3d_game_engine_basics.php


*/

#include "Stdafx.h"
#include "TaskManager.h"
#include "TaskRemPlayer.h"
#include "TimerTask.h"
#include "TaskGarbageManager.h"
#include "TaskInputEvents.h"

#include "Subject.h"
#include "DynamicEntity.h"
#include "DynamicPlayer.h"
#include "MemManager.h"
#include "QueueManager.h"

#include "GLRender.h"

#include "CollisionEntities.h"
#include "AnimationEntities.h"
#include "IAEntities.h"

#include "LogEngine.h"

#define NUM_THREADS 7


pthread_t hebras[NUM_THREADS];

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t dataNotProduced = PTHREAD_COND_INITIALIZER;
pthread_cond_t dataNotConsumed = PTHREAD_COND_INITIALIZER;

sem_t sem_1;
sem_t sem_2;
sem_t sem_3;
sem_t sem_4;
sem_t sem_5;
sem_t sem_6;
sem_t sem_7;
sem_t sem_8;
sem_t sem_9;
sem_t sem_10;

MemManager *mem;
QueueManager *qMem;
Subject *sub;
GLRender *render;

TaskManager *managerTask_1;
TaskManager *managerTask_2;
TaskManager *managerTask_3;
TaskManager *managerTask_4;
TaskManager *managerTask_5;
TaskManager *managerTask_6;

SDL_TimerID timerID_1;
SDL_TimerID timerID_2;
SDL_TimerID timerID_3;

TaskRemPlayer *managerRemTask;
TimerTask *schRenderTask;
TimerTask *schRemPlayerTask;
TaskGarbageManager *managerGarbageTask;
TaskInputEvents *taskInputEvents;

CollisionEntities *coll;
AnimationEntities *aEnt;
IAEntities *iAEnt;
LogEngine *logger;

int index_data;

typedef struct{
    int roof;
    TaskManager *manager;
}threadType;

//crea los elementos iniciales que van a trabajar en el motor evolucionado.
void createEnvirontment();
//process
void processLocalPlayer();

void evalLocalPlayerAgainstEnv(DynamicPlayer *dPlayer);

//funcion mierder pthreads enemigos/elementos dinamicos
static void* execute_RunTaskManager(void* ctx);
static void* execute_RunRemTaskManager(void* ctx);
static void* execute_RunTimerManager(void* ctx);
static void* execute_RunInputEventManager(void* ctx);


void processTimerTask_1(int param);
void processTimerTask_2(int param);
//void processTimerTask_3(int param);

Uint32 my_callbackTimer1(Uint32 interval, void *param);
Uint32 my_callbackTimer2(Uint32 interval, void *param);
Uint32 my_callbackTimer3(Uint32 interval, void *param);

void loadEventMsg();
void loadRender();
void loadDoneMsg();

//delay wait for signal
void wait (int seconds);

//crea el vector de poles (genera dos threads que gestionan los enemigos/elementos activos; otro que gestiona la eliminación de elementos)
void createPoolThread();

//crea el timertask (genera el ritmo para: 1-actualizar los elementos remotos (); 2-mandar la señal de renderizacion )
//1-espera X tiempo a recoger info de network. Si no; se hace prediction en local
void createTimerTask();

//event SDL
void getEventSDL();

void destroyAll();

int main (int argc, char *argv[])
{
 logger = new LogEngine();
 logger->deleteLogFile();
 logger->startUp(1,0);
 logger->printLogFlag();
 logger->info("================ [SSMULTITASKINGMANAGER - INI] ================");
 timerID_1 = SDL_AddTimer(100, my_callbackTimer1, NULL);
 timerID_2 = SDL_AddTimer(200, my_callbackTimer2, NULL);
 timerID_3 = SDL_AddTimer(500, my_callbackTimer3, NULL);
 createEnvirontment();
 createPoolThread();
 //getEventSDL();
 logger->info("================ [SSMULTITASKINGMANAGER - END] ================");
 destroyAll();
 return 0;
}


void processLocalPlayer(){

    if (mem->getPlayerIndex()==1){
        evalLocalPlayerAgainstEnv(mem->getPlayer_1());
    }else if(mem->getPlayerIndex()==2){
        evalLocalPlayerAgainstEnv(mem->getPlayer_2());
    }else{
        evalLocalPlayerAgainstEnv(mem->getPlayer_3());
    }
}


void evalLocalPlayerAgainstEnv(DynamicPlayer *dPlayer){

    pthread_t iThread = pthread_self();

    bool isCollition = coll->isCollDynamicPlayer(dPlayer,iThread);

    if (!isCollition){
        aEnt->isAnimDynamicPlayer(dPlayer,iThread);
        iAEnt->isIADynamicPlayer(dPlayer,iThread);
    }
}

//get event SDL
void getEventSDL(){

    SDL_Event event;

    bool DONE = false;
    bool PRESS = false;

    while (!DONE){
        while (SDL_WaitEvent(&event)){
            switch (event.type){

                case SDL_KEYDOWN:
                    logger->debug("[MAIN -  EVENT_MSG] KEY DOWN");

                    SDL_Keysym *keysym = &event.key.keysym;

                    if (keysym->sym == SDLK_LEFT){          //-> mover jugador actual a la izquierda
                        sub->setMsg(new EventMsg(1,1.0f,mem->getPlayerIndex()));
                        logger->debug("[MAIN -  EVENT_MSG] SEND LEFT TO ACT PLAYER [%d]",mem->getPlayerIndex());
                        PRESS = true;
                    }

                    else if (keysym->sym == SDLK_RIGHT){    //-> mover jugador actual a la derecha
                        sub->setMsg(new EventMsg(2,1.0f,mem->getPlayerIndex()));
                        logger->debug("[MAIN -  EVENT_MSG] SEND RIGHT TO ACT PLAYER [%d]",mem->getPlayerIndex());
                        PRESS = true;
                    }

                    else if (keysym->sym == SDLK_UP){       //-> mover jugador actual arriba
                        sub->setMsg(new EventMsg(3,1.0f,mem->getPlayerIndex()));
                        logger->debug("[MAIN -  EVENT_MSG] SEND UP TO ACT PLAYER [%d]",mem->getPlayerIndex());
                        PRESS = true;
                    }

                    else if (keysym->sym == SDLK_DOWN){     //-> mover jugador actual abajo
                        sub->setMsg(new EventMsg(4,1.0f,mem->getPlayerIndex()));
                        logger->debug("[MAIN -  EVENT_MSG] SEND DOWN TO ACT PLAYER [%d]",mem->getPlayerIndex());
                        PRESS = true;
                    }

                    else if (keysym->sym == SDLK_a){        //-> cambiar jugador
                        logger->debug("[MAIN -  EVENT_MSG] CHANGE PLAYER. ACT PLAYER [%d]",mem->getPlayerIndex());
                        pthread_mutex_lock(&lock);
                        int indexPlayer = mem->getPlayerIndex();
                        int indexPlayer_new = indexPlayer + 1;
                        if (indexPlayer_new > 3){indexPlayer_new = 1;}
                        mem->setPlayerIndex(indexPlayer_new);
                        logger->debug("[MAIN -  EVENT_MSG] before player [%d] after player [%d]",indexPlayer,indexPlayer_new);
                        pthread_mutex_unlock(&lock);
                        PRESS = true;
                    }


                    else if (keysym->sym == SDLK_d){        //-> cambiar nivel
                        logger->debug("[MAIN -  EVENT_MSG] CHANGE LEVEL. ACT LEVEL [%d]",mem->getPlayerIndex());
                        pthread_mutex_lock(&lock);
                        int indexPlayer = mem->getPlayerIndex();
                        DynamicPlayer *player = mem->getActPlayer(indexPlayer);
                        int indexLevel = player->getActLevel();
                        int indexLevel_new = indexLevel + 1;
                        if (indexLevel_new > 3){indexLevel_new = 1;}
                        player->setActLevel(indexLevel_new);
                        mem->setActPlayer(indexPlayer, player);
                        mem->setRoofIndex(indexLevel_new);
                        logger->debug("[MAIN -  EVENT_MSG] player [%d] before level [%d] after level [%d]",indexPlayer,indexLevel,indexLevel_new);
                        pthread_mutex_unlock(&lock);
                        PRESS = true;
                    }

                    else if (keysym->sym == SDLK_ESCAPE){   //-> salir de la aplicacion
                        logger->debug("[MAIN -  EVENT_MSG] LOGOUT SSMULTITASKINGMANAGER!!!");
                        DONE = true;
                        PRESS = true;
                    }

                    if (PRESS){
                        sub->notify();
                        if (DONE){
                            //fin del proceso, mandamos signal a los thread para que paren.
                        }
                    }

                    break;
            }
        }
        processLocalPlayer();
    }

}

//anyade los elementos de prueba para luego trabajar con ellos.
void createEnvirontment(){

    sub = new Subject();
    mem = new MemManager();
    qMem = new QueueManager(logger);
    render = new GLRender(logger);

    DynamicPlayer *player_1 = new DynamicPlayer(logger,1); player_1->setActLevel(1); player_1->setX(0); player_1->setY(0);
    DynamicPlayer *player_2 = new DynamicPlayer(logger,2); player_2->setActLevel(1); player_2->setX(128); player_2->setY(128);
    DynamicPlayer *player_3 = new DynamicPlayer(logger,3); player_3->setActLevel(1); player_3->setX(256); player_3->setY(256);

    //jugadores
    mem->setPlayer_1(player_1);
    mem->setPlayer_2(player_2);
    mem->setPlayer_3(player_3);

    sub->attachObserver(player_1);
    sub->attachObserver(player_2);
    sub->attachObserver(player_3);


    //enemigos
    ///////////////////////////////
    DynamicEntity *enemy_1_1 = new DynamicEntity(logger,qMem); enemy_1_1->setActLevel(1); enemy_1_1->setIDDE(4);
    DynamicEntity *enemy_2_1 = new DynamicEntity(logger,qMem); enemy_2_1->setActLevel(1); enemy_2_1->setIDDE(5);
    DynamicEntity *enemy_3_1 = new DynamicEntity(logger,qMem); enemy_3_1->setActLevel(1); enemy_3_1->setIDDE(6);

    mem->setEnemies_lvl_1(enemy_1_1);
    mem->setEnemies_lvl_1(enemy_2_1);
    mem->setEnemies_lvl_1(enemy_3_1);

    DynamicEntity *enemy_1_2 = new DynamicEntity(logger,qMem); enemy_1_2->setActLevel(2); enemy_1_2->setIDDE(7);
    DynamicEntity *enemy_2_2 = new DynamicEntity(logger,qMem); enemy_2_2->setActLevel(2); enemy_2_2->setIDDE(8);
    DynamicEntity *enemy_3_2 = new DynamicEntity(logger,qMem); enemy_3_2->setActLevel(2); enemy_3_2->setIDDE(9);

    mem->setEnemies_lvl_2(enemy_1_2);
    mem->setEnemies_lvl_2(enemy_2_2);
    mem->setEnemies_lvl_2(enemy_3_2);

    DynamicEntity *enemy_1_3 = new DynamicEntity(logger,qMem); enemy_1_3->setActLevel(3); enemy_1_3->setIDDE(10);
    DynamicEntity *enemy_2_3 = new DynamicEntity(logger,qMem); enemy_2_3->setActLevel(3); enemy_2_3->setIDDE(11);
    DynamicEntity *enemy_3_3 = new DynamicEntity(logger,qMem); enemy_3_3->setActLevel(3); enemy_3_3->setIDDE(12);

    mem->setEnemies_lvl_3(enemy_1_3);
    mem->setEnemies_lvl_3(enemy_2_3);
    mem->setEnemies_lvl_3(enemy_3_3);
    ///////////////////////////////

    //elementos dinamicos
    ///////////////////////////////
    DynamicEntity *DynElem_1_1 = new DynamicEntity(logger,qMem); DynElem_1_1->setActLevel(1); DynElem_1_1->setIDDE(14);
    DynamicEntity *DynElem_2_1 = new DynamicEntity(logger,qMem); DynElem_2_1->setActLevel(1); DynElem_2_1->setIDDE(15);
    DynamicEntity *DynElem_3_1 = new DynamicEntity(logger,qMem); DynElem_3_1->setActLevel(1); DynElem_3_1->setIDDE(16);

    mem->setDynElem_lvl_1(DynElem_1_1);
    mem->setDynElem_lvl_1(DynElem_2_1);
    mem->setDynElem_lvl_1(DynElem_3_1);

    DynamicEntity *DynElem_1_2 = new DynamicEntity(logger,qMem); DynElem_1_2->setActLevel(2); DynElem_1_2->setIDDE(17);
    DynamicEntity *DynElem_2_2 = new DynamicEntity(logger,qMem); DynElem_2_2->setActLevel(2); DynElem_2_2->setIDDE(18);
    DynamicEntity *DynElem_3_2 = new DynamicEntity(logger,qMem); DynElem_3_2->setActLevel(2); DynElem_3_2->setIDDE(19);

    mem->setDynElem_lvl_2(DynElem_1_2);
    mem->setDynElem_lvl_2(DynElem_2_2);
    mem->setDynElem_lvl_2(DynElem_3_2);

    DynamicEntity *DynElem_1_3 = new DynamicEntity(logger,qMem); DynElem_1_3->setActLevel(3); DynElem_1_3->setIDDE(20);
    DynamicEntity *DynElem_2_3 = new DynamicEntity(logger,qMem); DynElem_2_3->setActLevel(3); DynElem_2_3->setIDDE(21);
    DynamicEntity *DynElem_3_3 = new DynamicEntity(logger,qMem); DynElem_3_3->setActLevel(3); DynElem_3_3->setIDDE(22);

    mem->setDynElem_lvl_3(DynElem_1_3);
    mem->setDynElem_lvl_3(DynElem_2_3);
    mem->setDynElem_lvl_3(DynElem_3_3);

    ///////////////////////////////
    //remote player
    ///////////////////////////////
    DynamicEntity *rem_player_1 = new DynamicEntity(logger,qMem); rem_player_1->setActLevel(1); rem_player_1->setIDDE(23);
    DynamicEntity *rem_player_2 = new DynamicEntity(logger,qMem); rem_player_2->setActLevel(1); rem_player_2->setIDDE(24);
    DynamicEntity *rem_player_3 = new DynamicEntity(logger,qMem); rem_player_3->setActLevel(1); rem_player_3->setIDDE(25);

    mem->setRemPlayer(rem_player_1);
    mem->setRemPlayer(rem_player_2);
    mem->setRemPlayer(rem_player_3);
    ///////////////////////////////

    mem->setRoofIndex(1);           //planta-1
    mem->setPlayerIndex(1);         //jugador-1

    coll = new CollisionEntities(mem,logger, lock, sem_1, sem_2);
    aEnt = new AnimationEntities(mem,logger, lock, sem_1, sem_2);
    iAEnt = new IAEntities(mem,logger, lock, sem_1, sem_2);

    index_data = 0;

    logger->debug("[MULTITASKING] -- SET VARIABLES");

};


void destroyAll(){


   SDL_RemoveTimer(timerID_1);
   SDL_RemoveTimer(timerID_2);
   SDL_RemoveTimer(timerID_3);

   delete sub;
   delete mem;
   delete qMem;
   delete render;

   delete managerTask_1;
   delete managerTask_2;
   delete managerTask_3;
   delete managerTask_4;
   delete managerTask_5;
   delete managerTask_6;

   delete managerRemTask;
   delete schRenderTask;
   delete schRemPlayerTask;
   delete managerGarbageTask;
   delete taskInputEvents;

   delete coll;
   delete aEnt;
   delete iAEnt;
   delete logger;
};

//THREADS
//////////////////////////////////////////////////////
static void* execute_RunRemTaskManager(void* ctx){
    TaskRemPlayer *cptr = (TaskRemPlayer *)ctx;
    cptr->Run();
}
/////////////////////////////////////////////////////////////

//FUNCION THREADS TIMERS (MENSAJE ACTUALIZACION JUGADORES REMOTOS +  RENDERIZADO)
/////////////////////////////////////////////////////////////
static void* execute_RunTimerManager(void* ctx){
    TimerTask *cptr = (TimerTask *)ctx;
    cptr->Run();
}

/*
void processTimerTask_1(){
    pthread_mutex_lock(&lock);
    logger->debug("[MAIN]Processing TimerTask_1");
    EventMsg *msg = new EventMsg(5,0.0,0);
    logger->debug("[MAIN]Send Act Message");
    qMem->setMessageOutput(msg);
    pthread_mutex_unlock(&lock);
}


void processTimerTask_2(){
    pthread_mutex_lock(&lock);
    logger->debug("[MAIN]Processing TimerTask_2");
    render->Run();
    pthread_mutex_unlock(&lock);
}
*/

/*
void wait (int seconds){
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}

void processTimerTask_1(int param){
    wait(1);
    loadEventMsg();
    signal(SIGINT,processTimerTask_1);
    raise(SIGINT);

}

void processTimerTask_2(int param){
    wait(2);
    loadRender();
    signal(SIGILL,processTimerTask_2);
    raise(SIGILL);
}
*/



void loadEventMsg(){
    pthread_mutex_lock(&lock);
    struct timespec ts;
    ts.tv_sec = 100 / 1000;
    ts.tv_nsec = (100 % 1000) * 1000000;
    pthread_cond_timedwait(&dataNotConsumed, &lock, &ts);
    logger->debug("[MAIN -  TIMER_1] Wait consumers signals");
    if (!qMem->isEmptyMessageOutput()){qMem->popMessageOutputQueue();}
    EventMsg *msg = new EventMsg(5,0.0,0,index_data);
    qMem->setMessageOutput(msg);
    logger->debug("[MAIN -  TIMER_1] Send ACT MSG [%d] index [%d]",msg->getTypeMsg(),index_data);
    index_data=index_data+1;
    logger->debug("[MAIN -  TIMER_1] Broadcasting Produced");
    pthread_cond_broadcast(&dataNotProduced);
    pthread_mutex_unlock(&lock);
}

void loadRender(){
    logger->debug("[MAIN -  TIMER_2] Render");
    render->Run();
}


void loadDoneMsg(){

    pthread_mutex_lock(&lock);
    struct timespec ts;
    ts.tv_sec = 100 / 1000;
    ts.tv_nsec = (100 % 1000) * 1000000;
    pthread_cond_timedwait(&dataNotConsumed, &lock, &ts);
    logger->debug("[MAIN -  TIMER_3] Wait consumers signals");
    if (!qMem->isEmptyMessageOutput()){qMem->popMessageOutputQueue();}
    EventMsg *msg = new EventMsg(6,0.0,0,index_data);
    qMem->setMessageOutput(msg);
    logger->debug("[MAIN -  TIMER_3] Send DONE MSG [%d] index [%d]",msg->getTypeMsg(),index_data);
    index_data=index_data+1;
    logger->debug("[MAIN -  TIMER_3] Broadcasting Produced");
    pthread_cond_broadcast(&dataNotProduced);
    pthread_mutex_unlock(&lock);


}


Uint32 my_callbackTimer1(Uint32 interval, void *param){
    loadEventMsg();
    return interval;
}

Uint32 my_callbackTimer2(Uint32 interval, void *param){
    loadRender();
    return interval;
}

Uint32 my_callbackTimer3(Uint32 interval, void *param){
    loadDoneMsg();
    return 0;
}

//////////////////////////////////////////////////////////////

//FUNCION THREAD GARBAGE (ELIMINACION ELEMENTOS )
//FUNCION THREADS COOPERATIVE MULTITASKING (ENEMIGOS +  ELEMENTOS DINAMICOS)
/////////////////////////////////////////////////////////////
static void* execute_RunTaskManager(void* ctx) {
    threadType* cptr = (threadType *)ctx;

    if(cptr->roof == 1){
       cptr->manager->Run(mem->getEnemies_lvl_1(),1,cptr->roof);
    }else if (cptr->roof == 2){
       cptr->manager->Run(mem->getEnemies_lvl_2(),2,cptr->roof);
    }else if (cptr->roof == 3){
       cptr->manager->Run(mem->getEnemies_lvl_3(),3,cptr->roof);
    }else if (cptr->roof == 4){
       cptr->manager->Run(mem->getDynElem_lvl_1(),1,cptr->roof);
    }else if (cptr->roof == 5){
       cptr->manager->Run(mem->getDynElem_lvl_2(),2,cptr->roof);
    }else{
       cptr->manager->Run(mem->getDynElem_lvl_3(),3,cptr->roof);
    }
    return NULL;
}
//////////////////////////////////////////////////////////

static void *execute_GarbageManager(void* ctx){
    TaskGarbageManager *cptr = (TaskGarbageManager *)ctx;
    cptr->Run();
}

static void* execute_RunInputEventManager(void* ctx){
    TaskInputEvents *cptr = (TaskInputEvents *)ctx;
    cptr->Run();
}


//ALTA POOL THREADS
//////////////////////////////////////////////////////////
void createPoolThread(){

    int res = sem_init(&sem_1,0,1);
    if (res < 0){
        logger->warn("Main::createPoolThread Semaphore initialization failed");;
        exit(-1);
    }

    res = sem_init(&sem_2,0,1);
    if (res < 0){
        logger->warn("Main::createPoolThread Semaphore initialization failed");;
        exit(-1);
    }


    res = sem_init(&sem_3,0,1);
    if (res < 0){
        logger->warn("Main::createPoolThread Semaphore initialization failed");;
        exit(-1);
    }

    /*

    res = sem_init(&sem_4,0,1);
    if (res < 0){
        logger->warn("Main::createPoolThread Semaphore initialization failed");;
        exit(-1);
    }

    res = sem_init(&sem_5,0,1);
    if (res < 0){
        logger->warn("Main::createPoolThread Semaphore initialization failed");;
        exit(-1);
    }

    res = sem_init(&sem_6,0,1);
    if (res < 0){
        logger->warn("Main::createPoolThread Semaphore initialization failed");;
        exit(-1);
    }

    res = sem_init(&sem_7,0,1);
    if (res < 0){
        logger->warn("Main::createPoolThread Semaphore initialization failed");;
        exit(-1);
    }

    res = sem_init(&sem_8,0,1);
    if (res < 0){
        logger->warn("Main::createPoolThread Semaphore initialization failed");;
        exit(-1);
    }

    res = sem_init(&sem_9,0,1);
    if (res < 0){
        logger->warn("Main::createPoolThread Semaphore initialization failed");;
        exit(-1);
    }

    res = sem_init(&sem_10,0,1);
    if (res < 0){
        logger->warn("Main::createPoolThread Semaphore initialization failed");;
        exit(-1);
    }
    */



    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        logger->warn("Main::createPoolThread mutex init failed");
        exit(-1);
    }


    managerTask_1 = new TaskManager(logger,mem,qMem,lock, dataNotProduced, dataNotConsumed, sem_1,sem_2);
    managerTask_2 = new TaskManager(logger,mem,qMem,lock, dataNotProduced, dataNotConsumed, sem_2,sem_3);
    taskInputEvents = new TaskInputEvents(logger,mem,qMem,sub,lock, dataNotProduced, dataNotConsumed, sem_3, sem_1);

    //managerTask_3 = new TaskManager(logger,mem,qMem,lock,sem_3,sem_4);

    //managerTask_4 = new TaskManager(logger,mem,qMem,lock,sem_4,sem_5);
    //managerTask_5 = new TaskManager(logger,mem,qMem,lock,sem_5,sem_6);
    //managerTask_6 = new TaskManager(logger,mem,qMem,lock,sem_6,sem_7);

    //managerRemTask = new TaskRemPlayer(logger,mem,qMem,lock,sem_7,sem_8);
    //managerGarbageTask = new TaskGarbageManager(logger,mem,lock,sem_8,sem_9);

    //managerRemTask = new TaskRemPlayer(logger,mem,qMem,lock,sem_3,sem_1);
    //managerGarbageTask = new TaskGarbageManager(logger,mem,lock,sem_5,sem_6);


    //void (*timeFunct_1_ptr)(void);
    //void (*timeFunct_2_ptr)(void);

    //timeFunct_1_ptr = &processTimerTask_1;
    //timeFunct_2_ptr = &processTimerTask_2;

    //TimerTask *tTask_1 = new TimerTask(timeFunct_1_ptr,long(20000),logger,qMem,lock,sem_9,sem_10);
    //TimerTask *tTask_2 = new TimerTask(timeFunct_2_ptr,long(5000),logger,qMem,lock,sem_10,sem_1);

    //TimerTask *tTask_1 = new TimerTask(timeFunct_1_ptr,long(20000),logger,qMem,lock,sem_4,sem_5);
    //TimerTask *tTask_2 = new TimerTask(timeFunct_2_ptr,long(5000),logger,qMem,lock,sem_5,sem_1);

    //TimerTask *tTask_1 = new TimerTask(timeFunct_1_ptr,long(20000),logger,qMem,lock,sem_3,sem_4);
    //TimerTask *tTask_2 = new TimerTask(timeFunct_2_ptr,long(5000),logger,qMem,lock,sem_4,sem_1);


    //ENEMIES
    //////////////////////////////////////////////////////
    //pthread_t t1, t2, t3;
    threadType dat_1,dat_2,dat_3;

    dat_1.roof = 1;
    dat_1.manager = managerTask_1;
    pthread_create(&hebras[0],NULL,execute_RunTaskManager,&dat_1);
    SDL_Delay(10);

    dat_2.roof = 2;
    dat_2.manager = managerTask_2;
    pthread_create(&hebras[1],NULL,execute_RunTaskManager,&dat_2);
    SDL_Delay(10);

    pthread_create(&hebras[2],NULL,execute_RunInputEventManager,taskInputEvents);
    SDL_Delay(10);

    //dat_3.roof = 3;
    //dat_3.manager = managerTask_3;
    //pthread_create(&hebras[2],NULL,execute_RunTaskManager,&dat_3);
    //SDL_Delay(10);
    //////////////////////////////////////////////////////

    //DYN ELEMENTS
    //////////////////////////////////////////////////////
    //pthread_t t4, t5, t6;
    //threadType dat_4,dat_5,dat_6;

    //dat_4.roof = 4;
    //dat_4.manager = managerTask_4;
    //pthread_create(&hebras[3],NULL,execute_RunTaskManager,&dat_4);
    //SDL_Delay(10);

    //dat_5.roof = 5;
    //dat_5.manager = managerTask_5;
    //pthread_create(&hebras[4],NULL,execute_RunTaskManager,&dat_5);
    //SDL_Delay(10);

    //dat_6.roof = 6;
    //dat_6.manager = managerTask_6;
    //pthread_create(&hebras[5],NULL,execute_RunTaskManager,&dat_6);
    //SDL_Delay(10);
    //////////////////////////////////////////////////////

    //REMOTE PLAYERS
    //////////////////////////////////////////////////////
    //pthread_create(&hebras[2],NULL,execute_RunRemTaskManager,managerRemTask);
    //SDL_Delay(10);
    //////////////////////////////////////////////////////

     //GARBAGE COLLECTOR
    //////////////////////////////////////////////////////
    //pthread_create(&hebras[4],NULL,execute_GarbageManager,managerGarbageTask);
    //SDL_Delay(10);
    //////////////////////////////////////////////////////


    //TIMER
    //////////////////////////////////////////////////////
    //pthread_create(&hebras[2],NULL,execute_RunTimerManager,tTask_1);
    //SDL_Delay(10);


    //pthread_create(&hebras[3],NULL,execute_RunTimerManager,tTask_2);
    //SDL_Delay(10);
    //////////////////////////////////////////////////////

    pthread_join(hebras[0],0);
    pthread_join(hebras[1],0);
    pthread_join(hebras[2],0);
    //pthread_join(hebras[3],0);

    pthread_mutex_destroy(&lock);
    sem_destroy(&sem_1);
    sem_destroy(&sem_2);
    sem_destroy(&sem_3);
    //sem_destroy(&sem_4);


    /*
    for (int i=0; i<NUM_THREADS; i++){
        pthread_join(hebras[i],0);
    }

    pthread_mutex_destroy(&lock);
    sem_destroy(&sem_1);
    sem_destroy(&sem_2);
    sem_destroy(&sem_3);
    sem_destroy(&sem_4);
    sem_destroy(&sem_5);
    sem_destroy(&sem_6);
    sem_destroy(&sem_7);
    sem_destroy(&sem_8);
    sem_destroy(&sem_9);
    sem_destroy(&sem_10);
    */

    logger->debug("[MULTITASKING] -- POOL THREAD");
};
//////////////////////////////////////////////////////
