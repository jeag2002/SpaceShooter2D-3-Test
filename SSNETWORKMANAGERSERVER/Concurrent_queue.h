#ifndef CONCURRENT_QUEUE_H_INCLUDED
#define CONCURRENT_QUEUE_H_INCLUDED

#include <queue>
#include <pthread.h>
#include <SDL_net.h>

class Concurrent_queue
{

private:

    std::queue<TCPsocket *> _queue_;
    pthread_mutex_t push_mutex;
    pthread_mutex_t pop_mutex;
    pthread_cond_t cond;

public:

    Concurrent_queue()
    {
        pthread_mutex_init(&push_mutex, NULL);
        pthread_mutex_init(&pop_mutex, NULL);
        pthread_cond_init(&cond, NULL);
    }

    void push(TCPsocket* data)
    {
        pthread_mutex_lock(&push_mutex);

        _queue_.push(data);

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&push_mutex);
    }

    TCPsocket *front(){
        return _queue_.front();
    }

    bool isEmpty(){
        return _queue_.empty();
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


#endif // CONCURRENT_QUEUE_H_INCLUDED
