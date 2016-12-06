#ifndef CONCURRENT_QUEUE_UDP_H_INCLUDED
#define CONCURRENT_QUEUE_UDP_H_INCLUDED

#include <queue>
#include <pthread.h>
#include "EventMsg.h"
#include <SDL_thread.h>

class Concurrent_queue_UDP
{

private:

    std::queue<EventMsg *> _queue_;

    SDL_mutex *push_mutex;
    SDL_mutex *pop_mutex;
    SDL_mutex *front_mutex;
    SDL_mutex *size_mutex;
    SDL_mutex *empty_mutex;
    SDL_cond *cond;


    /*
    pthread_mutex_t push_mutex;
    pthread_mutex_t pop_mutex;
    pthread_mutex_t front_mutex;
    pthread_mutex_t empty_mutex;
    pthread_cond_t cond;
    */


public:

    Concurrent_queue_UDP()
    {

        push_mutex = NULL;
        pop_mutex  = NULL;
        front_mutex  = NULL;
        empty_mutex  = NULL;
        size_mutex = NULL;
        cond  = NULL;

        push_mutex = SDL_CreateMutex();
        pop_mutex = SDL_CreateMutex();
        front_mutex = SDL_CreateMutex();
        empty_mutex = SDL_CreateMutex();
        size_mutex = SDL_CreateMutex();
        cond = SDL_CreateCond();


        /*
        pthread_mutex_init(&push_mutex, NULL);
        pthread_mutex_init(&pop_mutex, NULL);
        pthread_mutex_init(&front_mutex, NULL);
        pthread_mutex_init(&empty_mutex, NULL);
        pthread_cond_init(&cond, NULL);
        */
    }

    void push(EventMsg* data)
    {
        //pthread_mutex_lock(&push_mutex);
        SDL_LockMutex( push_mutex );
        _queue_.push(data);
        SDL_CondSignal( cond );
        SDL_UnlockMutex( push_mutex );

        //pthread_cond_signal(&cond);
        //pthread_mutex_unlock(&push_mutex);
    }

    EventMsg *front(){

        EventMsg *msg = NULL;

        SDL_LockMutex( front_mutex);
        //pthread_mutex_lock(&front_mutex);
        msg = _queue_.front();
        //pthread_mutex_unlock(&front_mutex);
        SDL_UnlockMutex( front_mutex);

        return msg;
    }

    int sizeQueue(){
        int sizeQ = 0;
        SDL_LockMutex(size_mutex);
        sizeQ = _queue_.size();
        SDL_UnlockMutex(size_mutex);
        return sizeQ;
    }


    bool isEmpty(){

        bool res = false;

        SDL_LockMutex(empty_mutex);
        //pthread_mutex_lock(&empty_mutex);
        res = (_queue_.size() == 0);
        //pthread_mutex_unlock(&empty_mutex);
        SDL_UnlockMutex(empty_mutex);

        return res;
    }

    void pop()
    {
        //pthread_mutex_lock(&pop_mutex);
        SDL_LockMutex(pop_mutex);

        while (_queue_.empty() == true)
        {
            //pthread_cond_wait(&cond, &pop_mutex);
            SDL_CondWait( cond, pop_mutex);
        }

        _queue_.pop();
        SDL_UnlockMutex(pop_mutex);

        //pthread_mutex_unlock(&pop_mutex);
    }
};

#endif // CONCURRENT_QUEUE_UDP_H_INCLUDED
