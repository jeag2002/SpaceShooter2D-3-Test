
/*

crear una base de datos SQLite: https://www.sqlite.org/cli.html
acceder a una base de datos SQLite

acceder a base de datos. SQLite

http://www.codeproject.com/Tips/378808/Accessing-a-SQLite-Database-with-Cplusplus

*/

#include "Stdafx.h"

//RECURSOS
#include "ImageRes.h"       //--> fuente imagenes
#include "ScriptRes.h"      //--> script lua
#include "SoundRes.h"       //--> sonidos
#include "StateRes.h"       //--> estados
#include "TiffRes.h"        //--> fuentes de sonido
#include "ParticleRes.h"    //--> particulas
#include "LightRes.h"       //--> luces
#include "ShaderRes.h"      //--> shader

//ENTIDADES.
#include "TileEntity.h"     //--> Tiles
#include "MeshEntity.h"     //--> Mesh
#include "ActorEntity.h"    //--> Actor (Entity)
#include "BlockEntity.h"    //--> Block
#include "WeaponEntity.h"   //--> Weapon
#include "ItemEntity.h"     //--> Item
#include "ExitEntity.h"     //--> Exit

int main (int argc, char *argv[])
{
   return 0;
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
