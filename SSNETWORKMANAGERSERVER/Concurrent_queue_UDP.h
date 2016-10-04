#ifndef CONCURRENT_QUEUE_UDP_H_INCLUDED
#define CONCURRENT_QUEUE_UDP_H_INCLUDED

#include <queue>
#include <pthread.h>
#include "EventMsg.h"

class Concurrent_queue_UDP
{

private:

    std::queue<EventMsg *> _queue_;
    pthread_mutex_t push_mutex;
    pthread_mutex_t pop_mutex;
    pthread_mutex_t front_mutex;
    pthread_mutex_t empty_mutex;
    pthread_cond_t cond;

public:

    Concurrent_queue_UDP()
    {
        pthread_mutex_init(&push_mutex, NULL);
        pthread_mutex_init(&pop_mutex, NULL);
        pthread_mutex_init(&front_mutex, NULL);
        pthread_mutex_init(&empty_mutex, NULL);

        pthread_cond_init(&cond, NULL);
    }

    void push(EventMsg* data)
    {
        pthread_mutex_lock(&push_mutex);

        _queue_.push(data);

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&push_mutex);
    }

    EventMsg *front(){

        EventMsg *msg = NULL;

        pthread_mutex_lock(&front_mutex);
        msg = _queue_.front();
        pthread_mutex_unlock(&front_mutex);

        return msg;
    }

    bool isEmpty(){

        bool res = false;

        pthread_mutex_lock(&empty_mutex);
        res = (_queue_.size() == 0);
        pthread_mutex_unlock(&empty_mutex);

        return res;
    }

    void pop()
    {
        pthread_mutex_lock(&pop_mutex);

        while (_queue_.empty() == true)
        {
            pthread_cond_wait(&cond, &pop_mutex);
        }

        _queue_.pop();

        pthread_mutex_unlock(&pop_mutex);
    }
};

#endif // CONCURRENT_QUEUE_UDP_H_INCLUDED
