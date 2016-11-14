
/*
LOGENGINE.H MOTOR DE LOGS DE LA APLICACION
*/

#include "Stdafx.h"

#ifndef LOGMANAGER_H_INCLUDED
#define LOGMANAGER_H_INCLUDED

#define TO_FILE 0
#define TO_FILE_COUT 1

#define DEBUG_LOG 1
#define INFO_LOG 2
#define WARN_LOG 3
#define ERROR_LOG 4
#define FATAL_LOG 5

#define SIZE 3000
#define SIZE_SCREEN 2050
#define SIZE_BUFFER 3580
#define SIZE_TIME 50

#define DEFAULT_FILE "DEFAULT.log"

class LogEngine{

    public:

       /*0=all, 1=debug, 2=info, 3=warn, 4=error, 5=fatal*/
       LogEngine(){
           level = 0;
           typeLog = 0;
           pointer = 0;
           for(int i=0; i<SIZE_BUFFER; i++){buffer_logs[i]='\0';}
           //pthread_mutex_init(&push_log, NULL);
           push_log = SDL_CreateMutex();
           ownFile = DEFAULT_FILE;

        };

       void deleteLogFile();
       void startUp(int level, int typeLog);
       void shutDown();

       void printLogFlag(){
          this->info("LogEngine - INITIALIZED! to %s Channel %s",tagLevel(level).c_str(), toChannel(typeLog).c_str());
       };

       void setOwnFile(char *_file){ownFile = _file;}
       void debug(const std::string fmt, ...);
       void info(const std::string fmt, ...);
       void warn(const std::string fmt, ...);
       void error(const std::string fmt, ...);


    private:

       int level;
       int typeLog;
       void message(int type, const char *msg);
       char buffer_logs[SIZE_BUFFER];
       char *ownFile;
       //http://www.cplusplus.com/reference/cstdio/snprintf/
       int pointer;
       std::string getDateTime(void);
       std::string tagLevel(int level);
       std::string toChannel(int level);

        SDL_mutex *push_log;

};

#endif // LOGMANAGER_H_INCLUDED

/*
(+)1.0.00
1-un thread
2-cuatro niveles de log.

(Pensar para futuras iteraciones)
1-Soporte para mas de un thread
2-inserci�n de logs por bloques en vez de por acci�n

(+)1.1.00
1-Insertar los logs por bloques.
(No implementado): acceso de los logs de forma restringida
http://www.cplusplus.com/reference/mutex/mutex/lock/
Evaluar si merece la pena implementar una gesti�n desatendida de los logs.

(+)1.2.00
1-Motor de logs Thread Safety; utilizando Mutex.
2-Canal estandar de salida + Canal por fichero

*/
