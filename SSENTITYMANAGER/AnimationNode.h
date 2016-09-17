#ifndef ANIMATIONNODE_H_INCLUDED
#define ANIMATIONNODE_H_INCLUDED

/*
ID_ANIMATION    INT
ID_NODE         INT
X_NODE          FLOAT
Y_NODE          FLOAT
LENGHT          INT
ANGLE           FLOAT
IS_ROOT         BYTE        //gestion si es root o no
ID_TILE         INT         //ID_TILE asociado (2D)
ID_MESH         INT         //ID_MESH asociado (3D)
*/

class AnimationNode{

public:

AnimationNode(){

    this->idAnimation = 0;
    this->idNode = 0;
    this->idTile = 0;
    this->idMesh = 0;

    this->xPos = 0;
    this->yPos = 0;
    this->length = 0;
    this->angle = 0;
    this->Root = false;

    this->numChildren = 0;
    clearNodeChilds();
};

AnimationNode(AnimationNode *animationNodeRef){
    this->idAnimation = animationNodeRef->getIdAnimation();
    this->idNode = animationNodeRef->getIdNode();
    this->idTile = animationNodeRef->getIdTile();
    this->idMesh = animationNodeRef->getIdMesh();
    this->xPos = animationNodeRef->getXPos();
    this->yPos = animationNodeRef->getYPos();
    this->length = animationNodeRef->getLength();
    this->angle = animationNodeRef->getAngle();
    this->Root = animationNodeRef->isRoot();
    CopyChildNodes(animationNodeRef);
}


~AnimationNode(){
    this->idAnimation = 0;
    this->idNode = 0;
    this->idTile = 0;
    this->idMesh = 0;

    this->xPos = 0;
    this->yPos = 0;
    this->length = 0;
    this->angle = 0;
    this->Root = false;

    this->numChildren = 0;
    clearNodeChilds();
}


uint32_t getIdAnimation(){return this->idAnimation;}
void setIdAnimation(uint32_t _idAnimation){this->idAnimation = _idAnimation;}

uint32_t getIdNode(){return this->idNode;}
void setIdNode(uint32_t _idNode){this->idNode = _idNode;}

uint32_t getIdTile(){return this->idTile;}
void setIdTile(uint32_t _idTile){this->idTile = _idTile;}

uint32_t getIdMesh(){return this->idMesh;}
void setIdMesh(uint32_t _idMesh){this->idMesh = _idMesh;}

float getXPos(){return this->xPos;}
void setXPos(float _xPos){this->xPos = _xPos;}

float getYPos(){return this->yPos;}
void setYPos(float _yPos){this->yPos = _yPos;}

float getLength(){return this->length;}
void setLength(float _length){this->length = _length;}

float getAngle(){return this->angle;}
void setAngle(float _angle){this->angle = _angle;}

bool isRoot(){return this->Root;}
void setRoot(bool _isRoot){this->Root = _isRoot;}


void addNodeChild(AnimationNode *node){
    if ((numChildren >= 0) && (numChildren < SIZE_NODES)){
        children[numChildren] = new AnimationNode(node);
        numChildren++;
    }
}

AnimationNode *getNodeChild(int index){
    if ((index >=0) && (index < numChildren)){
        return children[index];
    }else{
    //assert();
        return NULL;
    }
}

int getNumChildren(){this->numChildren;}

void CopyChildNodes(AnimationNode *animationNodeRef){
    clearNodeChilds();
    for(int i=0; i<animationNodeRef->getNumChildren(); i++) {
        children[i] = new AnimationNode(animationNodeRef);
    }
    this->numChildren = animationNodeRef->getNumChildren();
}

void clearNodeChilds(){
    for(int i=0; i<this->numChildren; i++){
        delete children[i];
    }
    numChildren = 0;
}

private:

uint32_t idAnimation;
uint32_t idNode;

uint32_t idTile;
uint32_t idMesh;

float xPos;
float yPos;
float length;
float angle;
bool Root;

int numChildren;

AnimationNode *children[SIZE_NODES]; //siete hijos por cada nodo

};



#endif // ANIMATIONNODE_H_INCLUDED
