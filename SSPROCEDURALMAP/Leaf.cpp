#include "Leaf.h"

int Leaf::randomValues(int min, int max)
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



bool Leaf::split(){

    bool splitHB = false;
    bool splitWB = false;

    if (leftChild != NULL || rightChild != NULL){
        return false;
    }else{

        splitHB = (width < height) && ((float(height)/float(width)) >= 1.25);
        splitWB = (width > height) && ((float(width)/float(height)) >= 1.25);

        int theshold = 0;

        if (splitHB){theshold = height - sizeLeaf;}else{theshold = width - sizeLeaf;}

        if (theshold > sizeLeaf){

            if (splitHB){
                int incH = randomValues(sizeLeaf, height);
                leftChild = new Leaf(x,y,width,incH,sizeLeaf);
                rightChild = new Leaf(x,y+incH,width,height - incH,sizeLeaf);
                printf("\r\n[LEFT CHILD] x:%d, y:%d, width:%d, height:%d sizeLeaf:%d",leftChild->getX(),leftChild->getY(),leftChild->getWidth(),leftChild->getHeight(),leftChild->getSizeLeaf());
                printf("\r\n[RIGHT CHILD] x:%d, y:%d, width:%d, height:%d sizeLeaf:%d",rightChild->getX(),rightChild->getY(),rightChild->getWidth(),rightChild->getHeight(),rightChild->getSizeLeaf());
                return true;

            }else if (splitWB){
                int incW = randomValues(sizeLeaf, width);
                leftChild = new Leaf(x,y,incW,height,sizeLeaf);
                rightChild = new Leaf(x+incW,y,width-incW,height,sizeLeaf);
                printf("\r\n[LEFT CHILD] x:%d, y:%d, width:%d, height:%d sizeLeaf:%d",leftChild->getX(),leftChild->getY(),leftChild->getWidth(),leftChild->getHeight(),leftChild->getSizeLeaf());
                printf("\r\n[RIGHT CHILD] x:%d, y:%d, width:%d, height:%d sizeLeaf:%d",rightChild->getX(),rightChild->getY(),rightChild->getWidth(),rightChild->getHeight(),rightChild->getSizeLeaf());
                return true;
            }else{
                return false;
            }

        }else{
            return false;
        }

    }
}

Room *Leaf::getRoom(){

    if (rectangle != NULL){
        return rectangle;
    }else{

        Room *leftRoom;
        Room *rightRoom;

        if (this->leftChild != NULL){
            leftRoom = leftChild->getRoom();
        }

        if (this->rightChild != NULL){
            rightRoom = rightChild->getRoom();
        }

        if ((leftRoom == NULL) && (rightRoom == NULL)){
            return NULL;
        }else if (leftRoom == NULL){
            return rightRoom;
        }else{
            return leftRoom;
        }
    }
}



void Leaf::createHall(Room *left, Room *right){

    int point_1x = randomValues(left->getXRoom()+1, left->getXRoom()+left->getWidthRoom()-2);
    int point_1y = randomValues(left->getYRoom()+1, left->getYRoom()+left->getHeightRoom()-2);

    int point_2x = randomValues(right->getXRoom()+1, right->getXRoom()+right->getWidthRoom()-2);
    int point_2y = randomValues(right->getYRoom()+1, right->getYRoom()+right->getHeightRoom()-2);

    int w = point_2x - point_1x;
    int h = point_2y - point_1y;


    if (w < 0)
    {
        if (h < 0){
            halls.push_back(new Room(point_2x, point_2y, abs(w), 1));
            halls.push_back(new Room(point_1x, point_2y, 1, abs(h)));

            printf("\r\n[CREATE CORRIDOR -w -h] x:%d, y:%d, width:%d, height:%d",point_2x, point_2y, abs(w), 1);
            printf("\r\n[CREATE CORRIDOR -w -h] x:%d, y:%d, width:%d, height:%d",point_1x, point_2y, 1, abs(h));

        }
        else if (h > 0){
            halls.push_back(new Room(point_2x, point_2y, abs(w), 1));
            halls.push_back(new Room(point_1x, point_1y, 1, abs(h)));

            printf("\r\n[CREATE CORRIDOR -w +h] x:%d, y:%d, width:%d, height:%d",point_2x, point_2y, abs(w), 1);
            printf("\r\n[CREATE CORRIDOR -w +h] x:%d, y:%d, width:%d, height:%d",point_1x, point_1y, 1, abs(h));

        }
        else{
            halls.push_back(new Room(point_2x, point_2y, abs(w), 1));
            printf("\r\n[CREATE CORRIDOR -w h=0] x:%d, y:%d, width:%d, height:%d",point_2x, point_2y, abs(w), 1);
        }
    }
    else if (w > 0){
        if (h < 0){
            halls.push_back(new Room(point_1x, point_1y, abs(w), 1));
            halls.push_back(new Room(point_2x, point_2y, 1, abs(h)));

            printf("\r\n[CREATE CORRIDOR +w -h] x:%d, y:%d, width:%d, height:%d",point_1x, point_1y, abs(w), 1);
            printf("\r\n[CREATE CORRIDOR +w -h] x:%d, y:%d, width:%d, height:%d",point_2x, point_2y, 1, abs(h));

        }
        else if (h > 0){
            halls.push_back(new Room(point_1x, point_2y, abs(w), 1));
            halls.push_back(new Room(point_1x, point_1y, 1, abs(h)));

            printf("\r\n[CREATE CORRIDOR +w +h] x:%d, y:%d, width:%d, height:%d",point_1x, point_2y, abs(w), 1);
            printf("\r\n[CREATE CORRIDOR +w +h] x:%d, y:%d, width:%d, height:%d",point_1x, point_1y, 1, abs(h));

        }
        else{
            halls.push_back(new Room(point_1x, point_1y, abs(w), 1));

            printf("\r\n[CREATE CORRIDOR +w h=0] x:%d, y:%d, width:%d, height:%d",point_1x, point_1y, abs(w), 1);
        }
    }else{
        if (h < 0){
            halls.push_back(new Room(point_2x, point_2y, 1, abs(h)));
            printf("\r\n[CREATE CORRIDOR w=0 -h] x:%d, y:%d, width:%d, height:%d",point_2x, point_2y, 1, abs(h));
        }
        else if (h > 0){
            halls.push_back(new Room(point_1x, point_1y, 1, abs(h)));
            printf("\r\n[CREATE CORRIDOR w=0 +h] x:%d, y:%d, width:%d, height:%d",point_1x, point_1y, 1, abs(h));
        }
    }
}

void Leaf::createRooms(){

    if (this->leftChild != NULL || this->rightChild != NULL){
        if (this->leftChild!= NULL){leftChild->createRooms();}
        if (this->rightChild != NULL){rightChild->createRooms();}
        if ((this->rightChild != NULL) && (this->leftChild != NULL)){
            createHall(leftChild->getRoom(), rightChild->getRoom());
        }
    }else{

        rectangle = new Room();
        rectangle->setXRoom(this->x +1);
        rectangle->setYRoom(this->y +1);
        rectangle->setWidthRoom(this->width-2);
        rectangle->setHeightRoom(this->height-2);

        printf("\r\n[ROOM] (tiles) (x:%d,y:%d) - (x:%d,y:%d)",
               rectangle->getXRoom(),
               rectangle->getYRoom(),
               rectangle->getWidthRoom()+rectangle->getXRoom(),
               rectangle->getHeightRoom()+rectangle->getYRoom());

    }
}
