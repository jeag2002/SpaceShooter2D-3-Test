#ifndef EVENTMSG_H_INCLUDED
#define EVENTMSG_H_INCLUDED

#define BUFFER_SIZE 511
#define BUFFER_TRAMA 128
#define BUFFER_SUBTRAMA_INFO 95

#include "Constants.h"
#include "UtilsProtocol.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>#include <cstring>
#include <string>

#include <SDL_net.h>

/*

TRAMA: Tramas de 128 bytes:

CABECERA (25 bytes): TYPE(2)IDTRAMASEND(9)IDTRAMAGET(9)MORE(1)NUMTRAMAS(2)CRC16(2)

CUERPO (diferente x tipo de trama)

01-SET CONECTION (==> establece primera comunicacion con el servidor)
   <-->
02-RESPONSE CONECTION ( ==> el servidor está activo)
   CONFIRMACION (1+3)
   (Elementos: ID(1)
    MSG(3)==>OK/NOK
   )

03-GET SESSION LIST (==> busca las sesiones activas del servidor)
04-RESPONSE SESSION (SIZE * 20)
   (Elementos:
    SIZE(3) ->List Sessions
    [
    [ID_SESSION(4)ID_MAP(4)ID_PLAYERS(4)ID_PLAYERS_FREE(4)]
    ]


05-SET CONNECTION TO SESSION
   <-->

06-RESPONSE CONNECTION TO SESSION
   CONFIRMACION (1+3+5)
  (Elementos: ID(1)
   MSG(3)==>OK/NOK
   ID_PLAYER(5)
  )

07-COMMAND
   MOVEMENT (3+5+5+5)
   (Elementos: TYPE(3)
               ID_PLAYER(5)
               POS_X(5)
               POS_Y(5)
   )

   SHOOT (3+5+1+3)
   (Elementos: TYPE(3)
               ID_PLAYER(5)
               ID_WEAPON(1)
               AMMO(3)
    )

   CHGWEAPON (3+5+3+3)
   (Elementos: TYPE(3)
               ID_PLAYER(5)
               ID_WEAPON_OLD(3)
               ID_WEAPON_NEW(3)
    )

08-GET CONFIRMATION FROM SERVER.
    CONFIRMACION (1+3)
   (Elementos: ID(1)
    MSG(3)==>OK/NOK
   )

09-SEND COMMAND TO SERVER

   1-LIST_ACTIVE_PLAYERS
   2-LIST_ACTIVE_SESSIONS

   3-SEND MSG TO PLAYER
   4-SEND MSG TO ALL PLAYERS

   5-ADD ELEMENT TO LEVEL      (MODE CLIENT)
    (TYPE(3) LEVEL(1) POS_X(6) POS_Y(6) WIDTH(3) HEIGHT(3))
   6-REMOVE ELEMENT TO LEVEL   (MODE CLIENT)
   7-SAVE MODIFICATION TO FILE (MODE CLIENT)

10-GET ANSWER TO SERVER

11-GET DATA FROM SERVER

12-OBTAIN DATA FROM SERVER
   ENEMY/REM_PLAYER (3+3+1+5+5+5+5+1+3+3+2+(1+3)*10+10+5+1) = 89
   (Elementos: TYPE_DATA(3)
               TYPE(3)
               LVL(1)
               ID(5)
               ID_FATH(5)
               POS_X(5)
               POS_Y(5)
               LIFE(1)
               LIVE(3)
               SHD(3)
               ACT_WPN(2)
               WPN(1)AMMO(3) WPN(1)AMMO(3) WPN(1)AMMO(3) WPN(1)AMMO(3) WPN(1)AMMO(3) WPN(1)AMMO(3) WPN(1)AMMO(3) WPN(1)AMMO(3) WPN(1)AMMO(3) WPN(1)AMMO(3)
               ITEM(1) ITEM(1) ITEM(1) ITEM(1) ITEM(1) ITEM(1) ITEM(1) ITEM(1) ITEM(1) ITEM(1)
               SCORE(5) DIE(1)

   ELEMENT_ACTIVE (3+3+1+5+5+5+5)
   (Elementos: TYPE_DATA(3)
               TYPE(3)
               LVL(1)
               ID(5)
               ID_FATH(5)
               POS_X(5)
               POS_Y(5)

    ELEMENT_PASIVE()

   SOUND ()
   (Elementos: TYPE(3) LVL(1)POS_X(4)POS_Y(4) PADD(6))

   MSGFROMSERVER
   (Elementos: TYPE_DATA(3)
               TYPE (3)
               MSG(100)
    )

13-LOGOUT FROM SERVER
   <--->
14-GET LOGOUT FROM SERVER.
   CONFIRMACION (1+3)
   (Elementos: ID(1)
    MSG(3)==>OK/NOK
    )
*/



class EventMsg{

  public:

    EventMsg(){
        clearMsg();
    };

    //Commando local
    EventMsg(localActionType _lAction){
        clearMsg();
        setLocalActionType(_lAction);
    };

    //mensaje local
    EventMsg(msgType _mType){
        clearMsg();
        setMsgType(_mType);
    };

    EventMsg(shotType _sType){
        clearMsg();
        setShotType(_sType);
    };


    //orden local
    EventMsg(OrderType _oType){
        clearMsg();
        setOrderType(_oType);
    };

    //exit local
    EventMsg(exitType _eType){
        clearMsg();
        setExitType(_eType);
    }

    //TRAZAS UDP
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, UDPpacket *_packet){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = _packet;
    };

    //Evento Command local Player - movimiento
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, UDPpacket *_packet, movementType _mMovement){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = _packet;
        setMovementType(_mMovement);
    };

    //Evento Command local Player - shot
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, UDPpacket *_packet, shotType _sShot){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = _packet;
        setShotType(_sShot);
    };

    //Evento Command local Player - ChangeWpn
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, UDPpacket *_packet, changeWeaponType _cWeapon){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = _packet;
        setChangeWeaponType(_cWeapon);
    };

    //Evento Command local Player - Exit
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, UDPpacket *_packet, exitType _eType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = _packet;
        setExitType(_eType);
    };

    //Evento Get Remote server Data - Actor
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, UDPpacket *_packet, remotePlayerType _rPType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = _packet;
        setRemotePlayerType(_rPType);
    };

    //Evento Get Remote server Data - MSG
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, UDPpacket *_packet, msgType _mType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = _packet;
        setMsgType(_mType);
    };

    //Evento Command Answer
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, UDPpacket *_packet, answerType _aType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = _packet;
        setAnswerType(_aType);
    };

    //Evento Command ListActPlayer
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, UDPpacket *_packet, listOtherPlayersType _lOPType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = _packet;
        setListOtherPlayerType(_lOPType);
    };

    //Evento Command iistAvailable
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, UDPpacket *_packet, listSessionAvailableType _lSAType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = _packet;
        setListSessionAvaliableType(_lSAType);
    };

    //Evento Command get ID Player
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, UDPpacket *_packet, playerDataType _pDType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = _packet;
        setPlayerDataType(_pDType);
    };


    //Evento Orden al servidor
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, UDPpacket *_packet, OrderType _OType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = _packet;
        setOrderType(_OType);
    }

    //Evento Orden al servidor
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, UDPpacket *_packet, resultPingType _rPingType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = _packet;
        setResultPingType(_rPingType);
    }


    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, UDPpacket *_packet, predictionType _predictionType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = _packet;
        setPredictionType(_predictionType);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //END TRAZAS UDP



    //TRAZAS TCP
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = NULL;
    };

    //Evento Command local Player - movimiento
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, movementType _mMovement){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = NULL;
        setMovementType(_mMovement);
    };

    //Evento Command local Player - shot
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, shotType _sShot){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = NULL;
        setShotType(_sShot);
    };

    //Evento Command local Player - ChangeWpn
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, changeWeaponType _cWeapon){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = NULL;
        setChangeWeaponType(_cWeapon);
    };

    //Evento Command local Player - Exit
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, exitType _eType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = NULL;
        setExitType(_eType);
    };

    //Evento Get Remote server Data - Actor
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, remotePlayerType _rPType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = NULL;
        setRemotePlayerType(_rPType);
    };

    //Evento Get Remote server Data - MSG
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, msgType _mType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = NULL;
        setMsgType(_mType);
    };

    //Evento Command Answer
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, answerType _aType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = NULL;
        setAnswerType(_aType);
    };

    //Evento Command ListActPlayer
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, listOtherPlayersType _lOPType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = NULL;
        setListOtherPlayerType(_lOPType);
    };

    //Evento Command iistAvailable
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, listSessionAvailableType _lSAType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = NULL;
        setListSessionAvaliableType(_lSAType);
    };

    //Evento Command get ID Player
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, playerDataType _pDType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = NULL;
        setPlayerDataType(_pDType);
    };


    //Evento Orden al servidor
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, OrderType _OType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = NULL;
        setOrderType(_OType);
    }


     //Evento Orden al servidor
    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16, resultPingType _rPingType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = NULL;
        setResultPingType(_rPingType);
    }


    EventMsg(int _typeMsg, int _tramaSend, int _tramaGet, int _more, int _numtrazas, uint16_t _CRC16,  predictionType _predictionType){
        clearMsg();
        typeMsg = _typeMsg;
        tramaSend = _tramaSend;
        tramaGet = _tramaGet;
        more = _more;
        numtrazas = _numtrazas;
        CRC16 = _CRC16;
        packet = NULL;
        setPredictionType(_predictionType);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    EventMsg(EventMsg *_msg){
        setMsg(_msg);
    }

    ~EventMsg(){
        clearMsg();
     };


    int getTypeMsg(){return typeMsg;}
    void setTypeMsg(int _typeMsg){typeMsg = _typeMsg;}

    int getTramaSend(){return tramaSend;}
    void setTramaSend(int _tramaSend){tramaSend = _tramaSend;}

    int getTramaGet(){return tramaGet;}
    void setTramaGet(int _tramaGet){tramaGet = _tramaGet;}

    int getMore(){return more;}
    void setMore(int _more){more = _more;}

    int getNumTrazas(){return numtrazas;}
    void setNumTrazas(int _numtrazas){numtrazas = _numtrazas;}

    uint16_t getCRC16(){return CRC16;}
    void setCRC16(uint16_t _CRC16){CRC16 = _CRC16;}

    UDPpacket *getPacketUPD(){return packet;}
    void setPacketUPD(UDPpacket *_packet){packet = _packet;}


    std::string serializeMsg();

    //client side action
    ///////////////////////////////////////////////////////
    localActionType getLocalActionType(){return lAction;}
    void setLocalActionType(localActionType _lAction){
        lAction.idPlayer = _lAction.idPlayer;
        lAction.typeMovement = _lAction.typeMovement;
        lAction._inc = _lAction._inc;
        lAction._x = _lAction._x;
        lAction._y = _lAction._y;
        lAction.shot = _lAction.shot;
        lAction.newWPN = _lAction.newWPN;
        lAction.oldWPN = _lAction.oldWPN;
    }
    void clearLocalActionType(){
        lAction.typeMovement = 0;
        lAction._inc = 0.0f;
        lAction._x = 0.0f;
        lAction._y = 0.0f;
        lAction.shot = 0;
        lAction.newWPN = 0;
        lAction.oldWPN = 0;
    }
    //////////////////////////////////////////////////////

    //IN-COMMAND movement
    ///////////////////////////////////////////////////////
    movementType getMovementType(){return mMovement;}
    void setMovementType(movementType _mMovement){
        mMovement.actMap = _mMovement.actMap;
        mMovement.session = _mMovement.session;
        mMovement.lvl = _mMovement.lvl;
        mMovement.movementID = _mMovement.movementID;
        mMovement.idPlayer = _mMovement.idPlayer;
        mMovement.movementID = _mMovement.movementID;
        mMovement.x = _mMovement.x;
        mMovement.y = _mMovement.y;
        mMovement.width = _mMovement.width;
        mMovement.height = _mMovement.height;
        mMovement.velocity = _mMovement.velocity;
        mMovement.x_next = _mMovement.x_next;
        mMovement.y_next = _mMovement.y_next;
        mMovement.velocity_next = _mMovement.velocity_next;

    }
    void clearMovementType(){
        mMovement.idPlayer = 0;
        mMovement.actMap = 0;
        mMovement.lvl = 0;
        mMovement.session = 0;
        mMovement.movementID = 0;
        mMovement.x = 0;
        mMovement.y = 0;
        mMovement.velocity = 0;
        mMovement.width = 0;
        mMovement.height = 0;
        mMovement.x_next = 0;
        mMovement.y_next = 0;
        mMovement.velocity_next = 0;
    }
    ///////////////////////////////////////////////////////

    //IN-COMMAND shot
    ///////////////////////////////////////////////////////
    shotType getShotType(){return sShot;}
    void setShotType(shotType _sShot){
        sShot.actMap = _sShot.actMap;
        sShot.session = _sShot.session;
        sShot.shotID = _sShot.shotID;
        sShot.idPlayer = _sShot.idPlayer;
        sShot.ammo = _sShot.ammo;
    }
     void clearShotType(){
        sShot.actMap = 0;
        sShot.session = 0;
        sShot.shotID = 0;
        sShot.idPlayer = 0;
        sShot.ammo = 0;
    }
    ///////////////////////////////////////////////////////

    //IN-COMMAND changeWeapon
    //////////////////////////////////////////////////////
    changeWeaponType getChangeWeaponType(){return cWeapon;}
    void setChangeWeaponType(changeWeaponType _cWeapon){
        cWeapon.actMap = _cWeapon.actMap;
        cWeapon.session = _cWeapon.session;
        cWeapon.changeWeaponID = _cWeapon.changeWeaponID;
        cWeapon.idPlayer = _cWeapon.idPlayer;
        cWeapon.oldWeaponId = _cWeapon.oldWeaponId;
        cWeapon.newWeaponId = _cWeapon.newWeaponId;
    }
    void clearWeaponType(){
        cWeapon.changeWeaponID = 0;
        cWeapon.actMap = 0;
        cWeapon.session = 0;
        cWeapon.idPlayer = 0;
        cWeapon.oldWeaponId = 0;
        cWeapon.newWeaponId = 0;
    }
    //////////////////////////////////////////////////////

    //IN-COMMAND exit
    //////////////////////////////////////////////////////
    exitType getExitType(){return eType;}
    void setExitType(exitType _eType){
        eType.exitID = _eType.exitID;
        eType.idPlayer = _eType.idPlayer;
        eType.session = _eType.session;
        eType.actMap = _eType.actMap;
        eType.level = _eType.level;
        eType.x = _eType.x;
        eType.y = _eType.y;
        eType.reason = _eType.reason;
    }
    void clearExitType(){
        eType.exitID = 0;
        eType.idPlayer = 0;
        eType.actMap = 0;
        eType.session = 0;
        eType.level = 0;
        eType.x = 0;
        eType.y = 0;
        eType.reason = 0;
    }
    //////////////////////////////////////////////////////

    //REMOTE PLAYER-ENEMIES
    //////////////////////////////////////////////////////
    remotePlayerType getRemotePlayerType(){return rPType;}
    void setRemotePlayerType(remotePlayerType _rPType){
        rPType.typeTramaID = _rPType.typeTramaID;
        rPType.typeID = _rPType.typeID;
        rPType.entityID = _rPType.entityID;
        rPType.actMap = _rPType.actMap;
        rPType.session = _rPType.session;
        rPType.idPlayer = _rPType.idPlayer;
        rPType.idParPlayer = _rPType.idParPlayer;
        rPType.lvl = _rPType.lvl;
        rPType.x_pos = _rPType.x_pos;
        rPType.y_pos = _rPType.y_pos;
        rPType.width = _rPType.width;
        rPType.height = _rPType.height;
        rPType.life = _rPType.life;
        rPType.live = _rPType.live;
        rPType.shd = _rPType.shd;
        rPType.act_wpn = _rPType.act_wpn;
        rPType.wpn_1 = _rPType.wpn_1;
        rPType.ammo_wpn_1 = _rPType.ammo_wpn_1;
        rPType.wpn_2 = _rPType.wpn_2;
        rPType.ammo_wpn_2 = _rPType.ammo_wpn_2;
        rPType.wpn_3 = _rPType.wpn_3;
        rPType.ammo_wpn_3 = _rPType.ammo_wpn_3;
        rPType.wpn_4 = _rPType.wpn_4;
        rPType.ammo_wpn_4 = _rPType.ammo_wpn_4;
        rPType.item_1 = _rPType.item_1;
        rPType.item_1_val = _rPType.item_1_val;
        rPType.item_2 = _rPType.item_2;
        rPType.item_2_val = _rPType.item_2_val;
        rPType.item_3 = _rPType.item_3;
        rPType.item_3_val = _rPType.item_3_val;
        rPType.item_4 = _rPType.item_4;
        rPType.item_4_val = _rPType.item_4_val;
        rPType.score = _rPType.score;
        rPType.die = _rPType.die;
        rPType.animIndex = _rPType.animIndex;
        rPType.enabled = _rPType.enabled;
    }
    void clearRemotePlayerType(){
        rPType.typeTramaID = 0;
        rPType.typeID = 0;
        rPType.entityID = 0;
        rPType.actMap = 0;
        rPType.session = 0;
        rPType.idPlayer = 0;
        rPType.idParPlayer = 0;
        rPType.lvl = 0;
        rPType.x_pos = 0;
        rPType.y_pos = 0;
        rPType.width = 0;
        rPType.height = 0;
        rPType.life = 0;
        rPType.live = 0;
        rPType.shd = 0;
        rPType.act_wpn = 0;
        rPType.wpn_1 = 0;
        rPType.ammo_wpn_1 = 0;
        rPType.wpn_2 = 0;
        rPType.ammo_wpn_2 = 0;
        rPType.wpn_3 = 0;
        rPType.ammo_wpn_3 = 0;
        rPType.wpn_4 = 0;
        rPType.ammo_wpn_4 = 0;
        rPType.item_1 = 0;
        rPType.item_1_val = 0;
        rPType.item_2 = 0;
        rPType.item_2_val = 0;
        rPType.item_3 = 0;
        rPType.item_3_val = 0;
        rPType.item_4 = 0;
        rPType.item_4_val = 0;
        rPType.score = 0;
        rPType.die = 0;
        rPType.animIndex = 0;
        rPType.enabled = 0;
    }
    //////////////////////////////////////////////////////

    //MSG_TYPE
    //////////////////////////////////////////////////////
    msgType getMsgType(){return mType;}
    void setMsgType(msgType _mType){
        mType.actMap = _mType.actMap;
        mType.session = _mType.session;
        mType.msgTypeID = _mType.msgTypeID;
        mType.originMsg = _mType.originMsg;
        mType.endMsg = _mType.endMsg;
        for(int i=0; i<SIZE_MSG; i++){
            mType.msg[i] = _mType.msg[i];
        }
    }

    void clearMsgType(){
        mType.actMap = 0;
        mType.session = 0;
        mType.msgTypeID = 0;
        mType.originMsg = 0;
        mType.endMsg = 0;
        for(int i=0; i<SIZE_MSG; i++){
            mType.msg[i] = '\0';
        }
    }
    //////////////////////////////////////////////////////

    //ANSWER
    //////////////////////////////////////////////////////
    answerType getAnswerType(){return aType;}
    void setAnswerType(answerType _aType){
        aType.trama = _aType.trama;
        aType.type_trama = _aType.type_trama;
        aType.command = _aType.command;
        aType.result = _aType.result;
    }
    void clearAnswerType(){
        aType.trama = 0;
        aType.type_trama = 0;
        aType.command = 0;
        aType.result = 0;
    }
    //////////////////////////////////////////////////////

    //ORDERTYPE
    //////////////////////////////////////////////////////
    OrderType getOrderType(){return oType;}
    void setOrderType(OrderType _oType){
        oType.orderID = _oType.orderID;
        oType.orderType = _oType.orderType;
        oType.actMap = _oType.actMap;
        oType.session = _oType.session;
        oType.value = _oType.value;
        oType.entityID = _oType.entityID;
        oType.pos_x = _oType.pos_x;
        oType.pos_y = _oType.pos_y;
        oType.width = _oType.width;
        oType.height = _oType.height;
    }
    void clearOrderType(){
        oType.orderID = 0;
        oType.orderType = 0;
        oType.actMap = 0;
        oType.session = 0;
        oType.value = 0;
        oType.entityID = 0;
        oType.pos_x = 0;
        oType.pos_y = 0;
        oType.width = 0;
        oType.height = 0;
    }
    //////////////////////////////////////////////////////

    //LISTOTHERPLAYERS
    //////////////////////////////////////////////////////
    listOtherPlayersType getListOtherPlayersType(){return lOPType;}
    void setListOtherPlayerType(listOtherPlayersType _lOType){
        lOPType.listOtherPlayerID = _lOType.listOtherPlayerID;
        lOPType.playerID_1 = _lOType.playerID_1;
        lOPType.playerID_2 = _lOType.playerID_2;
        lOPType.playerID_3 = _lOType.playerID_3;
        lOPType.playerID_4 = _lOType.playerID_4;
        lOPType.scoreID_1 = _lOType.scoreID_1;
        lOPType.scoreID_2 = _lOType.scoreID_2;
        lOPType.scoreID_3 = _lOType.scoreID_3;
        lOPType.scoreID_4 = _lOType.scoreID_4;

    }
    void cleanListOtherPlayerType(){
        lOPType.playerID_1 = 0;
        lOPType.playerID_2 = 0;
        lOPType.playerID_3 = 0;
        lOPType.playerID_4 = 0;
        lOPType.scoreID_1 = 0;
        lOPType.scoreID_2 = 0;
        lOPType.scoreID_3 = 0;
        lOPType.scoreID_4 = 0;
    }

    //////////////////////////////////////////////////////

    //LISTSESSIONSAVALIABLES
    //////////////////////////////////////////////////////
    listSessionAvailableType getListSessionAvailableType(){return lSAType;}

    void setListSessionAvaliableType(listSessionAvailableType _lSAType){
        lSAType.listSessionsID = _lSAType.listSessionsID;
        lSAType.map_1_id = _lSAType.map_1_id;
        lSAType.map_2_id = _lSAType.map_2_id;
        lSAType.num_player_ava_1_1 = _lSAType.num_player_ava_1_1;
        lSAType.num_player_ava_1_2 = _lSAType.num_player_ava_1_2;
        lSAType.num_player_ava_2_1 = _lSAType.num_player_ava_2_1;
        lSAType.num_player_ava_2_2 = _lSAType.num_player_ava_2_2;
        lSAType.num_player_max_1_1 = _lSAType.num_player_max_1_1;
        lSAType.num_player_max_1_2 = _lSAType.num_player_max_1_2;
        lSAType.num_player_max_2_1 = _lSAType.num_player_max_2_1;
        lSAType.num_player_max_2_2 = _lSAType.num_player_max_2_2;
        lSAType.session_1_1 = _lSAType.session_1_1;
        lSAType.session_1_2 = _lSAType.session_1_2;
        lSAType.session_2_1 = _lSAType.session_2_1;
        lSAType.session_2_2 = _lSAType.session_2_2;
    }

    void cleanListSessionAvailableType(){
        lSAType.listSessionsID = 0;
        lSAType.map_1_id = 0;
        lSAType.map_2_id = 0;
        lSAType.num_player_ava_1_1 = 0;
        lSAType.num_player_ava_1_2 = 0;
        lSAType.num_player_ava_2_1 = 0;
        lSAType.num_player_ava_2_2 = 0;
        lSAType.num_player_max_1_1 = 0;
        lSAType.num_player_max_1_2 = 0;
        lSAType.num_player_max_2_1 = 0;
        lSAType.num_player_max_2_2 = 0;
        lSAType.session_1_1 = 0;
        lSAType.session_1_2 = 0;
        lSAType.session_2_1 = 0;
        lSAType.session_2_2 = 0;
    }
    //////////////////////////////////////////////////////

    //
    //////////////////////////////////////////////////////
    playerDataType getPlayerDataType(){return pDType;}
    void setPlayerDataType(playerDataType _pDType){
        pDType.playerDataID = _pDType.playerDataID;
        pDType.actMap = _pDType.actMap;
        pDType.session = _pDType.session;
        pDType.idPlayer = _pDType.idPlayer;
        pDType.typeID = _pDType.typeID;
        pDType.lvl = _pDType.lvl;
        pDType.x_pos = _pDType.x_pos;
        pDType.y_pos = _pDType.y_pos;
        pDType.width = _pDType.width;
        pDType.heigth = _pDType.heigth;
    }
    void clearPlayerDataType(){
        pDType.playerDataID = 0;
        pDType.actMap = 0;
        pDType.session = 0;
        pDType.idPlayer = 0;
        pDType.typeID = 0;
        pDType.lvl = 0;
        pDType.x_pos = 0.0f;
        pDType.y_pos = 0.0f;
        pDType.width = 0;
        pDType.heigth = 0;
    }
    //////////////////////////////////////////////////////

    predictionType getPredictionType(){return predicType;}
    void setPredictionType(predictionType _predictionType){
        predicType.predictionID = _predictionType.predictionID;
        predicType.actMap = _predictionType.actMap;
        predicType.session = _predictionType.session;
        predicType.idPlayer = _predictionType.idPlayer;
        predicType.lvl = _predictionType.lvl;
        predicType.velocity = _predictionType.velocity;
        predicType.velocity_next = _predictionType.velocity_next;
        predicType.x = _predictionType.x;
        predicType.x_next = _predictionType.x_next;
        predicType.y = _predictionType.y;
        predicType.y_next = _predictionType.y_next;
    }

    void clearPredictionType(){
        predicType.predictionID = 0;
        predicType.actMap = 0;
        predicType.session = 0;
        predicType.idPlayer = 0;
        predicType.lvl = 0;
        predicType.velocity = 0.0f;
        predicType.velocity_next = 0.0f;
        predicType.x = 0.0f;
        predicType.x_next = 0.0f;
        predicType.y = 0.0f;
        predicType.y_next = 0.0f;
    }
    //
    //////////////////////////////////////////////////////
    resultPingType getResultPingType(){return rPingType;}
    void setResultPingType(resultPingType _rPingType){
       rPingType.millisping = _rPingType.millisping;
       rPingType.indexAuthServer = _rPingType.indexAuthServer;
    }
    void clearResultPingType(){
        rPingType.millisping = 0;
        rPingType.indexAuthServer = 0;
    }
    //////////////////////////////////////////////////////


    char *getBuffer(){return buffer;}
    void copyBuffer(char *buffer_old){
        for(int i=0; i<BUFFER_SIZE; i++){buffer[i] = buffer_old[i];}
    }

    void setMsg(EventMsg *_remoteMsg){

        typeMsg = _remoteMsg->getTypeMsg();
        tramaSend = _remoteMsg->getTramaSend();
        tramaGet = _remoteMsg->getTramaSend();
        more = _remoteMsg->getMore();
        numtrazas = _remoteMsg->getNumTrazas();
        CRC16 = _remoteMsg->getCRC16();
        packet = _remoteMsg->getPacketUPD();

        copyBuffer(_remoteMsg->getBuffer());

        setLocalActionType(_remoteMsg->getLocalActionType());
        setMovementType(_remoteMsg->getMovementType());
        setShotType(_remoteMsg->getShotType());
        setRemotePlayerType(_remoteMsg->getRemotePlayerType());
        setExitType(_remoteMsg->getExitType());

        setChangeWeaponType(_remoteMsg->getChangeWeaponType());
        setAnswerType(_remoteMsg->getAnswerType());
        setPlayerDataType(_remoteMsg->getPlayerDataType());

        setMsgType(_remoteMsg->getMsgType());
        setListOtherPlayerType(_remoteMsg->getListOtherPlayersType());
        setListSessionAvaliableType(_remoteMsg->getListSessionAvailableType());

        setOrderType(_remoteMsg->getOrderType());

        setResultPingType(_remoteMsg->getResultPingType());
        setPredictionType(_remoteMsg->getPredictionType());

    };

    char *marshallMsg();
    void unmarshallMsg(const char *buffer);

    void clearBuffer(){
        for(int i=0; i<BUFFER_SIZE; i++){buffer[i] = '\0';}
    }

    void clearMsg(){
        tramaGet = 0;
        typeMsg = TRAMA_NULL;
        tramaSend = 0;
        more = 0;
        numtrazas = 0;
        CRC16 = 0;
        packet = NULL;

        clearBuffer();

        //IN GAME COMMANDS
        //////////////////////////
        clearLocalActionType();
        clearMovementType();
        clearShotType();
        clearWeaponType();
        clearExitType();
        //////////////////////////

        //ORDER COMMANDS
        //////////////////////////
        clearOrderType();
        cleanListSessionAvailableType();
        //////////////////////////

        //REMOTE DATA
        //////////////////////////
        clearRemotePlayerType();
        clearMsgType();
        //////////////////////////

        //ANSWERS
        //////////////////////////
        clearAnswerType();
        cleanListOtherPlayerType();
        clearPlayerDataType();
        //////////////////////////

        clearResultPingType();
        clearPredictionType();


    }


  private:

    int typeMsg;
    int tramaSend;
    int tramaGet;
    int numtrazas;
    int more;
    uint16_t CRC16;
    //solo para tramas UDP.
    UDPpacket *packet;

    char buffer[BUFFER_SIZE];

    localActionType lAction;
    //INGAME_MOVEMENTS
    movementType mMovement;
    shotType sShot;
    changeWeaponType cWeapon;
    exitType eType;

    //COMMAND GAMES
    OrderType oType;

    //REMOTE PLAYER/ENEMIES
    remotePlayerType rPType;
    msgType mType;

    //LIST OTHER PLAYERS
    listOtherPlayersType lOPType;
    listSessionAvailableType lSAType;

    //ANSWER TYPE.
    answerType aType;
    playerDataType pDType;

    //RESULT TYPE
    resultPingType rPingType;

    //PREDICTION TYPE
    predictionType predicType;

    OrderType processSubMsgOType(const char *subbuffer);
    msgType processSubMsgMType(const char *subbuffer);
    answerType processSubMsgAType(const char *subbuffer);
    remotePlayerType processSubMsgrRType(const char *subbuffer);
    listOtherPlayersType processSubMsglOPT(const char *subbuffer);
    listSessionAvailableType processSubMsglSAType(const char *subbuffer);

    movementType processSubMsgMMovement(const char *subbuffer);
    shotType processSubMsgSShot(const char *subbuffer);
    changeWeaponType processSubMsgCWeapon(const char *subbuffer);
    exitType processSubMsgEType(const char *subbuffer);

    playerDataType processSubMsgPDType(const char *subbuffer);

    predictionType processPredictionType(const char *subbuffer);

};


#endif // EVENTMSG_H_INCLUDED
