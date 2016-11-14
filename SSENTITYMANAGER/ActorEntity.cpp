#include "ActorEntity.h"


/*
ID              INT       //identificador del ACTOR
ID_ANIMATION    INT       //identificador ANIMATION

INC             FLOAT
SHIELD          FLOAT
LIVE            FLOAT
SCORE           INT

SCRIPT_IA       CHAR(20)  //Comportamiento IA (Jugador, define el gameplay separado de su animacion)
LIMIT           CHAR(100) //nodos mapa colision. (mapa luz?)
SHADE           CHAR(100) //nodos mapa sombreado.

TABLE ENT_ACTOR_COMPONENT_ITEM //-->definicion componentes de un actor.

ID              INT            //identificador del componente
ID_ACTOR        INT            //identificador del actor.
ID_ITEM         INT            //identficador del item

TABLE ENT_ACTOR_COMPONENT_WEAPON //-->definicion componente armas

ID              INT           //identificador del componente
ID_ACTOR        INT           //identificador del actor.
ID_WEAPON       INT           //identificador del arma.

*/




void ActorEntity::marshallActorEntity(char **data){

    this->id = atoi(data[0]);
    this->live = atoi(data[1]);
    this->shield = atoi(data[2]);
    this->score = atoi(data[3]);
}

