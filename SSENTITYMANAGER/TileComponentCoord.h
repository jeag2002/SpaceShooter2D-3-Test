#ifndef TILECOMPONENTCOORD_H_INCLUDED
#define TILECOMPONENTCOORD_H_INCLUDED

#include "Stdafx.h"
#include "Resource.h"
#include "CoreString.h"

/*
TABLE ENT_TILE_COMP_BUFF   //-->definicion de un fotograma del componente.

IDBUFF          INT
IDCOMP          INT
ID              INT
COORD           CHAR(100)  //-->coordinates of texture.
*/

class TileComponentCoord{

private:

    uint32_t idbuff;
    uint32_t idcomp;
    uint32_t id;
    coordsXY coordinates[SIZE_COORD];
    int coordLimits;

    void clearCoordinates(){
        for(int i=0; i<SIZE_COORD; i++){
            coordinates[i].rel_pos_x = 0.0;
            coordinates[i].rel_pos_y = 0.0;
        }
    }


public:

    TileComponentCoord(){
        this->idbuff = 0;
        this->idcomp = 0;
        this->id = 0;
        clearCoordinates();
        this->coordLimits = 0;
    }

    TileComponentCoord(TileComponentCoord *tileComponentCoordRef){
        this->idbuff = tileComponentCoordRef->getIdBuff();
        this->idcomp = tileComponentCoordRef->getIdComp();
        this->id = tileComponentCoordRef->getId();
        copyVectorCoordinates(tileComponentCoordRef);
    }

    void copyTo(TileComponentCoord *tileComponentCoordRef){
        this->idbuff = tileComponentCoordRef->getIdBuff();
        this->idcomp = tileComponentCoordRef->getIdComp();
        this->id = tileComponentCoordRef->getId();
        copyVectorCoordinates(tileComponentCoordRef);
    }

    void clear(){
        this->idbuff = 0;
        this->idcomp = 0;
        this->id = 0;
        clearCoordinates();
        this->coordLimits = 0;
    }

    ~TileComponentCoord(){
        this->idbuff = 0;
        this->idcomp = 0;
        this->id = 0;
        clearCoordinates();
        this->coordLimits = 0;
    }

    uint32_t getIdBuff(){return idbuff;}
    void setIdBuff(uint32_t _idbuff){this->idbuff = _idbuff;}

    uint32_t getIdComp(){return idcomp;}
    void setIdComp(uint32_t _idcomp){this->idcomp = _idcomp;}

    uint32_t getId(){return id;}
    void setId(uint32_t _id){this->id = _id;}

    coordsXY *getCoordinates(){return coordinates;}
    int getCoordinatesSize(){return this->coordLimits;}

    void addCoordinate(coordsXY data){
        if (this->coordLimits < SIZE_COORD){
            coordinates[coordLimits] = data;
            coordLimits++;
        }
    }

    coordsXY getCoordinateByIndex(int index){

        coordsXY coordDummy;
        coordDummy.rel_pos_x = 0;
        coordDummy.rel_pos_y = 0;

        if ((index >=0) && (index < SIZE_COORD)){
            return coordinates[index];
        }else{
            return coordDummy;
        }

    }


    void copyVectorCoordinates(TileComponentCoord *tileComponentCoordRef){

        int limits = tileComponentCoordRef->getCoordinatesSize();
        clearCoordinates();
        coordLimits = 0;


        for(int i=0; i<limits; i++){
            coordsXY coordsMaster;

            coordsXY coordsDummy = tileComponentCoordRef->getCoordinateByIndex(i);
            coordsMaster.rel_pos_x = coordsDummy.rel_pos_x;
            coordsMaster.rel_pos_y = coordsDummy.rel_pos_y;

            coordinates[coordLimits] = coordsMaster;
            coordLimits++;
        }


    }




};


#endif // TILECOMPONENTCOORD_H_INCLUDED
