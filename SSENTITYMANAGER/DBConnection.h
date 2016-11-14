#ifndef DBCONNECTION_H_INCLUDED
#define DBCONNECTION_H_INCLUDED

#include "Stdafx.h"
#include "LogEngine.h"

class DBConnection{

public:

DBConnection(LogEngine *_logger){
    logger = _logger;
};

~DBConnection(){
};

void createConn();
void deleteConn();

char **queryConn(const char *query);

private:

LogEngine *logger;
sqlite3 *dbfile;
sqlite3_stmt *statement;
const char *zErrMsg;

};


#endif // DBCONNECTION_H_INCLUDED
