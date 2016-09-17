#ifndef LEAF_H_INCLUDED
#define LEAF_H_INCLUDED

#include <vector>
#include <cstdlib>
#include <stdio.h>
#include "Room.h"

class Leaf{

public:

    Leaf(){
        this->x = 0;
        this->y = 0;
        this->width = 0;
        this->height = 0;

        this->rectangle = NULL;
        this->leftChild = NULL;
        this->rightChild = NULL;

    };

    Leaf(int _x, int _y, int _width, int _height, int _sizeLeaf){
        this->x = _x;
        this->y = _y;
        this->width = _width;
        this->height = _height;
        this->sizeLeaf = _sizeLeaf;

        this->rectangle = NULL;
        this->leftChild = NULL;
        this->rightChild = NULL;
    }

    ~Leaf(){
        this->x = 0;
        this->y = 0;
        this->width = 0;
        this->height = 0;
        this->sizeLeaf = 0;

        delete rectangle;
        delete leftChild;
        delete rightChild;
    }

    /*
    void room(int _x_room, int _y_room, int _width_room, int _height_room){
        rectangle->setXRoom(_x_room);
        rectangle->setYRoom(_y_room);
        rectangle->setWidthRoom(_width_room);
        rectangle->setHeightRoom(_height_room);
    }*/


    int getX(){return this->x;}
    int getY(){return this->y;}
    int getWidth(){return this->width;}
    int getHeight(){return this->height;}
    int getSizeLeaf(){return this->sizeLeaf;}

    Room *getRectangle(){return rectangle;}
    Leaf *getLeftLeaf(){return leftChild;}
    Leaf *getRightLeaf(){return rightChild;}

    Room *getRoom();

    int randomValues(int min, int max);
    bool split();
    void createRooms();
    void createHall(Room *left, Room *right);
    std::vector<Room *>getHalls(){return halls;}

private:

 int x;
 int y;
 int width;
 int height;
 int sizeLeaf;

 Room *rectangle;
 std::vector<Room *>halls;

 Leaf *leftChild;
 Leaf *rightChild;

};

#endif // LEAF_H_INCLUDED
