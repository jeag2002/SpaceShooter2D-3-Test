/*
http://disi.unitn.it/~abeni/RTOS/periodic_threads-1.c
*/


#ifndef TIMERTASK_H_INCLUDED
#define TIMERTASK_H_INCLUDED

#include "Stdafx.h"
#include "LogEngine.h"
#include "QueueManager.h"

#define NSEC_PER_SEC 1000000000ULL

#define SIZE 500

class TimerTask{

public:

TimerTask(void(*compar)(void),long _milliseconds, LogEngine *_log, QueueManager *_qMem, pthread_mutex_t _lock, sem_t _OKToBuyMilk, sem_t _Remote){
    this->log = _log;
    this->qMem = _qMem;
    this->milliseconds = _milliseconds;
    this->data = compar;
    this->lock = _lock;
    this->OKToBuyMilk = _OKToBuyMilk;
    this->Remote = _Remote;
};

~TimerTask(){
};

void Run();
//void PrintLog(const std::string fmt, ...);

private:

pthread_t iThread;

long milliseconds;
LogEngine *log;
QueueManager *qMem;
void (*data)(void);
pthread_mutex_t lock;
sem_t OKToBuyMilk;
sem_t Remote;


};

#endif // TIMERTASK_H_INCLUDED
