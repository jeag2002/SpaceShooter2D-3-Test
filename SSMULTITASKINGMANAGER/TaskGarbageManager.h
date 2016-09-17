#ifndef TASKGARBAGEMANAGER_H_INCLUDED
#define TASKGARBAGEMANAGER_H_INCLUDED

#include "Stdafx.h"
#include "MemManager.h"
#include "LogEngine.h"

#define SIZE 500

class TaskGarbageManager{

public:

TaskGarbageManager(LogEngine *_log, MemManager *_mem, pthread_mutex_t _lock, sem_t _OKToBuyMilk, sem_t _Remote){
    mem = _mem;
    log = _log;
    lock = _lock;
    OKToBuyMilk = _OKToBuyMilk;
    Remote = _Remote;
}

~TaskGarbageManager(){}
void Run();
//void PrintLog(const std::string fmt, ...);

private:

MemManager *mem;
LogEngine *log;
pthread_t iThread;
pthread_mutex_t lock;
sem_t OKToBuyMilk;
sem_t Remote;

};

#endif // TASKGARBAGEMANAGER_H_INCLUDED
