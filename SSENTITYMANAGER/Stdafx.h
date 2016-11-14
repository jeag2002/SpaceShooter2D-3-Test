#ifndef STDAFX_H_INCLUDED
#define STDAFX_H_INCLUDED

#define SIZE_PATH 100
#define SIZE_TYPE 5
#define SIZE_COORD 20
#define SIZE_NODES 7

#define IMAGE_REF 0
#define SCRIPT_REF 1
#define TIFF_REF 2
#define SOUND_REF 3
#define LIGHT_REF 4
#define PARTICLE_REF 5
#define SHADER_REF 6

#define TILE_ENT 7
#define MESH_ENT 8
#define ACTOR_ENT 9
#define BLOCK_ENT 10
#define EXIT_ENT 11
#define WEAPON_ENT 12
#define WEAPON_BEAM_ENT 13

#define ITEM_ENT 14

#define DB "data/sea.s3db"
#include "sqlite3.h"

#include <vector>
#include <map>
#include <list>

#ifdef PROFILING
    #define DEBUG_DATA 1
#else
    #define DEBUG_DATA 2
    #define NDEBUG
#endif

#include <cassert>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <time.h>

//INFO PROFILING
#ifdef WIN32
#include <windows.h>
#include <winbase.h>
#include <psapi.h>
#include <tchar.h>
#endif

#include <SDL.h>
#undef main

#define ACTOR_QUERY "select ID, LIVE, SHIELD, SCORE from ACTOR where ID = %d"

typedef struct{
    float rel_pos_x;
    float rel_pos_y;
}coordsXY;


#endif // STDAFX_H_INCLUDED
