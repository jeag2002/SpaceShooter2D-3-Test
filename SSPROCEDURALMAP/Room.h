#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

class Room{

public:

    Room(){
        this->x_room = 0;
        this->y_room = 0;
        this->width_room = 0;
        this->height_room = 0;
    };

    Room(int _x, int _y, int _width, int _height){
        this->x_room = _x;
        this->y_room = _y;
        this->width_room = _width;
        this->height_room = _height;
    };

    ~Room(){
        this->x_room = 0;
        this->y_room = 0;
        this->width_room = 0;
        this->height_room = 0;
    };

    int getXRoom(){return this->x_room;}
    int getYRoom(){return this->y_room;}
    int getWidthRoom(){return this->width_room;}
    int getHeightRoom(){return this->height_room;}

    void setXRoom(int _x_room){this->x_room = _x_room;}
    void setYRoom(int _y_room){this->y_room = _y_room;}
    void setWidthRoom(int _width_room){this->width_room = _width_room;}
    void setHeightRoom(int _height_room){this->height_room = _height_room;}

private:

int x_room;
int y_room;
int width_room;
int height_room;

};

#endif // ROOM_H_INCLUDED
