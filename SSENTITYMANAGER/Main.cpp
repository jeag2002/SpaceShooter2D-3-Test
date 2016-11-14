/*
crear una base de datos SQLite: https://www.sqlite.org/cli.html
acceder a una base de datos SQLite

acceder a base de datos. SQLite

http://www.codeproject.com/Tips/378808/Accessing-a-SQLite-Database-with-Cplusplus
*/

#include "Stdafx.h"
#include "LogEngine.h"
#include "DBConnection.h"
#include "MemManagerRes.h"
#include "EntityManager.h"
#include "ProfileEngine.h"


LogEngine *logger;
DBConnection *dbConn;
MemManagerRes *mMRes;
EntityManager *eManager;
ProfileEngine *pEngine;

void createEnvironment();
void destroyEnvironment();

int main (int argc, char *argv[])
{
   createEnvironment();
   logger->info("================ [SSENTITYMANAGER - INI] ================");
   ActorEntity *aEntity_1 = (ActorEntity *)eManager->getEntity(200);
   aEntity_1->setXPos(0.00);
   aEntity_1->setYPos(0.00);

   logger->info("GET ACTOR ENTITY 200 1 POS_X:%f POS_Y:%f LIVE:%d SHIELD:%d SCORE:%d",aEntity_1->getXPos(),aEntity_1->getYPos(),aEntity_1->getLive(),aEntity_1->getShield(),aEntity_1->getScore());



   ActorEntity *aEntity_2 = (ActorEntity *)eManager->getEntity(200);
   aEntity_2->setXPos(640.00);
   aEntity_2->setYPos(0.00);

   logger->info("GET ACTOR ENTITY 200 2 POS_X:%f POS_Y:%f LIVE:%d SHIELD:%d SCORE:%d",aEntity_2->getXPos(),aEntity_2->getYPos(),aEntity_2->getLive(),aEntity_2->getShield(),aEntity_2->getScore());

   ActorEntity *aEntity_3 = (ActorEntity *)eManager->getEntity(200);
   aEntity_3->setXPos(640.00);
   aEntity_3->setYPos(640.00);

   logger->info("GET ACTOR ENTITY 200 3 POS_X:%f POS_Y:%f LIVE:%d SHIELD:%d SCORE:%d",aEntity_3->getXPos(),aEntity_3->getYPos(),aEntity_3->getLive(),aEntity_3->getShield(),aEntity_3->getScore());



   //ActorEntity *aEntity_4 = (ActorEntity *)eManager->getEntity(200);
   //ActorEntity *aEntity_5 = (ActorEntity *)eManager->getEntity(200);
   //ActorEntity *aEntity_6 = (ActorEntity *)eManager->getEntity(200);


   logger->info("================ [SSENTITYMANAGER - FIN] ================");
   destroyEnvironment();
   return 0;
}



void createEnvironment(){
   logger = new LogEngine();
   logger->setOwnFile("TRAMACLIENT.log");
   logger->deleteLogFile();
   logger->startUp(DEBUG_DATA,0);
   logger->printLogFlag();

   mMRes = new MemManagerRes();
   dbConn = new DBConnection(logger);
   pEngine = new ProfileEngine(DEBUG_DATA);
   eManager = new EntityManager(dbConn, mMRes, logger, pEngine);
   dbConn->createConn();

   #ifdef PROFILING
   pEngine->setMsg("=============== PROFILING GENERAL STATE DATA INI ================");
   pEngine->printVirtualMemoryUsed();
   pEngine->printRAMMemoryUsed();
   pEngine->printCPUUsed();
   pEngine->setMsg("=============== PROFILING GENERAL STATE DATA FIN ================");
   #endif // NDEBUG

}


void destroyEnvironment(){

    dbConn->deleteConn();

    delete eManager;
    delete mMRes;
    delete dbConn;
    delete logger;
}


/*
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#include "sqlite3.h"
#define DB "data/sea.s3db"

bool isOpenDB = false;
sqlite3 *dbfile;



int main (int argc, char *argv[])
{
   if ( sqlite3_open(DB, &dbfile) == SQLITE_OK )
   {
		isOpenDB = true;
   }

   cout << "Connected Successful" << endl;

    sqlite3_stmt *statement;

	char *query = "select * from student";

	if ( sqlite3_prepare(dbfile, query, -1, &statement, 0 ) == SQLITE_OK )
	{
		int ctotal = sqlite3_column_count(statement);
		int res = 0;

		while ( 1 )

		{
			res = sqlite3_step(statement);

			if ( res == SQLITE_ROW )
			{
				for ( int i = 0; i < ctotal; i++ )
				{
					string s = (char*)sqlite3_column_text(statement, i);
					cout << s << " " ;
				}

				cout << endl;
			}

			if ( res == SQLITE_DONE )
			{
				cout << "done " << endl;
				break;
			}

		}
	}

   if ( isOpenDB == true )
   {
		sqlite3_close(dbfile);
   }

   cout << "Connected Closed" << endl;

   return 0;
}
*/
