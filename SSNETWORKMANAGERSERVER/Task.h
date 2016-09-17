#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED

#include <pthread.h>

class Task{

public:

    enum State{
        UNITIALIZED = 0, //incializado
        REMOVED,         //en proceso de eliminarse
        RUNNING,         //en proceso
        PAUSED,          //parado
        ///////////////////////////////////////////////////////////////////////
        SUCCEED,         //finalizado correctamente
        FAILED,          //finalizado con fallos
        ABORTED,         //no creado
        //==> estos tres últimos pueden ser eliminados por el thread de limpieza.
    };

    Task(){};
    Task(State _m_state){m_state = _m_state;};
    ~Task(){};

    //FUNCIONES ESTADO TASK
    virtual void VOnInit()=0;
    virtual void VOnUpdate(unsigned long deltaMs)=0;
    virtual void VOnSuccess()=0;
    virtual void VOnFail()=0;
    virtual void VOnAbort()=0;

    //FUNCIONES FINALIZACION TASK
    inline void Succeed(){}
    inline void Fail(){};

    inline void Pause(){};
    inline void UnPause(){};

    //ESTADOS
    State GetState(){return m_state;}
    void setState(State _m_state){m_state = _m_state;}

    bool isAlive(){return ((m_state == RUNNING) || (m_state == PAUSED));}
    bool isDead(){return ((m_state == SUCCEED) || ( m_state == FAILED) || (m_state == ABORTED));}

    bool isRemoved(){return (m_state == REMOVED);}
    bool isPaused(){return (m_state == PAUSED); }

private:
    State m_state;
};

#endif // TASK_H_INCLUDED
