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

#include <string>
#include <vector>
#include <map>

typedef struct{
    float rel_pos_x;
    float rel_pos_y;
}coordsXY;


#endif // STDAFX_H_INCLUDED
