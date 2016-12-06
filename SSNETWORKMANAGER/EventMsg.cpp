#include "EventMsg.h"


//HEAD OF TRAMA (CLIENT/SERVER) //--> CABECERA 33
//ESPACIO PARA SUBTRAMA CLIENTE //--> 128-33 = 95

char *EventMsg::marshallMsg(){
    clearBuffer();
    std::string dataSubMsg = serializeMsg();

    CRC16 = UtilsProtocol::calculateCRC16_CCITT((const unsigned char *)dataSubMsg.c_str(),dataSubMsg.size());
    sprintf (buffer, "%02d%011d%011d%01d%02d%06d%s", typeMsg, tramaSend, tramaGet, more, numtrazas, CRC16,dataSubMsg.c_str());

    return buffer;
}

//MESSAGE (CLIENT/SERVER)
msgType EventMsg::processSubMsgMType(const char *subbuffer){
    msgType mType;
    std::string buffer_to_string(subbuffer);
    std::string mapStr = buffer_to_string.substr(0,3);
    std::string sessionStr = buffer_to_string.substr(3,3);
    std::string tramaIDStr = buffer_to_string.substr(6,3);
    std::string originIDStr = buffer_to_string.substr(9,5);
    std::string destIDStr = buffer_to_string.substr(14,5);
    std::string msgStr = buffer_to_string.substr(19,74);

    int tramaIDInt = atoi(tramaIDStr.c_str());
    int mapInt = atoi(mapStr.c_str());
    int sessionInt = atoi(sessionStr.c_str());
    int originIDInt = atoi(originIDStr.c_str());
    int destIDInt = atoi(destIDStr.c_str());
    const char *buffer = msgStr.c_str();

    mType.msgTypeID = tramaIDInt;
    mType.actMap = mapInt;
    mType.session = sessionInt;
    mType.originMsg = originIDInt;
    mType.endMsg = destIDInt;

    for(int i=0; i<SIZE_MSG; i++){
        mType.msg[i] = '\0';
    }

    for(int i=0; i<74; i++){
        mType.msg[i] = buffer[i];
    }

    return mType;
}


//RESULT OF AN ACTION (CLIENT/SERVER)
answerType EventMsg::processSubMsgAType(const char *subbuffer){

    std::string buffer_to_string(subbuffer);
    std::string tramaStr = buffer_to_string.substr(0,11);       //(pos 0+11)
    std::string typeTramaStr = buffer_to_string.substr(11,2);   //(pos 2+11)
    std::string commandStr = buffer_to_string.substr(13,3);     //(pos 12+11)
    std::string resultStr = buffer_to_string.substr(16,1);      //(pos 22+1)

    int tramaInt = atoi(tramaStr.c_str());
    int typeTramaInt = atoi(typeTramaStr.c_str());
    int commandInt =  atoi(commandStr.c_str());
    int resultInt = atoi(resultStr.c_str());

    answerType aType;
    aType.trama = tramaInt;
    aType.type_trama = typeTramaInt;
    aType.command = commandInt;
    aType.result = resultInt;

    return aType;
}

//sprintf(subBuffer,"%03d%03d%03d%03d%03d%05d%05d%01d%06d%02d%06d%02d%03d%03d%01d%03d%03d
//%02d %01d%03d %01d%03d% 01d%03d %01d%03d
//%01d%02d %01d%02d %01d%02d %01d%02d
//%05d %01d %02d %01d",

//sprintf(subBuffer,"%03d%03d%03d%03d%03d%05d%05d%01d%06d%02d%06d%02d%03d%03d%01d%03d%03d
//%02d %01d%03d %01d%03d %01d%03d %01d%03d
//%01d%02d %01d%02d %01d%02d %01d%02d
//%05d %01d %02d% 01d",

//UNMARSHALL REMOTE ACTIVE ELEMENT (ACTOR) (CLIENT)
remotePlayerType EventMsg::processSubMsgrRType(const char *subbuffer){

    std::string buffer_to_string(subbuffer);
    std::string typeTramaIDStr = buffer_to_string.substr(0,3);  //0+3
    std::string typeIDStr = buffer_to_string.substr(3,3);       //3+3
    std::string typeEntityIDStr = buffer_to_string.substr(6,3); //6+3
    std::string typeMapIdStr = buffer_to_string.substr(9,3);    //9+3
    std::string typeSessionStr = buffer_to_string.substr(12,3); //12+3
    std::string idPlayerStr = buffer_to_string.substr(15,5);    //15+5
    std::string idParPlayerStr = buffer_to_string.substr(20,5); //20+5
    std::string lvlStr = buffer_to_string.substr(25,1);         //25+1
    std::string XPosStr = buffer_to_string.substr(26,6);        //26+6
    std::string XPosDecStr = buffer_to_string.substr(32,2);     //32+2
    std::string YPosStr = buffer_to_string.substr(34,6);        //34+6
    std::string YPosDecStr = buffer_to_string.substr(40,2);     //40+2
    std::string WidthStr = buffer_to_string.substr(42,3);       //42+3
    std::string HeightStr = buffer_to_string.substr(45,3);      //45+3
    std::string lifeStr = buffer_to_string.substr(48,1);        //48+1
    std::string liveStr = buffer_to_string.substr(49,3);        //49+3
    std::string ShdStr = buffer_to_string.substr(52,3);         //52+3
    std::string ActWpnStr = buffer_to_string.substr(55,2);      //55+2
    std::string Wpn1Str = buffer_to_string.substr(57,1);        //57+1
    std::string Wpn1AmmoStr = buffer_to_string.substr(58,3);    //58+3
    std::string Wpn2Str = buffer_to_string.substr(61,1);        //61+1
    std::string Wpn2AmmoStr = buffer_to_string.substr(62,3);    //62+3
    std::string Wpn3Str = buffer_to_string.substr(65,1);        //65+1
    std::string Wpn3AmmoStr = buffer_to_string.substr(66,3);    //66+3
    std::string Wpn4Str = buffer_to_string.substr(69,1);        //69+1
    std::string Wpn4AmmoStr = buffer_to_string.substr(70,3);    //70+3

    std::string Item1Str = buffer_to_string.substr(73,1);       //73+1
    std::string Item1ValStr = buffer_to_string.substr(74,2);    //74+2
    std::string Item2Str = buffer_to_string.substr(76,1);       //76+1
    std::string Item2ValStr = buffer_to_string.substr(77,2);    //77+2
    std::string Item3Str = buffer_to_string.substr(79,1);       //79+1
    std::string Item3ValStr = buffer_to_string.substr(80,2);    //80+2
    std::string Item4Str = buffer_to_string.substr(82,1);       //82+1
    std::string Item4ValStr = buffer_to_string.substr(83,2);    //83+2

    std::string ScoreStr = buffer_to_string.substr(85,5);       //85+5
    std::string DieStr = buffer_to_string.substr(90,1);         //90+1
    std::string AnimIndexStr = buffer_to_string.substr(91,2);   //91+2
    std::string enabledStr = buffer_to_string.substr(93,1);     //93+1

    int typeTramaIDInt = atoi(typeTramaIDStr.c_str());
    int typeIDSInt = atoi(typeIDStr.c_str());
    int typeEntityIDInt = atoi(typeEntityIDStr.c_str());
    int mapInt = atoi(typeMapIdStr.c_str());
    int sessionInt = atoi(typeSessionStr.c_str());
    int idPlayerInt = atoi(idPlayerStr.c_str());
    int idParPlayerInt = atoi(idParPlayerStr.c_str());
    int lvlInt = atoi(lvlStr.c_str());
    float XPosInt = atof(XPosStr.c_str()) + (((float)atof(XPosDecStr.c_str())) * 0.01f);
    float YPosInt = atof(YPosStr.c_str()) + (((float)atof(YPosDecStr.c_str())) * 0.01f);
    int WidthInt = atoi(WidthStr.c_str());
    int HeightInt = atoi(HeightStr.c_str());
    int lifeInt = atoi(lifeStr.c_str());
    int liveInt = atoi(liveStr.c_str());
    int shdInt = atoi(ShdStr.c_str());
    int ActWpnInt = atoi(ActWpnStr.c_str());
    int Wpn1Int = atoi(Wpn1Str.c_str());
    int Wpn1AmmoInt = atoi(Wpn1AmmoStr.c_str());
    int Wpn2Int = atoi(Wpn2Str.c_str());
    int Wpn2AmmoInt = atoi(Wpn2AmmoStr.c_str());
    int Wpn3Int = atoi(Wpn3Str.c_str());
    int Wpn3AmmoInt = atoi(Wpn3AmmoStr.c_str());
    int Wpn4Int = atoi(Wpn4Str.c_str());
    int Wpn4AmmoInt = atoi(Wpn4AmmoStr.c_str());
    int Item1Int = atoi(Item1Str.c_str());
    int Item1ValInt = atoi(Item1ValStr.c_str());
    int Item2Int = atoi(Item2Str.c_str());
    int Item2ValInt = atoi(Item2ValStr.c_str());
    int Item3Int = atoi(Item3Str.c_str());
    int Item3ValInt = atoi(Item3ValStr.c_str());
    int Item4Int = atoi(Item4Str.c_str());
    int Item4ValInt = atoi(Item4ValStr.c_str());
    int ScoreInt = atoi(ScoreStr.c_str());
    int DieInt = atoi(DieStr.c_str());
    int AnimIndexInt = atoi(AnimIndexStr.c_str());
    int EnabledInt = atoi(enabledStr.c_str());

    remotePlayerType rPType;

    rPType.typeTramaID = typeTramaIDInt;
    rPType.typeID = typeIDSInt;
    rPType.entityID = typeEntityIDInt;
    rPType.actMap = mapInt;
    rPType.session = sessionInt;
    rPType.idPlayer = idPlayerInt;
    rPType.idParPlayer = idParPlayerInt;
    rPType.lvl = lvlInt;
    rPType.x_pos = XPosInt;
    rPType.y_pos = YPosInt;
    rPType.width = WidthInt;
    rPType.height = HeightInt;
    rPType.life = lifeInt;
    rPType.live = liveInt;
    rPType.shd = shdInt;
    rPType.act_wpn = ActWpnInt;
    rPType.wpn_1 = Wpn1Int;
    rPType.ammo_wpn_1 = Wpn1AmmoInt;
    rPType.wpn_2 = Wpn2Int;
    rPType.ammo_wpn_2 = Wpn2AmmoInt;
    rPType.wpn_3 = Wpn3Int;
    rPType.ammo_wpn_3 = Wpn3AmmoInt;
    rPType.wpn_4 = Wpn4Int;
    rPType.ammo_wpn_4 = Wpn4AmmoInt;
    rPType.item_1 = Item1Int;
    rPType.item_1_val = Item1ValInt;
    rPType.item_2 = Item2Int;
    rPType.item_2_val = Item2ValInt;
    rPType.item_3 = Item3Int;
    rPType.item_3_val = Item3ValInt;
    rPType.item_4 = Item4Int;
    rPType.item_4_val = Item4ValInt;
    rPType.score = ScoreInt;
    rPType.die = DieInt;
    rPType.animIndex = AnimIndexInt;
    rPType.enabled = EnabledInt;

    return rPType;
}

//GET STATUS OF ALL PLAYERS OF THE SAME SESSION/SAME MAP (CLIENT)
listOtherPlayersType EventMsg::processSubMsglOPT(const char *subbuffer){

    listOtherPlayersType lOPTypeData;

    std::string buffer_to_string(subbuffer);
    std::string typeTramaStr = buffer_to_string.substr(0,3);

    std::string idPlayerID1Str = buffer_to_string.substr(3,5);
    std::string idPlayerScore1Str = buffer_to_string.substr(8,5);

    std::string idPlayerID2Str = buffer_to_string.substr(13,5);
    std::string idPlayerScore2Str = buffer_to_string.substr(18,5);

    std::string idPlayerID3Str = buffer_to_string.substr(23,5);
    std::string idPlayerScore3Str = buffer_to_string.substr(28,5);

    std::string idPlayerID4Str = buffer_to_string.substr(33,5);
    std::string idPlayerScore4Str = buffer_to_string.substr(38,5);

    int typeTramaInt = atoi(typeTramaStr.c_str());

    int idPlayerID1Int = atoi(idPlayerID1Str.c_str());
    int idPlayerScore1Int = atoi(idPlayerScore1Str.c_str());

    int idPlayerID2Int = atoi(idPlayerID2Str.c_str());
    int idPlayerScore2Int = atoi(idPlayerScore2Str.c_str());

    int idPlayerID3Int = atoi(idPlayerID3Str.c_str());
    int idPlayerScore3Int = atoi(idPlayerScore3Str.c_str());

    int idPlayerID4Int = atoi(idPlayerID4Str.c_str());
    int idPlayerScore4Int = atoi(idPlayerScore4Str.c_str());

    return lOPTypeData;
}


//PROCESS REMOTE ORDERS FROM CLIENT (SERVER)
OrderType EventMsg::processSubMsgOType(const char *subbuffer){
    OrderType oType;

    std::string buffer_to_string(subbuffer);
    std::string orderIDStr = buffer_to_string.substr(0,3);
    std::string orderTypeStr = buffer_to_string.substr(3,3);
    std::string actMapStr = buffer_to_string.substr(6,3);
    std::string sessionStr = buffer_to_string.substr(9,3);
    std::string orderValueStr = buffer_to_string.substr(12,5);
    std::string entityIDStr = buffer_to_string.substr(17,3);
    std::string levelStr = buffer_to_string.substr(21,3);
    std::string posXStr = buffer_to_string.substr(23,6);
    std::string posXDecStr = buffer_to_string.substr(29,2);
    std::string posYStr = buffer_to_string.substr(31,6);
    std::string posYDecStr = buffer_to_string.substr(37,2);
    std::string widthStr = buffer_to_string.substr(39,3);
    std::string heightStr = buffer_to_string.substr(42,3);

    int orderIDInt = atoi(orderIDStr.c_str());
    int orderTypeInt = atoi(orderTypeStr.c_str());
    int actMapInt = atoi(actMapStr.c_str());
    int sessionInt = atoi(sessionStr.c_str());
    int orderValueInt = atoi(orderValueStr.c_str());
    int levelInt = atoi(levelStr.c_str());
    int entityIDInt = atoi(entityIDStr.c_str());
    float x = atof(posXStr.c_str());
    float x_dec = atof(posXDecStr.c_str()) * 0.01;
    float y = atof(posYStr.c_str());
    float y_dec = atof(posYDecStr.c_str()) * 0.01;
    int widthInt = atoi(widthStr.c_str());
    int heightInt = atoi(heightStr.c_str());


    oType.orderID = orderIDInt;
    oType.orderType = orderTypeInt;
    oType.actMap = actMapInt;
    oType.session = sessionInt;
    oType.value = orderValueInt;
    oType.entityID = entityIDInt;
    oType.level = levelInt;
    oType.pos_x = x + x_dec;
    oType.pos_y = y + y_dec;
    oType.width = widthInt;
    oType.height = heightInt;


    return oType;
}

//get List Avaliables MAPS/SESSIONS (CLIENT)
listSessionAvailableType EventMsg::processSubMsglSAType(const char *subbuffer){
    listSessionAvailableType lSAType;
    std::string buffer_to_string(subbuffer);
    std::string listSessionIDStr = buffer_to_string.substr(0,3);
    std::string map1IDStr = buffer_to_string.substr(3,3);
    std::string session11Str = buffer_to_string.substr(6,3);
    std::string maxPlayer11Str = buffer_to_string.substr(9,3);
    std::string numPlayer11Str = buffer_to_string.substr(12,3);
    std::string session12Str = buffer_to_string.substr(15,3);
    std::string maxPlayer12Str = buffer_to_string.substr(18,3);
    std::string numPlayer12Str = buffer_to_string.substr(21,3);
    std::string map2IDStr = buffer_to_string.substr(24,3);
    std::string session21Str = buffer_to_string.substr(27,3);
    std::string maxPlayer21Str = buffer_to_string.substr(30,3);
    std::string numPlayer21Str = buffer_to_string.substr(33,3);
    std::string session22Str = buffer_to_string.substr(36,3);
    std::string maxPlayer22Str = buffer_to_string.substr(39,3);
    std::string numPlayer22Str = buffer_to_string.substr(42,3);


    int listSessionIDInt = atoi(listSessionIDStr.c_str());
    int map1IDInt = atoi(map1IDStr.c_str());
    int session11Int = atoi(session11Str.c_str());
    int maxPlayer11Int = atoi(maxPlayer11Str.c_str());
    int numPlayer11Int = atoi(numPlayer11Str.c_str());
    int session12Int = atoi(session12Str.c_str());
    int maxPlayer12Int = atoi(maxPlayer12Str.c_str());
    int numPlayer12Int = atoi(numPlayer12Str.c_str());
    int map2IDInt = atoi(map2IDStr.c_str());
    int session21Int = atoi(session21Str.c_str());
    int maxPlayer21Int = atoi(maxPlayer21Str.c_str());
    int numPlayer21Int = atoi(numPlayer21Str.c_str());
    int session22Int = atoi(session22Str.c_str());
    int maxPlayer22Int = atoi(maxPlayer22Str.c_str());
    int numPlayer22Int = atoi(numPlayer22Str.c_str());

    lSAType.listSessionsID = listSessionIDInt;
    lSAType.map_1_id = map1IDInt;
    lSAType.session_1_1 = session11Int;
    lSAType.num_player_max_1_1 = maxPlayer11Int;
    lSAType.num_player_ava_1_1 = numPlayer11Int;
    lSAType.session_1_2 = session12Int;
    lSAType.num_player_max_1_2 = maxPlayer12Int;
    lSAType.num_player_ava_1_2 = numPlayer12Int;
    lSAType.map_2_id =  map2IDInt;
    lSAType.session_2_1 = session21Int;
    lSAType.num_player_max_2_1 = maxPlayer21Int;
    lSAType.num_player_ava_2_1 = numPlayer21Int;
    lSAType.session_2_2 = session22Int;
    lSAType.num_player_max_2_2 = maxPlayer22Int;
    lSAType.num_player_ava_2_2 = numPlayer22Int;


    return lSAType;
}

//movement COMMAND LOCAL_PLAYER (SERVER)
movementType EventMsg::processSubMsgMMovement(const char *subbuffer){
    movementType mMovement;
    std::string buffer_to_string(subbuffer);

    std::string movementIDStr = buffer_to_string.substr(0,3);
    std::string movementMapStr = buffer_to_string.substr(3,3);
    std::string movementSessionStr = buffer_to_string.substr(6,3);

    std::string idPlayerStr = buffer_to_string.substr(9,5);
    std::string idLvlStr = buffer_to_string.substr(14,1);

    std::string xStr = buffer_to_string.substr(15,6);
    std::string xDecStr = buffer_to_string.substr(21,2);
    std::string yStr = buffer_to_string.substr(23,6);
    std::string yDecStr = buffer_to_string.substr(29,2);
    std::string widthStr = buffer_to_string.substr(31,3);
    std::string heightStr = buffer_to_string.substr(34,3);

    int movementIDInt = atoi(movementIDStr.c_str());
    int movementMapInt = atoi(movementMapStr.c_str());
    int movementSessionInt = atoi(movementSessionStr.c_str());

    int idPlayerInt = atoi(idPlayerStr.c_str());
    int idLvlInt = atoi(idLvlStr.c_str());

    float x = atof(xStr.c_str());
    float xDec = atof(xDecStr.c_str()) * 0.01f;
    float y = atof(yStr.c_str());
    float yDec = atof(yDecStr.c_str()) * 0.01f;
    int width = atoi(widthStr.c_str());
    int height = atoi(heightStr.c_str());


    mMovement.movementID = movementIDInt;
    mMovement.actMap = movementMapInt;
    mMovement.session = movementSessionInt;

    mMovement.idPlayer = idPlayerInt;
    mMovement.lvl = idLvlInt;
    mMovement.x = x+xDec;
    mMovement.y = y+yDec;
    mMovement.width = width;
    mMovement.height = height;

    return mMovement;
}

//shot COMMAND LOCAL_PLAYER (SERVER)
shotType EventMsg::processSubMsgSShot(const char *subbuffer){
    shotType sShot;

    std::string buffer_to_string(subbuffer);
    std::string shotIDStr = buffer_to_string.substr(0,3);
    std::string shotMapStr = buffer_to_string.substr(3,3);
    std::string shotSessionStr = buffer_to_string.substr(6,3);
    std::string playerIDStr = buffer_to_string.substr(9,5);
    std::string ammoStr = buffer_to_string.substr(14,3);

    int shotInt = atoi(shotIDStr.c_str());
    int shotMapInt = atoi(shotMapStr.c_str());
    int shotSessionInt = atoi(shotSessionStr.c_str());

    int playerInt = atoi(playerIDStr.c_str());
    int ammoInt = atoi(ammoStr.c_str());

    sShot.shotID = shotInt;
    sShot.actMap = shotMapInt;
    sShot.session = shotSessionInt;
    sShot.idPlayer = playerInt;
    sShot.ammo = ammoInt;


    return sShot;
}

//change weapon COMMAND LOCAL_PLAYER (SERVER)
changeWeaponType EventMsg::processSubMsgCWeapon(const char *subbuffer){

    changeWeaponType cWeapon;

    std::string buffer_to_string(subbuffer);
    std::string changeWeaponIDStr = buffer_to_string.substr(0,3);
    std::string changeWeaponMapStr = buffer_to_string.substr(3,3);
    std::string changeWeaponSessionStr = buffer_to_string.substr(6,3);
    std::string playerIDStr = buffer_to_string.substr(9,5);
    std::string oldWeaponIDStr = buffer_to_string.substr(14,3);
    std::string newWeaponIDStr = buffer_to_string.substr(17,3);

    int changeWeaponInt = atoi(changeWeaponIDStr.c_str());
    int changeWeaponMapInt = atoi(changeWeaponMapStr.c_str());
    int changeWeaponSessionInt = atoi(changeWeaponSessionStr.c_str());
    int idPlayerInt = atoi(playerIDStr.c_str());
    int oldWeaponInt = atoi(oldWeaponIDStr.c_str());
    int newWeaponInt = atoi(newWeaponIDStr.c_str());

    cWeapon.changeWeaponID = changeWeaponInt;
    cWeapon.actMap = changeWeaponInt;
    cWeapon.session = changeWeaponSessionInt;
    cWeapon.idPlayer = idPlayerInt;
    cWeapon.oldWeaponId = oldWeaponInt;
    cWeapon.newWeaponId = newWeaponInt;

    return cWeapon;

}

//exit IN-COMMAND LOCAL PLAYER. (SERVER)
exitType EventMsg::processSubMsgEType(const char *subbuffer){

    exitType eType;

    std::string buffer_to_string(subbuffer);
    std::string exitIDStr = buffer_to_string.substr(0,3);
    std::string idPlayerStr = buffer_to_string.substr(3,5);
    std::string idActMapStr = buffer_to_string.substr(8,3);
    std::string sessionStr = buffer_to_string.substr(11,3);
    std::string levelStr = buffer_to_string.substr(14,1);
    std::string xStr = buffer_to_string.substr(15,6);
    std::string xDecStr = buffer_to_string.substr(21,2);
    std::string yStr = buffer_to_string.substr(23,6);
    std::string yDecStr = buffer_to_string.substr(29,2);
    std::string reasonStr = buffer_to_string.substr(31,3);

    int exitIDInt = atoi(exitIDStr.c_str());
    int idPlayerInt = atoi(idPlayerStr.c_str());
    int actMapInt = atoi(idActMapStr .c_str());
    int sessionInt = atoi(sessionStr.c_str());
    int levelInt = atoi(levelStr.c_str());
    float xFloat = atof(xStr.c_str());
    float xDecFloat = atof(xDecStr.c_str()) * 0.01f;
    float yFloat = atof(yStr.c_str());
    float yDecFloat = atof(yDecStr.c_str()) * 0.01f;
    int reasonInt = atoi(reasonStr.c_str());

    eType.exitID = exitIDInt;
    eType.idPlayer = idPlayerInt;
    eType.session = sessionInt;
    eType.level = levelInt;
    eType.x = xFloat + xDecFloat;
    eType.y = yFloat + yDecFloat;
    eType.reason = reasonInt;

    return eType;
}

/*
 sprintf(subBuffer,"%03d%03d%03d%03d%05d%03d%06d%02d%06d%02d%03d%03d",
                pDType.playerDataID,
                pDType.actMap,
                pDType.session,
                pDType.typeID,
                pDType.idPlayer,
                pDType.lvl,
                (int)pDType.x_pos,
                fractional_part_as_int(pDType.x_pos,2),
                (int)pDType.y_pos,
                fractional_part_as_int(pDType.y_pos,2),
                pDType.width,
                pDType.heigth
                );
*/


//GET ID PLAYER (SERVER/CLIENT)
//"%03d%03d%03d%05d%01d%06d%02d%06d%02d%03d%03d"
playerDataType EventMsg::processSubMsgPDType(const char *subbuffer){

    playerDataType pDType;
    std::string buffer_to_string(subbuffer);
    std::string playerIDStr = buffer_to_string.substr(0,3);
    std::string actMapStr = buffer_to_string.substr(3,3);
    std::string sessionStr = buffer_to_string.substr(6,3);
    std::string typeIDStr = buffer_to_string.substr(9,3);
    std::string idPlayerStr = buffer_to_string.substr(12,5);
    std::string lvlStr = buffer_to_string.substr(17,3);
    std::string xPosStr = buffer_to_string.substr(20,6);
    std::string xPosDecStr = buffer_to_string.substr(26,2);
    std::string yPosStr = buffer_to_string.substr(28,6);
    std::string yPosDecStr = buffer_to_string.substr(34,2);
    std::string widthStr = buffer_to_string.substr(36,3);
    std::string heightStr = buffer_to_string.substr(39,3);

    int playerIDInt = atoi(playerIDStr.c_str());
    int actMapInt = atoi(actMapStr.c_str());
    int sessionInt = atoi(sessionStr.c_str());
    int lvlInt = atoi(lvlStr.c_str());
    int typeInt = atoi(typeIDStr.c_str());
    int idPlayerInt = atoi(idPlayerStr.c_str());
    float xPosFloat = atof(xPosStr.c_str());
    float xPosDecFloat = atof(xPosDecStr.c_str()) * 0.01;
    float yPosFloat = atof(yPosStr.c_str());
    float yPosDecFloat = atof(yPosDecStr.c_str()) * 0.01;
    int widthInt = atoi(widthStr.c_str());
    int heightInt = atoi(heightStr.c_str());


    pDType.playerDataID = playerIDInt;
    pDType.actMap = actMapInt;
    pDType.session = sessionInt;
    pDType.lvl = lvlInt;
    pDType.typeID = typeInt;
    pDType.idPlayer = idPlayerInt;
    pDType.x_pos = xPosFloat+xPosDecFloat;
    pDType.y_pos = yPosFloat+yPosDecFloat;
    pDType.width = widthInt;
    pDType.heigth = heightInt;

    return pDType;
}



//UNMARSHALL TRAMA PRINCIPAL
void EventMsg::unmarshallMsg(const char *buffer){

    std::string buffer_to_string(buffer);
    std::string typeTramaStr = buffer_to_string.substr(0,2);     //(pos 0+2)  //--> tipo trama
    std::string tramaSendStr = buffer_to_string.substr(2,11);    //(pos 2+11)  //--> trama enviada
    std::string tramaGetStr = buffer_to_string.substr(13,11);    //(pos 13+11) //--> trama recibida
    std::string moreStr = buffer_to_string.substr(24,1);         //(pos 24+1) //--> mas tramas?
    std::string numTrazasStr = buffer_to_string.substr(25,2);    //(pos 25+2) //--> num tramas
    std::string CRC16Str = buffer_to_string.substr(27,6);        //(poa 27+6) //--> CRC16

    //cabecera 33

    int typeTramaInt = atoi(typeTramaStr.c_str());
    int tramaSendInt = atoi(tramaSendStr.c_str());
    int tramaGetInt = atoi(tramaGetStr.c_str());
    int moreInt = atoi(moreStr.c_str());
    int numTrazasInt = atoi(numTrazasStr.c_str());
    uint16_t CRC16_aux = (uint16_t)atoi(CRC16Str.c_str());

    setTypeMsg(typeTramaInt);
    setTramaSend(tramaSendInt);
    setTramaGet(tramaGetInt);
    setMore(moreInt);
    setNumTrazas(numTrazasInt);
    setCRC16(CRC16_aux);

    //CONFIRMATION CONNECTION = TRAMA_GET_CONECTION (CLIENT)
    //CONFIRMATION COMMAND = TRAMA_RES_COMMAND (CLIENT)
    //CONFIRMATION LOGOUT = TRAMA_RES_LOGOUT (CLIENT)
    //CONFIRMATION ORDER FROM SERVER = TRAMA_CONFIRMORDER_FROM_SERVER (CLIENT)

    if ((typeTramaInt == TRAMA_GET_CONECTION) ||
        (typeTramaInt == TRAMA_RES_COMMAND) ||
        (typeMsg == TRAMA_CONFIRMORDER_FROM_SERVER) ||
        (typeTramaInt == TRAMA_GET_LOGOUT) ||
        (typeTramaInt == TRAMA_NACK_SESSION)){

        setAnswerType(processSubMsgAType(buffer_to_string.substr(33,95).c_str()));

    //INGAME COMMAND (SERVER)
    }else if (typeMsg == TRAMA_COMMAND){
        std::string subbuffer = buffer_to_string.substr(33,95);
        std::string typeSubTramaStr = subbuffer.substr(0,3);
        int typeSubTramaInt = atoi(typeSubTramaStr.c_str());

        if (typeSubTramaInt == TYPE_COMMAND_MOVEMENT){
            setMovementType(processSubMsgMMovement(subbuffer.c_str()));
        }else if (typeSubTramaInt == TYPE_COMMAND_SHOOT){
            setShotType(processSubMsgSShot(subbuffer.c_str()));
        }else if (typeSubTramaInt == TYPE_COMMAND_CHGWPN){
            setChangeWeaponType(processSubMsgCWeapon(subbuffer.c_str()));
        }else if (typeSubTramaInt == TYPE_COMMAND_EXIT){
            setExitType(processSubMsgEType(subbuffer.c_str()));
        }

    //ORDER TO SERVER (SERVER)
    }else if (typeMsg == TRAMA_SND_ORDER_TO_SERVER){

        std::string subbuffer = buffer_to_string.substr(33,95);
        std::string typeSubTramaStr = subbuffer.substr(6,3);
        int typeSubTramaInt = atoi(typeSubTramaStr.c_str());

        //MSG FROM SERVER
        if (typeSubTramaInt == TYPE_MSG_FROM_SERVER){
            setMsgType(processSubMsgMType(subbuffer.c_str()));
        }else{
            setOrderType(processSubMsgOType(subbuffer.c_str()));
        }

    }
    //REMOTE DATA FROM SERVER (CLIENT)
    else if (typeMsg == TRAMA_GET_DATASERVER){
        std::string subbuffer = buffer_to_string.substr(33,95);
        std::string typeSubTramaStr = subbuffer.substr(0,3);
        int typeSubTramaInt = atoi(typeSubTramaStr.c_str());

        //ACTORS
        if (typeSubTramaInt == TYPE_ACTIVE_ELEMENT){
            setRemotePlayerType(processSubMsgrRType(subbuffer.c_str()));
        }
        //MSG FROM SERVER
        else if (typeSubTramaInt == TYPE_MSG_FROM_SERVER){
            setMsgType(processSubMsgMType(subbuffer.c_str()));
        }
    }

    //REMOTE
    else if (typeMsg == TRAMA_SND_ORDER_TO_SERVER){
        std::string subbuffer = buffer_to_string.substr(33,95);
        std::string typeSubTramaStr = subbuffer.substr(0,3);
        int typeSubTramaInt = atoi(typeSubTramaStr.c_str());

        //MSG FROM SERVER
        if (typeSubTramaInt == TYPE_MSG_FROM_SERVER){
            setMsgType(processSubMsgMType(subbuffer.c_str()));
        }

    }

    //REMOTE LIST OF ACTIVE CLIENT (CLIENT)
    else if (typeMsg == TRAMA_GETDATAFROMORDER_FROM_SERVER){

        std::string subbuffer = buffer_to_string.substr(33,95);
        std::string typeSubTramaStr = subbuffer.substr(0,3);
        int typeSubTramaInt = atoi(typeSubTramaStr.c_str());

        if (typeSubTramaInt = TYPE_ORDER_GETLISTACTIVEPLAYER){
            setListOtherPlayerType(processSubMsglOPT(subbuffer.c_str()));
        }
    }

    //REMOTE LIST OF AVAILABLE SESSIONS (CLIENT)
    else if (typeMsg == TRAMA_GET_SESSION_LIST){
        std::string subbuffer = buffer_to_string.substr(33,95);
        std::string typeSubTramaStr = subbuffer.substr(0,3);
        int typeSubTramaInt = atoi(typeSubTramaStr.c_str());
        setListSessionAvaliableType(processSubMsglSAType(subbuffer.c_str()));
    }

    //GET ID PLAYER FOR SESSION X MAP Y (CLIENT/SERVER)
    else if ((typeMsg == TRAMA_ACK_SESSION) || (typeMsg == TRAMA_SYNACK_SESSION) || (typeMsg == TRAMA_QRY_DATASERVER)){
        std::string subbuffer = buffer_to_string.substr(33,95);
        setPlayerDataType(processSubMsgPDType(subbuffer.c_str()));
    }
}


//subtramas de 103
std::string EventMsg::serializeMsg(){
    char subBuffer[BUFFER_SUBTRAMA_INFO];

    for(int i=0; i<BUFFER_SUBTRAMA_INFO; i++){subBuffer[i]='\0';}

    //QUERY SYNACK CONECTION = TRAMA_SYNACK_CONECTION (SERVER) --> el servidor esta preparado para recibir señales.
    //QUERY CONECTION = TRAMA_QRY_CONECTION (CLIENT)
    //QUERY SESSION LIST = TRAMA_QRY_SESSION_LIST (CLIENT)
    //QUERY DATA FROM SERVER = TRAMA_QRY_DATASERVER (CLIENT)
    //QUERY LOGOUT = TRAMA_QRY_LOGOUT (CLIENT)
    if ((typeMsg == TRAMA_QRY_CONECTION) || (typeMsg == TRAMA_QRY_SESSION_LIST) || (typeMsg == TRAMA_QRY_LOGOUT) || (typeMsg == TRAMA_SYNACK_CONECTION)){


    //CONFIRMATION CONNECTION = TRAMA_GET_CONECTION (SERVER)
    //CONFIRMATION COMMAND = TRAMA_RES_COMMAND (SERVER)
    //CONFIRMATION LOGOUT = TRAMA_RES_LOGOUT (SERVER)
    //CONFIRMATION ORDER FROM SERVER = TRAMA_CONFIRMORDER_FROM_SERVER (SERVER)
    //DENY ACCESS TO PLAYER TO SESSION = TRAMA_NACK_SESSION (SERVER)
    }else if ((typeMsg == TRAMA_GET_CONECTION) ||
              (typeMsg == TRAMA_RES_COMMAND) ||
              (typeMsg == TRAMA_CONFIRMORDER_FROM_SERVER) ||
              (typeMsg == TRAMA_GET_LOGOUT) ||
              (typeMsg == TRAMA_NACK_SESSION)){
        sprintf(subBuffer,"%011d%02d%03d%01d",aType.trama,aType.type_trama,aType.command,aType.result);

    //INGAME COMMAND (CLIENT)
    }else if (typeMsg ==TRAMA_COMMAND){
        if (mMovement.idPlayer != 0){ //local player do a movement.
            sprintf(subBuffer,"%03d%03d%03d%05d%d%06d%02d%06d%02d%03d%03d",
                   mMovement.movementID,
                   mMovement.actMap,
                   mMovement.session,
                   mMovement.idPlayer,
                   mMovement.lvl,
                   (int)mMovement.x,
                   UtilsProtocol::fractional_part_as_int(mMovement.x,2),
                   (int)mMovement.y,
                   UtilsProtocol::fractional_part_as_int(mMovement.y,2),
                   mMovement.width,
                   mMovement.height);


        }else if (sShot.idPlayer != 0){ //local player do a shot
           sprintf(subBuffer,"%03d%03d%03d%05d%03d",sShot.shotID,sShot.actMap,sShot.session,sShot.idPlayer,sShot.ammo);
        }else if (cWeapon.idPlayer != 0){ //local player change a weapon
           sprintf(subBuffer,"%03d%03d%03d%05d%03d%03d",cWeapon.changeWeaponID,cWeapon.actMap,cWeapon.session,cWeapon.idPlayer,cWeapon.oldWeaponId,cWeapon.newWeaponId);
        }
        //local player use a item
        //local player active a switch
        //local player get exit
        else if (eType.idPlayer != 0){
            sprintf(subBuffer,"%03d%05d%03d%03d%01d%06d%02%06d%02d%03d",
                    eType.exitID,
                    eType.idPlayer,
                    eType.actMap,
                    eType.session,
                    eType.level,
                    (int)eType.x,
                    UtilsProtocol::fractional_part_as_int(eType.x,2),
                    (int)eType.y,
                    UtilsProtocol::fractional_part_as_int(eType.y,2),
                    eType.reason);
        }
    //orders from client to server (CLIENT)
    }else if (typeMsg == TRAMA_SND_ORDER_TO_SERVER){
        //envia un mensaje al servidor o a otro cliente
        if (mType.msgTypeID != 0){
            sprintf(subBuffer,"%03d%03d%03d%05d%05d%s",
                    mType.actMap,
                    mType.session,
                    mType.msgTypeID,
                    mType.originMsg,
                    mType.endMsg,
                    mType.msg);

        }else{
            sprintf(subBuffer,"%03d%03d%03d%03d%05%03d%01d%06d%02d%06d%02d%03d%03d",
                    oType.orderID,
                    oType.orderType,
                    oType.actMap,
                    oType.session,
                    oType.value,
                    oType.entityID,
                    oType.level,
                    (int)oType.pos_x,
                    UtilsProtocol::fractional_part_as_int(oType.pos_x,2),
                    (int)oType.pos_y,
                    UtilsProtocol::fractional_part_as_int(oType.pos_y,2),
                    oType.width,
                    oType.height);
        }

    //send data from server to client (SERVER)
    }else if (typeMsg == TRAMA_GET_DATASERVER){

        //REMOTE ACTOR (PRIMERA VERSION, TODOS LOS ELEMENTOS ACTIVOS SON ACTORES)
        if (rPType.typeTramaID!=0){ //Longitud 87
            sprintf(subBuffer,"%03d%03d%03d%03d%03d%05d%05d%01d%06d%02d%06d%02d%03d%03d%01d%03d%03d%02d%01d%03d%01d%03d%01d%03d%01d%03d%01d%02d%01d%02d%01d%02d%01d%02d%05d%01d%02d%01d",
                 rPType.typeTramaID,
                 rPType.typeID,
                 rPType.entityID,
                 rPType.actMap,
                 rPType.session,
                 rPType.idPlayer,
                 rPType.idParPlayer,
                 rPType.lvl,
                 (int)rPType.x_pos,
                 UtilsProtocol::fractional_part_as_int(rPType.x_pos,2),
                 (int)rPType.y_pos,
                 UtilsProtocol::fractional_part_as_int(rPType.y_pos,2),
                 rPType.width,
                 rPType.height,
                 rPType.life,
                 rPType.live,
                 rPType.shd,
                 rPType.act_wpn,
                 rPType.wpn_1,
                 rPType.ammo_wpn_1,
                 rPType.wpn_2,
                 rPType.ammo_wpn_2,
                 rPType.wpn_3,
                 rPType.ammo_wpn_3,
                 rPType.wpn_4,
                 rPType.ammo_wpn_4,
                 rPType.item_1,
                 rPType.item_1_val,
                 rPType.item_2,
                 rPType.item_2_val,
                 rPType.item_3,
                 rPType.item_3_val,
                 rPType.item_4,
                 rPType.item_4_val,
                 rPType.score,
                 rPType.die,
                 rPType.animIndex,
                 rPType.enabled
                 );

        //SEND MESSAGE FROM SERVER
        }else if (mType.msgTypeID!=0){
            sprintf(subBuffer,"%03d%03d%03d%05d%05d%s",
                    mType.actMap,
                    mType.session,
                    mType.msgTypeID,
                    mType.originMsg,
                    mType.endMsg,
                    mType.msg);

        }

    //LISTA DE USUARIOS ACTIVOS EN LA SESION (SERVER)
    }else if (typeMsg == TRAMA_GETDATAFROMORDER_FROM_SERVER){
        if (lOPType.listOtherPlayerID!=0){
            sprintf(subBuffer,"%03d%05d%05d%05d%05d%05d%05d%05d%05d",
                    lOPType.listOtherPlayerID,
                    lOPType.playerID_1,
                    lOPType.scoreID_1,
                    lOPType.playerID_2,
                    lOPType.scoreID_2,
                    lOPType.playerID_3,
                    lOPType.scoreID_3,
                    lOPType.playerID_4,
                    lOPType.scoreID_4);

        }

    //LISTA DE MAPAS-SESIONES_ACTIVAS_JUGADORESxSESSION (SERVER)
    }else if (typeMsg == TRAMA_GET_SESSION_LIST){
        sprintf(subBuffer,"%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d",
                lSAType.listSessionsID,
                lSAType.map_1_id,
                lSAType.session_1_1,
                lSAType.num_player_max_1_1,
                lSAType.num_player_ava_1_1,
                lSAType.session_1_2,
                lSAType.num_player_max_1_2,
                lSAType.num_player_ava_1_2,
                lSAType.map_2_id,
                lSAType.session_2_1,
                lSAType.num_player_max_2_1,
                lSAType.num_player_ava_2_1,
                lSAType.session_2_2,
                lSAType.num_player_max_2_2,
                lSAType.num_player_ava_2_2);

    //ENVIO ID JUGADOR PARA SESION X DEL MAPA Y (SERVER)
    }else if ((typeMsg == TRAMA_ACK_SESSION) || (typeMsg == TRAMA_SYNACK_SESSION) || (typeMsg == TRAMA_QRY_DATASERVER) ){
        sprintf(subBuffer,"%03d%03d%03d%03d%05d%03d%06d%02d%06d%02d%03d%03d",
                pDType.playerDataID,
                pDType.actMap,
                pDType.session,
                pDType.typeID,
                pDType.idPlayer,
                pDType.lvl,
                (int)pDType.x_pos,
                UtilsProtocol::fractional_part_as_int(pDType.x_pos,2),
                (int)pDType.y_pos,
                UtilsProtocol::fractional_part_as_int(pDType.y_pos,2),
                pDType.width,
                pDType.heigth
                );
    }


    std::string data_to_string(subBuffer);
    return data_to_string;
}




