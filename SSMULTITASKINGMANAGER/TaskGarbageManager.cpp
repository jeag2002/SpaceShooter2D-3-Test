#include "TaskGarbageManager.h"

void TaskGarbageManager::Run(){
    if (sem_wait(&OKToBuyMilk)==0){
        pthread_mutex_lock(&lock);
        iThread = pthread_self();
        int i=0;
        sem_getvalue(&OKToBuyMilk,&i);
        log->debug("TaskGarbageManager:: PID %d CreateThread [%08x] - SEMAPHOR [%d]", getpid(), iThread, i);
        sem_post(&Remote);
        sem_post(&OKToBuyMilk);
        pthread_mutex_unlock(&lock);
    }

}



/*
void TaskGarbageManager::PrintLog(const std::string fmt, ...){
    if (sem_wait(&OKToBuyMilk)==0){
        pthread_mutex_lock(&lock);
        iThread = pthread_self();
        int i=0;
        sem_getvalue(&OKToBuyMilk,&i);

        va_list ap;
        char msg[SIZE];
        for(int i=0;i<SIZE; i++){msg[i]='\0';}

        va_start(ap, fmt);
        int size_msg = vsnprintf(msg, (sizeof(msg)/sizeof(*msg))-1, fmt.c_str(), ap);

        PrintLog("TaskGarbageManager:: PID %d [%08x] - SEMAPHOR [%d] - %s",getpid(),iThread,i, msg);
        sem_post(&Remote);
        sem_post(&OKToBuyMilk);
        pthread_mutex_unlock(&lock);
    }

}
*/
