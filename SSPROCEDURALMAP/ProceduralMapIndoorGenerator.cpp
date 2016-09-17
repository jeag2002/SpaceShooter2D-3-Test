#include "ProceduralMapIndoorGenerator.h"

int **ProceduralMapIndoorGenerator::createMatrix(){

    int **_Matrix;

    _Matrix  = new  int *[sizeFiles];
    for (int i = 0; i< sizeFiles; i++){
            _Matrix[i] = new int[sizeColumns];
    }
    return _Matrix;


};

void ProceduralMapIndoorGenerator::fillMatrix(){
    for(int i=0; i< sizeFiles; i++){
        for(int j=0; j<sizeColumns; j++){
            Matrix[i][j] = 1;
        }
    }
};



void ProceduralMapIndoorGenerator::destroyMatrix(){

        for (int i = 0; i < sizeFiles; ++i){
            delete [] Matrix[i];
        }
        delete [] Matrix;
};

void ProceduralMapIndoorGenerator::createTree(){

    root = new Leaf(0,0,this->sizeFiles,this->sizeColumns,this->seed);
    ListOfLeaf.push_back(root);

    bool did_split = true;

    while(did_split){
         did_split = false;
         for (int i=0; i<ListOfLeaf.size(); i++){
                Leaf *idle = ListOfLeaf[i];

                if ((idle->getWidth() > this->seed) || (idle->getHeight() > this->seed)){
                    if ((idle->getLeftLeaf() == NULL) && (idle->getRightLeaf() == NULL)){
                        did_split = idle->split();
                        if (did_split){
                            ListOfLeaf.push_back(idle->getLeftLeaf());
                            ListOfLeaf.push_back(idle->getRightLeaf());
                        }
                    }
                }
         }
    }
    root->createRooms();
};

void ProceduralMapIndoorGenerator::processMatrix(){

    //LEAFS
    /*
    for(int i=0; i<ListOfLeaf.size(); i++){

        Leaf *leaf = ListOfLeaf[i];
        if (leaf != NULL){

            int x = leaf->getX();
            int y = leaf->getY();
            int width = leaf->getWidth();
            int height = leaf->getHeight();

            for(int j=leaf->getX(); j<(leaf->getX()+leaf->getWidth()); j++){
                    for(int z=leaf->getY(); z<(leaf->getY()+leaf->getHeight()); z++){
                        Matrix[j][z] = 4;
                    }
            }
        }
    }
    */

    //ROOMS
    for(int i=0; i<ListOfLeaf.size(); i++){
            Leaf *leaf = ListOfLeaf[i];

            Room *room = leaf->getRoom();

            if(room!=NULL){
                int x = room->getXRoom();
                int y = room->getYRoom();
                int width = room->getWidthRoom();
                int height = room->getHeightRoom();

                for(int j=room->getXRoom(); j<(room->getXRoom()+room->getWidthRoom()); j++){
                    for(int z=room->getYRoom(); z<(room->getYRoom()+room->getHeightRoom()); z++){
                        Matrix[j][z] = 0;
                    }
                }
            }
    }

    //CORRIDORS
    for(int i=0; i<ListOfLeaf.size(); i++){
        Leaf *leaf = ListOfLeaf[i];
        if (leaf != NULL){
            std::vector<Room *>corrs = leaf->getHalls();
            for (int j=0; j<corrs.size(); j++){

                Room *corr = corrs[j];

                if (corr!=NULL){

                    int x = corr->getXRoom();
                    int y = corr->getYRoom();
                    int width = corr->getWidthRoom();
                    int height = corr->getHeightRoom();

                    for(int k=corr->getXRoom(); ((k<(corr->getXRoom()+corr->getWidthRoom())) && (k<this->sizeFiles)); k++){
                        for(int z=corr->getYRoom(); ((z<(corr->getYRoom()+corr->getHeightRoom())) && (z<this->sizeColumns)); z++){
                            Matrix[k][z] = 0;
                        }
                    }
                }
            }
        }
    }

    /*
    std::vector<Room *>corridors = root->getHalls();
    for (int i=0; i<corridors.size(); i++){
        Room *corr = corridors[i];

        if (corr!=NULL){

            int x = corr->getXRoom();
            int y = corr->getYRoom();
            int width = corr->getWidthRoom();
            int height = corr->getHeightRoom();

            for(int j=corr->getXRoom(); j<(corr->getXRoom()+corr->getWidthRoom()); j++){
                for(int z=corr->getYRoom(); z<(corr->getYRoom()+corr->getHeightRoom()); z++){
                    Matrix[j][z] = 3;
                }
            }
        }
    }
    */
};
