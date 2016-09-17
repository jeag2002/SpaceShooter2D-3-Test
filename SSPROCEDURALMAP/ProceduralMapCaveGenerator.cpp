#include "ProceduralMapCaveGenerator.h"


int **ProceduralMapCaveGenerator::createMatrix(){

    int **_Matrix;

    _Matrix  = new  int *[sizeFiles];
    for (int i = 0; i< sizeFiles; i++){
            _Matrix[i] = new int[sizeColumns];
    }
    return _Matrix;

};

void ProceduralMapCaveGenerator::fillMatrix(){
    for(int i=0; i< sizeFiles; i++){
        for(int j=0; j<sizeColumns; j++){
            Matrix[i][j] = randomValues(0, 1);
        }
    }
};

void ProceduralMapCaveGenerator::processCellAutomata(){

    int num_walls = 0;
    int num_floors = 0;
    int value = 0;

    for (int i=0; i<sizeFiles; i++){
        for (int j=0; j<sizeColumns; j++){

            num_walls = 0;
            num_floors = 0;
            value = Matrix[i][j];

            if (((i-1) >= 0) && ((j-1) >= 0)){//izquierda-arriba
                if (Matrix[i-1][j-1] == 0){num_floors++;}
                else{num_walls++;}
            }

            if (((i-1) >= 0) && ((j) >= 0)){//arriba
                if (Matrix[i-1][j] == 0){num_floors++;}
                else{num_walls++;}
            }

            if (((i-1) >= 0 ) && ((j+1) < sizeColumns)){ //derecha-arriba
                if (Matrix[i-1][j+1] == 0){num_floors++;}
                else{num_walls++;}
            }


            if ((i >= 0) && ((j-1) >= 0)){//izquierda
                if (Matrix[i][j-1] == 0){num_floors++;}
                else{num_walls++;}
            }

            if ((i >= 0 ) && ((j+1) < sizeColumns)){ //derecha
                if (Matrix[i][j+1] == 0){num_floors++;}
                else{num_walls++;}
            }

            if (((i+1) < sizeFiles) && ((j-1) >= 0)){//izquierda-abajo
                if (Matrix[i+1][j-1] == 0){num_floors++;}
                else{num_walls++;}
            }

            if (((i+1) < sizeFiles) && ((j) >= 0)){//abajo
                if (Matrix[i+1][j] == 0){num_floors++;}
                else{num_walls++;}
            }

            if (((i+1) < sizeFiles) && ((j+1) < sizeColumns)){ //derecha-abajo
                if (Matrix[i+1][j+1] == 0){num_floors++;}
                else{num_walls++;}
            }

            if ((value == 0) && (num_walls > 4)){Matrix[i][j]=1;}
            else if ((value == 1) && (num_walls < 3)){Matrix[i][j]=0;}
            else{
                Matrix[i][j] = value;
            }
        }
    }


}


int ProceduralMapCaveGenerator::randomValues(int min, int max)
{
    int range, result, cutoff;

    if (min >= max)
        return min;
    range = max-min+1;
    cutoff = (RAND_MAX / range) * range;
    do {
        result = rand();
    } while (result >= cutoff);

    return result % range + min;
}


void ProceduralMapCaveGenerator::destroyMatrix(){

        for (int i = 0; i < sizeFiles; ++i){
            delete [] Matrix[i];
        }
        delete [] Matrix;

};


void ProceduralMapCaveGenerator::floodFillCavern(int tile_pos_fila, int tile_pos_columna){

    if (Matrix_Copy[tile_pos_fila][tile_pos_columna] != 1){
        cell data;

        data.tile_pos_fila = tile_pos_fila;
        data.tile_pos_columna = tile_pos_columna;
        caveCoords.push_back(data);
        Matrix_Copy[tile_pos_fila][tile_pos_columna] = 1;

        if (tile_pos_fila > 0){floodFillCavern(tile_pos_fila-1,tile_pos_columna);}

        if (tile_pos_fila < sizeFiles -1){floodFillCavern(tile_pos_fila+1,tile_pos_columna);}

        if (tile_pos_columna > 0){floodFillCavern(tile_pos_fila,tile_pos_columna-1);}

        if (tile_pos_columna < sizeColumns -1){floodFillCavern(tile_pos_fila,tile_pos_columna+1);}
    }

}

int ProceduralMapCaveGenerator::evaluateH(cell c1, cell c2){

    int H = 0;

    H = abs(c2.tile_pos_fila - c1.tile_pos_fila);
    H += abs(c2.tile_pos_columna - c1.tile_pos_columna);

    return H;
};

bool ProceduralMapCaveGenerator::findCellInClosePath(cell c1){
    bool res = false;
    for(int i=0; ((i<closeList.size()) && (!res)); i++){
        cell aux = (cell)closeList[i];
        res = ((c1.tile_pos_fila == aux.tile_pos_fila) && (c1.tile_pos_columna == aux.tile_pos_columna));
    }
    return res;
};

bool ProceduralMapCaveGenerator::findCellInOpenPath(cell c1){
    bool res = false;
    for(int i=0; ((i<openList.size()) && (!res)); i++){
        cell aux = (cell)openList[i];
        res = ((c1.tile_pos_fila == aux.tile_pos_fila) && (c1.tile_pos_columna == aux.tile_pos_columna));
    }
    return res;

};

void ProceduralMapCaveGenerator::deleteCellInClosePath(cell c1){

    bool res = false;
    int index = 0;
    for(index=0; ((index<closeList.size()) && (!res)); index++){
        cell aux = (cell)closeList[index];
        res = ((c1.tile_pos_fila == aux.tile_pos_fila) && (c1.tile_pos_columna == aux.tile_pos_columna));
    }

    if (index < closeList.size()){
        closeList.erase(closeList.begin()+index);
    }

};

void ProceduralMapCaveGenerator::deleteCellInOpenPath(cell c1){
    bool res = false;
    int index = 0;
    for(index=0; ((index<openList.size()) && (!res)); index++){
        cell aux = (cell)openList[index];
        res = ((c1.tile_pos_fila == aux.tile_pos_fila) && (c1.tile_pos_columna == aux.tile_pos_columna));
    }

    if (index < openList.size()){
        openList.erase(openList.begin()+index);
    }
};

int ProceduralMapCaveGenerator::indexCellInOpenPath(cell c1){

    int index = 0;
    bool res = false;

    for(index = 0; ((index<openList.size()) && (!res)); index++){
        cell aux = (cell)openList[index];
        res = ((c1.tile_pos_fila == aux.tile_pos_fila) && (c1.tile_pos_columna == aux.tile_pos_columna));
    }

    return (index-1);

}


int ProceduralMapCaveGenerator::indexCellInClosePath(int fila, int col){
    int index = 0;
    bool res = false;

    for(index = 0; ((index<closeList.size()) && (!res)); index++){
        cell aux = (cell)closeList[index];
        res = ((fila == aux.tile_pos_fila) && (col == aux.tile_pos_columna));
    }

    return (index-1);

}




void ProceduralMapCaveGenerator::connectingBetweenPaths(cell c1, cell c2){


    if (evaluateH(c1,c2)!= 0){
        //1-Evalua los nodos adjacentes, los añade en la lista abierta

        //UP
        if (c1.tile_pos_fila > 0){
            cell cA;
            cA.tile_pos_fila = c1.tile_pos_fila-1;
            cA.tile_pos_columna = c1.tile_pos_columna;
            cA.G = c1.G+1;
            cA.H = evaluateH(cA, c2);

            cA.tile_pos_fila_par = c1.tile_pos_fila;
            cA.tile_pos_columna_par = c1.tile_pos_columna;
            cA.G_par = c1.G;
            cA.H_par = c1.H;

            if (!findCellInClosePath(cA)){
                if (!findCellInOpenPath(cA)){
                    openList.push_back(cA);
                }else{
                    int index = indexCellInOpenPath(cA);
                    if(index < openList.size()){
                       cell aux = openList[index];
                       if (cA.G < aux.G){
                            printf("OJO cA camino mas optimo. Sustituto en ListaAbierta");
                            openList[index] = cA;
                       }
                    }
                }
            }
        }

        //DOWN
        if (c1.tile_pos_fila < (sizeFiles-1)){
            cell cB;
            cB.tile_pos_fila = c1.tile_pos_fila+1;
            cB.tile_pos_columna = c1.tile_pos_columna;
            cB.G = c1.G+1;
            cB.H = evaluateH(cB, c2);

            cB.tile_pos_fila_par = c1.tile_pos_fila;
            cB.tile_pos_columna_par = c1.tile_pos_columna;
            cB.G_par = c1.G;
            cB.H_par = c1.H;

            if (!findCellInClosePath(cB)){
                if (!findCellInOpenPath(cB)){
                    openList.push_back(cB);
                }else{
                    int index = indexCellInOpenPath(cB);
                    if(index < openList.size()){
                        cell aux = openList[index];
                        if (cB.G < aux.G){
                            printf("OJO cB camino mas optimo. Sustituto en ListaAbierta");
                            openList[index] = cB;
                       }
                    }
                }
            }
        }

        //LEFT
        if (c1.tile_pos_columna > 0){
            cell cC;
            cC.tile_pos_fila = c1.tile_pos_fila;
            cC.tile_pos_columna = c1.tile_pos_columna -1;
            cC.G = c1.G+1;
            cC.H = evaluateH(cC, c2);

            cC.tile_pos_fila_par = c1.tile_pos_fila;
            cC.tile_pos_columna_par = c1.tile_pos_columna;
            cC.G_par = c1.G;
            cC.H_par = c1.H;


            if (!findCellInClosePath(cC)){
                if (!findCellInOpenPath(cC)){
                   openList.push_back(cC);
                }else{
                    int index = indexCellInOpenPath(cC);
                    if(index < openList.size()){
                        cell aux = openList[index];
                        if (cC.G < aux.G){
                            printf("OJO cC camino mas optimo. Sustituto en ListaAbierta");
                            openList[index] = cC;
                       }
                    }
                }
            }
        }

        //RIGHT
        if (c1.tile_pos_columna < (sizeColumns-1)){
            cell cD;
            cD.tile_pos_fila = c1.tile_pos_fila;
            cD.tile_pos_columna = c1.tile_pos_columna + 1;
            cD.G = c1.G+1;
            cD.H = evaluateH(cD, c2);

            cD.tile_pos_fila_par = c1.tile_pos_fila;
            cD.tile_pos_columna_par = c1.tile_pos_columna;
            cD.G_par = c1.G;
            cD.H_par = c1.H;

            if (!findCellInClosePath(cD)){
                if (!findCellInOpenPath(cD)){
                    openList.push_back(cD);
                }else{
                    int index = indexCellInOpenPath(cD);
                    if(index < openList.size()){
                       cell aux = openList[index];
                       if (cD.G < aux.G){
                            printf("OJO cD camino mas optimo. Sustituto en ListaAbierta");
                            openList[index] = cD;
                       }
                    }
                }
            }
        }

        //coge el menor de los almacenados en la lista abierta. Lo pone en la lista cerrada.
        //////////////////////////////////////////////////////////////////////////////////////////////
        cell ini_data = openList[0];
        int F = ini_data.G + ini_data.H;
        int index = 0;

        for(int i=0; i<openList.size(); i++){
            cell data = openList[i];
            int F_compare = data.G +  data.H;

            if (F_compare < F){
                F = F_compare;
                index = i;
            }
        }

        cell lessWeight  = openList[index];
        closeList.push_back(lessWeight);            //-->añade el elemento en la lista cerrada.
        printf("\r\nPUSH CLOSELIST --> fila:%d columna:%d filapar:%d colpar:%d G:%d H:%d",
               lessWeight.tile_pos_fila,
               lessWeight.tile_pos_columna,
               lessWeight.tile_pos_fila_par,
               lessWeight.tile_pos_columna_par,
               lessWeight.G,
               lessWeight.H);

        openList.erase(openList.begin()+index);     //-->borra el elemento en la lista abierta.
        //////////////////////////////////////////////////////////////////////////////////////////////

        connectingBetweenPaths(lessWeight,c2);

    }else{
       printf("\n\rCAMINO ENCONTRADO");
       //printf("\r\nPUSH CLOSELIST --> fila:%d columna:%d G:%d H:%d",c1.tile_pos_fila,c1.tile_pos_columna,c1.G,c1.H);
       //closeList.push_back(c1);
    }

};


//llena cavernas no conectadas
void ProceduralMapCaveGenerator::FillCaves(){

    for(int i=0; i<this->num_caves; i++){
        if (i!=this->big_cave){
            FillCave(i);
        }
    }

}
//llena una caverna.
void ProceduralMapCaveGenerator::FillCave(int index){

    caveCoordsType cFilled = caves[this->big_cave];

    for(int j=0; j<cFilled.size(); j++){
        cell data = cFilled[j];
        Matrix[data.tile_pos_fila][data.tile_pos_columna] = 1;
    }
}



void ProceduralMapCaveGenerator::connectingUnconnectedCaverns(){
    printf("\n\rConectingUnconectedCaves --- INI");
    printf("\n\rConectingUnconectedCaves --- BigCave [%d]",big_cave);

    caveCoordsType cPrincipal = caves[this->big_cave];

    for(int i=0; i<this->num_caves; i++){

        if (i!=this->big_cave){
            caveCoordsType cOther = caves[i];
            int indexPrincipal = randomValues(0, cPrincipal.size()-1);
            int indexOthers = randomValues(0,cOther.size()-1);

            printf("\n\rConectingUnconectedCaves --- IndexPrincipal [%d] - IndexOthers [%d]",indexPrincipal,indexOthers);

            cell cell_Ini = cPrincipal[indexPrincipal];
            cell cell_Fin = cOther[indexOthers];

            cell_Ini.G = 0;
            cell_Ini.H = evaluateH(cell_Ini, cell_Fin);

            cell_Ini.tile_pos_fila_par = 0;
            cell_Ini.tile_pos_columna_par = 0;
            cell_Ini.G_par = 0;
            cell_Ini.H_par = 0;

            printf("\n\rConectingUnconectedCaves --- Coord BigCave (fila:%d,columna:%d) - Coord DestCave(fila:%d,columna:%d)",
                   cell_Ini.tile_pos_fila, cell_Ini.tile_pos_columna, cell_Fin.tile_pos_fila, cell_Fin.tile_pos_columna);

            openList.push_back(cell_Ini);
            connectingBetweenPaths(cell_Ini,cell_Fin);

            if (closeList.size() > 0){

                int index = this->indexCellInClosePath(cell_Fin.tile_pos_fila, cell_Fin.tile_pos_columna);
                cell step = closeList[index];

                while (((step.tile_pos_fila != cell_Ini.tile_pos_fila) || (step.tile_pos_columna != cell_Ini.tile_pos_columna)) && (index < closeList.size())){

                    printf("\r\nClear way file:%d,column:%d,index:%d",step.tile_pos_fila,step.tile_pos_columna,index);
                    Matrix[step.tile_pos_fila][step.tile_pos_columna] = 0;

                    index = this->indexCellInClosePath(step.tile_pos_fila_par, step.tile_pos_columna_par);
                    step = closeList[index];
                }
            }

            openList.clear();
            closeList.clear();
        }
    }


    printf("\n\rConectingUnconectedCaves --- END");
}


void ProceduralMapCaveGenerator::detectCaves(){

    int size_cave = 0;
    this->num_caves = 0;
    this->big_cave = -1;

    printf("\n\rDetecting caves --- INI");
    Matrix_Copy  = new  int *[sizeFiles];
    for (int i = 0; i< sizeFiles; i++){
            Matrix_Copy[i] = new int[sizeColumns];
    }

    for(int i=0; i<sizeFiles; i++){
        for(int j=0; j<sizeColumns; j++){
           Matrix_Copy[i][j] = Matrix[i][j];
        }
    }


    for(int i=0; i<sizeFiles; i++){
        for(int j=0; j<sizeColumns; j++){
            if (Matrix_Copy[i][j] == 0){
                floodFillCavern(i, j);
                caves.push_back(caveCoords);
                printf("\n\rSize of cave --- %d",caveCoords.size());

                if (size_cave < caveCoords.size()){
                    size_cave = caveCoords.size();
                    this->big_cave = this->num_caves;
                }

                this->num_caves++;

                caveCoords.clear();
            }
        }
    }

    if (caveCoords.size() > 0){
        caves.push_back(caveCoords);
        printf("\n\rSize of cave --- %d",caveCoords.size());

        if (size_cave < caveCoords.size()){
            size_cave  = caveCoords.size();
            this->big_cave = this->num_caves;
        }

        this->num_caves++;
        caveCoords.clear();
    }

    printf("\n\rNumber of caves --- %d",caves.size());

    for (int i = 0; i < sizeFiles; ++i){
            delete [] Matrix_Copy[i];
    }
    delete [] Matrix_Copy;

    printf("\n\rDetecting caves --- END");

};
