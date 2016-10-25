#include "LogEngine.h"

std::string LogEngine::tagLevel(int level){

    std::string data;

    switch(level){
        case 1: data = "[DEBUG] "; break;
        case 2: data = "[INFO]  "; break;
        case 3: data = "[WARN]  "; break;
        case 4: data = "[ERROR] "; break;
        default:
                data = "[IDLE]  "; break;
    }
    return data;
}


std::string LogEngine::toChannel(int level){

    std::string data;

    switch(level){
        case 0: data = "[FILE] "; break;
        case 1: data = "[FILE][COUT] "; break;
        default:
                data = "[IDLE]  "; break;
    }

    return data;
}




void LogEngine::startUp(int level, int typeLog){
    this->level = level;
    this->typeLog = typeLog;

}


void LogEngine::shutDown(){

}

void LogEngine::deleteLogFile(){

    int flag = 0;
    flag = remove(ownFile);

	if (flag!=0){
        printf("Error al borrar el fichero de log SSNETWORKMANAGERSERVER");
	}


}


std::string LogEngine::getDateTime(void){

  char buffer[SIZE_TIME];
  std::string output;
  time_t curtime;
  struct tm *loctime;

  curtime = time (NULL);
  loctime = localtime (&curtime);

  strftime (buffer, SIZE, "(%d/%m/%Y - %H:%M:%S) - ", loctime);

  output = buffer;

  return output;
}


void LogEngine::message(int type, const char *msg)
{
    std::string dateTime = getDateTime();
    FILE *f = fopen(ownFile, "a");

    if (f) {
        fprintf(f, "\n%s%s - %s",tagLevel(type).c_str(), dateTime.c_str(),msg);
        fclose(f);
    }

    char buffer [SIZE_SCREEN];
    int value = sprintf (buffer, "\n%s%s - %s", tagLevel(type).c_str(), dateTime.c_str(), msg);
    if ((value > 0) && (value < SIZE_SCREEN)){
        std::cout << buffer;
    }
}



/*
NO HABILITAR HASTA QUE SE IMPLEMENTE LOGICA DEL JUEGO (movimiento del jugador, enemigos y colisiones)
Almacenamiento en buffer registro actividad hasta que llena el buffer y se borra.

void LogEngine::message(int type, const char *msg)
{
    string dateTime = getDateTime();
    //insertamos los datos de logs en el buffer
    this->pointer = snprintf ( buffer_logs+this->pointer, SIZE_BUFFER-this->pointer, "\n%s%s - %s", tagLevel(type).c_str(), dateTime.c_str(),msg);

    //si llenamos el buffer, lo volcamos a fichero, y borramos.
    if (this->pointer == -1){
        FILE *f = fopen("data/Sin2DEng.log", "a");
        if (f) {
            fprintf(f, "%s",buffer_logs);
            fclose(f);
        }

        //borramos el buffer
        for(int i=0; i<SIZE_BUFFER; i++){buffer_logs[i]='\0';}
        this->pointer = 0;
        //insertamos el registro otra vez.
        this->pointer = snprintf ( buffer_logs, SIZE_BUFFER, "\n%s%s - %s", tagLevel(type).c_str(), dateTime.c_str(),msg);

    }
}
*/



void LogEngine::debug(const std::string fmt, ...){
     if (this->level <= DEBUG_LOG){

        SDL_LockMutex(push_log);
        //pthread_mutex_lock(&push_log);

        va_list ap;
        char msg[SIZE];

        va_start(ap, fmt);
        int size_msg = vsnprintf(msg, (sizeof(msg)/sizeof(*msg))-1, fmt.c_str(), ap);

        if ((size_msg > 0) && (size_msg < SIZE)){
            message(DEBUG_LOG, msg);
        }

        //pthread_mutex_unlock(&push_log);
        SDL_UnlockMutex(push_log);
    }
}


void LogEngine::info(const std::string fmt, ...){
    if (this->level <= INFO_LOG){

        SDL_LockMutex(push_log);
        //pthread_mutex_lock(&push_log);

        va_list ap;
        char msg[SIZE];

        va_start(ap, fmt);
        int size_msg = vsnprintf(msg, (sizeof(msg)/sizeof(*msg))-1, fmt.c_str(), ap);

        if ((size_msg > 0) && (size_msg < SIZE)){
            message(INFO_LOG, msg);
        }

        //pthread_mutex_unlock(&push_log);
        SDL_UnlockMutex(push_log);
    }
}


void LogEngine::warn(const std::string fmt, ...){
    if (this->level <= WARN_LOG){

        SDL_LockMutex(push_log);
        //pthread_mutex_lock(&push_log);

        va_list ap;
        char msg[SIZE];

        va_start(ap, fmt);
        int size_msg = vsnprintf(msg, (sizeof(msg)/sizeof(*msg))-1, fmt.c_str(), ap);

        if ((size_msg > 0) && (size_msg < SIZE)){
            message(WARN_LOG, msg);
        }

        //pthread_mutex_unlock(&push_log);
        SDL_UnlockMutex(push_log);

    }
}


void LogEngine::error(const std::string fmt, ...){
    if (this->level <= ERROR_LOG){

        SDL_LockMutex(push_log);
        //pthread_mutex_lock(&push_log);

        va_list ap;
        char msg[SIZE];

        va_start(ap, fmt);
        int size_msg = vsnprintf(msg, (sizeof(msg)/sizeof(*msg))-1, fmt.c_str(), ap);

        if ((size_msg > 0) && (size_msg < SIZE)){
            message(ERROR_LOG, msg);
        }

        //pthread_mutex_unlock(&push_log);
        SDL_UnlockMutex(push_log);
    }
}
