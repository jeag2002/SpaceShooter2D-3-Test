#ifndef PROCEDURALMAPINDOORGENERATOR_H_INCLUDED
#define PROCEDURALMAPINDOORGENERATOR_H_INCLUDED

#include "Leaf.h"
#include <vector>
#include <cstdlib>
#include <stdio.h>

class ProceduralMapIndoorGenerator{

public:

ProceduralMapIndoorGenerator(int _sizeFiles, int _sizeColumns, int _seed){
    this->sizeFiles = _sizeFiles;
    this->sizeColumns = _sizeColumns;
    this->seed = _seed;
    printf("\r\nProceduralMapIndoorGenerator--INI");
    Matrix = createMatrix();
    fillMatrix();
    createTree();
    processMatrix();
    printf("\r\nProceduralMapIndoorGenerator--FIN");
};


~ProceduralMapIndoorGenerator(){
    destroyMatrix();
    this->sizeFiles = 0;
    this->sizeColumns = 0;
    this->seed = 0;
};


int **getMatrix(){return Matrix;};

void processMatrix();

private:


Leaf *root;

std::vector<Leaf *>ListOfLeaf;

int **createMatrix();
void destroyMatrix();
void fillMatrix();

void createTree();
void processLeaf(Leaf *_leaf);

int sizeFiles;
int sizeColumns;
int sizeTileW;
int sizeTileH;
int seed;

int **Matrix;

};


#endif // PROCEDURALMAPINDOORGENERATOR_H_INCLUDED
