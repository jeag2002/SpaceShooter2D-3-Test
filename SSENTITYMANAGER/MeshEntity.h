#ifndef MESHENTITY_H_INCLUDED
#define MESHENTITY_H_INCLUDED

#include "Stdafx.h"
#include "Resource.h"
#include "CoreString.h"

/*
TABLE ENT_MESH             //-->Definicion MESHES
ID              INT        //-->identificador MESH
SKELETON        CHAR(100)  //-->coordenadas VERTICES, COORD_TEXTURES, NORMALS, ORDER_OF_RENDERING
ID_IMAGE        CHAR(100)  //-->imagenes texturas.
*/

class MeshEntity : public Resource{

public:

MeshEntity():Resource(false,0, MESH_ENT){
    this->id = 0;
    this->skeleton = "";
    this->idimage = "";
}

MeshEntity(uint32_t timestamp):Resource(false, timestamp, MESH_ENT){
    this->id = 0;
    this->skeleton = "";
    this->idimage = "";
}

MeshEntity(MeshEntity *meshRef):Resource(false,0, MESH_ENT){
    this->id = meshRef->getId();
    this->skeleton = CoreString::copySafetyString(meshRef->getSkeleton());
    this->idimage = CoreString::copySafetyString(meshRef->getIdImage());
}

MeshEntity(MeshEntity *meshRef, uint32_t timestamp):Resource(false, timestamp, MESH_ENT){
    this->id = meshRef->getId();
    this->skeleton = CoreString::copySafetyString(meshRef->getSkeleton());
    this->idimage = CoreString::copySafetyString(meshRef->getIdImage());
}

void copyTo(MeshEntity *meshRef){
    this->id = meshRef->getId();
    this->skeleton = CoreString::copySafetyString(meshRef->getSkeleton());
    this->idimage = CoreString::copySafetyString(meshRef->getIdImage());
}

void clear(){
    this->id = 0;
    this->skeleton = "";
    this->idimage = "";
}

uint32_t getId(){return this->id;}
void setId(uint32_t _id){this->id = _id;}

std::string getSkeleton(){return this->skeleton;}
void setSkeleton(std::string _skeleton){this->skeleton = CoreString::copySafetyString(_skeleton);}

std::string getIdImage(){return this->idimage;}
void setIdImage(std::string _idimage){this->idimage = CoreString::copySafetyString(_idimage);}


private:

uint32_t id;
std::string skeleton;
std::string idimage;


};


#endif // MESHENTITY_H_INCLUDED
