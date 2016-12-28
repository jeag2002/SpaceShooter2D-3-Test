http://r3dux.org/2011/01/a-simple-sdl_net-chat-server-client/


Funcionamiento del cliente:

1-Se arranca después del servidor.
2-Inicializa variables de memoria.
3-dos procesos.
3.1-primer proceso, evalua los jugadores locales y envia msg al servidor
3.2-segundo proceso, recupera información del servidor del estado del mundo
4-gameplay.


Requerimientos, primera version.

Conexion Cliente-Servidor Local.

(
1-MODO CLIENTE

2-MODO CLIENTE-SERVIDOR LOCAL

2.1-1 Sesion de 1 Mapa. Habilitado para LANs (Basado en Sockets)
**************************************************************** ==> Primera versión MONOLITICA, soportará esto.
2.2-X Sesiones de 1 Mapa.
2.3-X Sesiones de X Mapas.
2.4-X Sesiones de X Mapas; definido por el cliente. (?)

3-MODO CLIENTE-SERVIDOR REMOTO (Cliente/Servidor Esclavo, Servidor Remoto Master. Basado en Sockets/MQSeries)
3.1-1 Sesion de 1 Mapa
3.2-X Sesiones de 1 Mapa
3.3-X Sesiones de X Mapas
3.4-X Sesiones de X Mapas; definido por el cliente (?)
)


TIPOS MENSAJE INPUT/OUTPUT:

1-GET CONNECTION TO SERVER
2-SET CONNECTION TO SERVER

1-GET SESSIONS
2-SET SESSIONS

1-SET CONNECT TO SESSION
2-GET CONNECT TO SESSION

1-SEND COMMAND TO SERVER

1-GET DATA FROM SERVER
2-RECEIVE DATA FROM SERVER

1-LOGOUT FROM SERVER
2-OK FROM SERVER.

TRAMA: Tramas de 128 bytes:

CABECERA (25 bytes):
TYPE(2)IDTRAMA(11)IDTRAMA(11)MORE(1)

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
   ENEMY/REM_PLAYER (3+1+5+5+5+5+1+3+3+2+(1+3)*10+10+5+1) = 89
   (Elementos: TYPE(3)
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

   ELEMENT (3+1+5+5+5+5)
   (Elementos: TYPE(3)
               LVL(1)
               ID(5)
               ID_FATH(5)
               POS_X(5)
               POS_Y(5)

   SOUND ()
   (Elementos: TYPE(3) LVL(1)POS_X(4)POS_Y(4) PADD(6))

   MSGFROMSERVER
   (Elementos: TYPE (3) MSG(100))

13-LOGOUT FROM SERVER
   <--->
14-GET LOGOUT FROM SERVER.
   CONFIRMACION (1+3)
   (Elementos: ID(1)
    MSG(3)==>OK/NOK
    )

CRC:


16-07-2016:
**************************************************************************************************************************
Tramas a programar en primera version:

1-Conectar a servidor (S/N)

2-Recuperar sesiones activas de servidor
  Respuesta:(Servidor,sesion,numero_jugadores,numero_jugadores_libres)

3-Conexion a servidor+sesion
  Respuesta:(Servidor,sesion,ok/nok,idjugador)

4-Comandos Jugador (Movimiento, Shot, ChangeWeapon, Exit)

5-Ordenes (Mensaje a X Jugador, Mensaje All Jugadores, lista Jugadores) ==> Descarto modificacion mapa en caliente (x)

6-Logout.

7-Actualizar Datos servidor (Actores, Msgs)

17-07-2016
Concretamos: 4 Players. 4 Sesiones x Mapa. 4 Mapas
**************************************************************************************************************************


https://github.com/anujagarwal464/SDL_net
