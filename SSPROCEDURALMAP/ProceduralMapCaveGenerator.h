#ifndef PROCEDURALMAPCAVEGENERATOR_H_INCLUDED
#define PROCEDURALMAPCAVEGENERATOR_H_INCLUDED

#include <cstdlib>
#include <vector>
#include <stdio.h>

class ProceduralMapCaveGenerator{

public:

ProceduralMapCaveGenerator(int _sizeFiles, int _sizeColumns, int _seed){
    this->sizeFiles = _sizeFiles;
    this->sizeColumns = _sizeColumns;
    this->seed = _seed;
    this->num_caves = 0;
    Matrix = createMatrix();
    fillMatrix();
    processCellAutomata();
    processCellAutomata();
    detectCaves();
    connectingUnconnectedCaverns();
};


~ProceduralMapCaveGenerator(){
    destroyMatrix();
    this->sizeFiles = 0;
    this->sizeColumns = 0;
    this->seed = 0;
    this->num_caves = 0;
    this->big_cave = 0;
};

//genera valores aleatorios
int randomValues(int min, int max);
//genera cavernas aleatorias
void processCellAutomata();
//detecta el numero de cavernas
void detectCaves();
//detecta la amplitud de una caverna
void floodFillCavern(int tile_pos_x, int tile_pos_y);
//conecta cavernas desconectadas de la principal
void connectingUnconnectedCaverns();


//eliminar matrices
/////////////////////////////////////////////////
int **getMatrix(){return Matrix;};
int **createMatrix();
void destroyMatrix();
void fillMatrix();
/////////////////////////////////////////////////



private:


typedef struct{
    int tile_pos_fila;
    int tile_pos_columna;
    int G;
    int H;

    int tile_pos_fila_par;
    int tile_pos_columna_par;
    int G_par;
    int H_par;
}cell;

typedef std::vector<cell> caveCoordsType;

std::vector<cell> openList;
std::vector<cell> closeList;

caveCoordsType caveCoords;
std::vector<caveCoordsType > caves;

void connectingBetweenPaths(cell c1, cell c2);
int evaluateH(cell c1, cell c2);

//A*
/////////////////////////////////////////////////
bool findCellInClosePath(cell c1);
bool findCellInOpenPath(cell c1);
void deleteCellInClosePath(cell c1);
void deleteCellInOpenPath(cell c1);
int indexCellInOpenPath(cell c1);
int indexCellInClosePath(int fila, int col);
/////////////////////////////////////////////////

/////////////////////////////////////////////////
//llena cavernas no conectadas
void FillCaves();
//llena una caverna.
void FillCave(int index);
/////////////////////////////////////////////////


int sizeFiles;
int sizeColumns;
int seed;

int num_caves;
int big_cave;

int **Matrix;
int **Matrix_Copy;

};

#endif // PROCEDURALMAPCAVEGENERATOR_H_INCLUDED
