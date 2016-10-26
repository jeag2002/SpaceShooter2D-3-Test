#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#define SIZE_MSG 90

/*
01-SET CONECTION
02-RESPONSE CONECTION
03-GET SESSION LIST
04-RESPONSE SESSION
05-SET CONNECTION TO SESSION
06-RESPONSE CONNECTION TO SESSION
07-COMMAND (MOVEMENT, SHOOT, CHANGE_WEAPON)
08-RESPONSE COMMAND
10-ORDER
11-RESPONSE ORDER
11-GET DATA FROM SERVER
12-OBTAIN DATA FROM SERVER
13-LOGOUT FROM SERVER
14-GET LOGOUT FROM SERVER
*/
#define TRAMA_SYNACK_CONECTION 0
#define TRAMA_QRY_CONECTION 1
#define TRAMA_GET_CONECTION 2

#define TRAMA_QRY_SESSION_LIST 3
#define TRAMA_GET_SESSION_LIST 4

#define TRAMA_SYNACK_SESSION 5
#define TRAMA_ACK_SESSION 6
#define TRAMA_NACK_SESSION 7

#define TRAMA_COMMAND 8
#define TRAMA_RES_COMMAND 9

#define TRAMA_SND_ORDER_TO_SERVER 10
#define TRAMA_CONFIRMORDER_FROM_SERVER 11
#define TRAMA_GETDATAFROMORDER_FROM_SERVER 12

#define TRAMA_QRY_DATASERVER 13
#define TRAMA_GET_DATASERVER 14
#define TRAMA_QRY_LOGOUT 15
#define TRAMA_GET_LOGOUT 16

#define TRAMA_NULL 99


//TRAMA COMMAND (TRAMA_COMMAND)
////////////////////////////////////////////////////////////////////
#define TYPE_COMMAND_MOVEMENT 1       /*Local player do a movement*/
#define TYPE_COMMAND_SHOOT 2          /*Local player do a shot*/
#define TYPE_COMMAND_CHGWPN 3         /*Local player do a change weapon*/
#define TYPE_COMMAND_EXIT 4           /*Local player exit the level*/
//16-07-2016: implemento hasta aquí... (esto para una segunda version si llega)

#define TYPE_COMMAND SWITCH 5         /*Local player active a switch*/
#define TYPE_COMMAND_GETITEM 6        /*Local player get item*/
#define TYPE_COMMAND_USEITEM 7        /*Local player use a item*/
#define TYPE_COMMAND_TELEPORT 8       /*Local player teleported*/
#define TYPE_COMMAND_OPENDOOR 9       /*Local player open a door*/
#define TYPE_COMMAND_USEBLOCK 10      /*Local player use a block*/
#define TYPE_COMMAND_FINDSECRET 11    /*Local player find a secret*/
////////////////////////////////////////////////////////////////////

//TRAMA ORDER_TO_SERVER (TRAMA_SND_ORDER_TO_SERVER)
////////////////////////////////////////////////////////////////////
#define TYPE_ORDER_GETLISTACTIVEPLAYER 1
////////////////////////////////////////////////////////////////////

//TRAMA GET DATA SERVER
////////////////////////////////////////////////////////////////////
#define TYPE_ACTIVE_ELEMENT 1         /*Enemies*/
#define TYPE_ACTIVEOTHER_ELEMENT 2    /*Other active elements*/
#define TYPE_PASIVE_ELEMENT 3         /*Pasive elements*/
#define TYPE_REM_PLAYER_ELEMENT 4     /*Remote Players*/
#define TYPE_SOUNDS 5                 /*Remote Sounds*/
#define TYPE_MSG_FROM_SERVER 6        /*Message from server*/
////////////////////////////////////////////////////////////////////


//LOCAL BEHAVIOUR PLAYER
////////////////////////////////////////////////////////////////////
#define MOVEMENT 1
#define SHT 2
#define CHGWPN 3
#define EXIT 4

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define MOUSE 5
////////////////////////////////////////////////////////////////////

//TRAMA CONFIRMATION/DEN PROCESS (TRAMA_CONFIRMORDER_FROM_SERVER; TRAMA_GET_CONECTION; TRAMA_GET_LOGOUT; TRAMA_RES_COMMAND)
////////////////////////////////////////////////////////////////////
#define OK 1
#define NOK 0
////////////////////////////////////////////////////////////////////

#define TYPE_MSG_ANSWER_CONNECTION 0
#define TYPE_MSG_ANSWER_SESSION 1
#define TYPE_MSG_ANSWER_COMMAND 2
#define TYPE_MSG_ANSWER_CONFIRMORDER 3
#define TYPE_MSG_ANSWER_LOGOUT 4

#define TYPE_LIST_SESSION_ID 1
#define TYPE_PLAYER_INI_SESSION_ID 2
#define TYPE_SERVER_DATA_ID 3

//list active maps/sessions
typedef struct{
    int listSessionsID;
    int map_1_id;
    int session_1_1;
    int num_player_max_1_1;
    int num_player_ava_1_1;
    int session_1_2;
    int num_player_max_1_2;
    int num_player_ava_1_2;
    int map_2_id;
    int session_2_1;
    int num_player_max_2_1;
    int num_player_ava_2_1;
    int session_2_2;
    int num_player_max_2_2;
    int num_player_ava_2_2;
}listSessionAvailableType;


//orders procesed to server
typedef struct{
    int orderID;
    int orderType;
    int actMap;
    int session;
    int value;
    int entityID;
    int level;
    float pos_x;
    float pos_y;
    int width;
    int height;
}OrderType;

//orders processed server-side (list of actual player)
typedef struct{
    int listOtherPlayerID;
    int playerID_1;
    int scoreID_1;
    int playerID_2;
    int scoreID_2;
    int playerID_3;
    int scoreID_3;
    int playerID_4;
    int scoreID_4;
}listOtherPlayersType;


//MSG from/to server
typedef struct{
   int msgTypeID;
   int actMap;
   int session;
   int originMsg; //(3)
   int endMsg;    //(3)
   char msg[SIZE_MSG]; //(97)
}msgType;

//commands in-game (player command) as local
typedef struct{
    int typeMovement;
    int idPlayer;
    float _inc;
    float _x;
    float _y;
    int shot;
    int oldWPN;
    int newWPN;
}localActionType;

//command in-game (movement)
typedef struct{
    int movementID;
    int actMap;
    int session;
    int idPlayer;
    int lvl;
    float x;
    float y;
    int width;
    int height;
}movementType;

//command in-game (shot)
typedef struct{
    int shotID;
    int actMap;
    int session;
    int idPlayer;
    int ammo;
}shotType;

//command in-game (chgweapon)
typedef struct{
    int changeWeaponID;
    int actMap;
    int session;
    int idPlayer;
    int oldWeaponId;
    int newWeaponId;
}changeWeaponType;

//command in-game (exit) ==> sale de la sesion, ha encontrado el final.
typedef struct{
    int exitID;
    int actMap;
    int session;
    int idPlayer;
    int level;
    float x;
    float y;
    int reason;
}exitType;

//command in-game (answer)
typedef struct{
    int trama;
    int type_trama;
    int command;
    int result;
}answerType;

//return session player
typedef struct{
    int playerDataID;
    int actMap;
    int session;
    int typeID;
    int idPlayer;
    int lvl;
    float x_pos;
    float y_pos;
    int width;
    int heigth;
}playerDataType;


//active element (Enemies/RemotePlayers/ActiveElements)
typedef struct{
    int typeTramaID;
    int typeID;
    int entityID;
    int actMap;
    int session;
    int idPlayer;
    int idParPlayer;
    int lvl;
    float x_pos;
    float y_pos;
    int width;
    int height;
    int life;
    int live;
    int shd;
    int act_wpn;
    int wpn_1;
    int ammo_wpn_1;
    int wpn_2;
    int ammo_wpn_2;
    int wpn_3;
    int ammo_wpn_3;
    int wpn_4;
    int ammo_wpn_4;
    int item_1;
    int item_1_val;
    int item_2;
    int item_2_val;
    int item_3;
    int item_3_val;
    int item_4;
    int item_4_val;
    int score;
    int die;
    int animIndex;
    int enabled;
}remotePlayerType;


typedef struct{
    const char *host;
    int port;
}remoteHostData;

//y = a + b*x
typedef struct{
    double ACoef;
    double BCoef;
    double CoefD;
    double CoefC;
    double stdError;
}coefLinRegresion;

typedef struct{
    double x;
    double y;
}positionXY;

#endif // CONSTANTS_H_INCLUDED
