#ifndef GLRENDER_H_INCLUDED
#define GLRENDER_H_INCLUDED

#include "LogEngine.h"

class GLRender{

public:
    GLRender(LogEngine *_log){
        this->log = _log;
    }
    ~GLRender(){}
    void Run(){
        log->debug("GLRender::Run launch Renderize!!!");
    }
private:

LogEngine *log;



};

#endif // GLRENDER_H_INCLUDED
