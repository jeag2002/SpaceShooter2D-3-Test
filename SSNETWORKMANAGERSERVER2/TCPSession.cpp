#include "TCPSession.h"

void TCPSession::Run(){

    bool DONE = false;
    bool sessionFull = false;
    pthread_t iThread = pthread_self();

    while (!DONE){
          if (!cQ->isEmpty()){
              TCPsocket *client = cQ->front();
              int i = 0;
              for(i=0; i<MAX_CLIENT_SESSION; i++){
                if (freeSocket[i]==true){
                    freeSocket[i] = false;
                    clientSocket[i] = *client;
                    cQ->pop();
                    break;
                }
              }

              if (i > MAX_CLIENT_SESSION){
                 logger->debug("[TCPSession::Run] FULL STACK CLIENT SOCKETS FOR SESSION [%08x]",iThread);
              }else{
                 logger->debug("[TCPSession::Run] CLIENT SOCKET ACCEPTED FOR SESSION [%08x]",iThread);
              }
           }

           for (int j=0; j<MAX_CLIENT_SESSION; j++){
                if (clientSocket[j]!=NULL){
                    EventMsg *inputMsg = nClient->getMsgFromClient(clientSocket[j]);
                    processInputMsgFromClient(clientSocket[j], j ,inputMsg);
                }
           }

    }


}


void TCPSession::processInputMsgFromClient(TCPsocket client, int index, EventMsg *inputMsg){

    EventMsg *msgOutput = new EventMsg();

    if (inputMsg->getTypeMsg() == TRAMA_QRY_SESSION_LIST){

        logger->debug("[SSNETWORKMANAGERSERVER::processInputMsgFromClient] return Available sessions for client");

        msgOutput->setTypeMsg(TRAMA_GET_SESSION_LIST);
        msgOutput->setTramaGet(inputMsg->getTramaSend());
        msgOutput->setTramaSend(inputMsg->getTramaGet());
        msgOutput->setMore(NOK);

        listSessionAvailableType lSAT;

        lSAT.listSessionsID = TYPE_LIST_SESSION_ID;
        lSAT.map_1_id = 1;
        lSAT.session_1_1 = 1;
        lSAT.num_player_ava_1_1 = numPlayers;
        lSAT.num_player_max_1_1 = maxPlayers;
        lSAT.session_1_2 = 2;
        lSAT.num_player_ava_1_2 = 0;
        lSAT.num_player_max_1_2 = 0;

        lSAT.map_2_id = 2;
        lSAT.session_2_1 = 3;
        lSAT.num_player_ava_2_1 = 0;
        lSAT.num_player_max_2_1 = 0;
        lSAT.session_2_2 = 4;
        lSAT.num_player_ava_2_2 = 0;
        lSAT.num_player_max_2_2 = 0;

        msgOutput->setListSessionAvaliableType(lSAT);
        nClient->sendMsgToClient(client,msgOutput);

    }else if (inputMsg->getTypeMsg() == TRAMA_SYNACK_SESSION){

        playerDataType pDT = inputMsg->getPlayerDataType();

        if (numPlayers < maxPlayers){

            logger->debug("[SSNETWORKMANAGERSERVER::processInputMsgFromClient] looking for client free player space in map [%d] session [%d] (numPlayersActives %d)", pDT.actMap,pDT.session,numPlayers);
            bool findNotUserPlayer = false;

            DynamicEntity *dEntity;
            int index = 0;
            std::map<int, DynamicEntity *> eLvl = mem->getRemPlayerMap();

            for(auto iterator = eLvl.begin(); (iterator != eLvl.end() && !findNotUserPlayer); iterator++){
                 index = iterator->first;
                 dEntity = iterator->second;                 if (!dEntity->isEnabled()){findNotUserPlayer = true;}
            }

            mem->getRemPlayerMapElem(index)->setEnabled(true);

            pDT.idPlayer =  mem->getRemPlayerMapElem(index)->getIDDE();
            pDT.lvl = mem->getRemPlayerMapElem(index)->getActLevel();
            pDT.typeID = mem->getRemPlayerMapElem(index)->getTypeId();
            pDT.x_pos = mem->getRemPlayerMapElem(index)->getX();
            pDT.y_pos = mem->getRemPlayerMapElem(index)->getY();
            pDT.width = mem->getRemPlayerMapElem(index)->getWidth();
            pDT.heigth = mem->getRemPlayerMapElem(index)->getHeight();

            logger->debug("[SSNETWORKMANAGERSERVER::processInputMsgFromClient] assigned to new client IDPlayer Type:[%d] ID:[%d] X_POS:[%f] Y_POS:[%f] WIDTH:[%d] HEIGHT:[%d]",
                          pDT.typeID,
                          pDT.idPlayer,
                          pDT.x_pos,
                          pDT.y_pos,
                          pDT.width,
                          pDT.heigth);

            msgOutput->setTypeMsg(TRAMA_ACK_SESSION);
            msgOutput->setTramaGet(inputMsg->getTramaSend());
            msgOutput->setTramaSend(inputMsg->getTramaGet());
            msgOutput->setMore(NOK);
            msgOutput->setPlayerDataType(pDT);

            nClient->sendMsgToClient(client, msgOutput);

           numPlayers++;
        }else{

            logger->debug("[SSNETWORKMANAGERSERVER::processInputMsgFromClient] no free player space in map [%d] session [%d] for client",pDT.actMap,pDT.session);

            msgOutput->setTypeMsg(TRAMA_NACK_SESSION);
            msgOutput->setTramaGet(inputMsg->getTramaSend());
            msgOutput->setTramaSend(inputMsg->getTramaGet());
            msgOutput->setMore(NOK);

            answerType aType;
            aType.type_trama = TYPE_MSG_ANSWER_CONNECTION;
            aType.trama =   inputMsg->getTramaGet();
            aType.command = TYPE_MSG_ANSWER_SESSION;
            aType.result = NOK;

            msgOutput->setAnswerType(aType);
            nClient->sendMsgToClient(client, msgOutput);
            nClient->closeClient(client);

            clientSocket[index] = NULL;
            freeSocket[index] = true;


        }
    }else if (inputMsg->getTypeMsg() == TRAMA_QRY_DATASERVER){
        logger->debug("[SSNETWORKMANAGERSERVER::processInputMsgFromClient] send all the data to the client");
        sendServerDataToClient(client, inputMsg);

    }else if ((inputMsg->getTypeMsg() == TRAMA_COMMAND) || (inputMsg->getTypeMsg() == TRAMA_SND_ORDER_TO_SERVER)){
        logger->debug("[SSNETWORKMANAGERSERVER::processInputMsgFromClient] process input command from the client");
        processCommandsFromClient(client, inputMsg);
    }
}


void TCPSession::sendServerDataToClient(TCPsocket client, EventMsg *inputMsg){

    DynamicEntity *dEntity;

    //ENEMIES-LVL1
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::map<int, DynamicEntity *> eLvl = mem->getEnemy_Lvl_1_Map();
    for(auto iterator = eLvl.begin(); iterator != eLvl.end(); iterator++){
        int i = iterator->first;
        dEntity = iterator->second;

        EventMsg *outputMsg = new EventMsg(TRAMA_GET_DATASERVER,inputMsg->getTramaSend(),inputMsg->getTramaGet(),OK,OK,(uint16_t)0);
        outputMsg->setRemotePlayerType(dEntity->getDynamicEntityRPT());
        nClient->sendMsgToClient(client, outputMsg);
    }

    //ENEMIES-LVL2
    eLvl = mem->getEnemy_Lvl_2_Map();
    for(auto iterator = eLvl.begin(); iterator != eLvl.end(); iterator++){
        int i = iterator->first;
        dEntity = iterator->second;

        EventMsg *outputMsg = new EventMsg(TRAMA_GET_DATASERVER,inputMsg->getTramaSend(),inputMsg->getTramaGet(),OK,OK,(uint16_t)0);
        outputMsg->setRemotePlayerType(dEntity->getDynamicEntityRPT());
        nClient->sendMsgToClient(client, outputMsg);
    }

    //ENEMIES-LVL2
    eLvl = mem->getEnemy_Lvl_3_Map();
    for(auto iterator = eLvl.begin(); iterator != eLvl.end(); iterator++){
        int i = iterator->first;
        dEntity = iterator->second;

        EventMsg *outputMsg = new EventMsg(TRAMA_GET_DATASERVER,inputMsg->getTramaSend(),inputMsg->getTramaGet(),OK,OK,(uint16_t)0);
        outputMsg->setRemotePlayerType(dEntity->getDynamicEntityRPT());
        nClient->sendMsgToClient(client, outputMsg);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //DYNELEM-LVL1
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    eLvl = mem->getDynElem_Lvl_1_Map();
    for(auto iterator = eLvl.begin(); iterator != eLvl.end(); iterator++){
        int i = iterator->first;
        dEntity = iterator->second;

        EventMsg *outputMsg = new EventMsg(TRAMA_GET_DATASERVER,inputMsg->getTramaSend(),inputMsg->getTramaGet(),OK,OK,(uint16_t)0);
        outputMsg->setRemotePlayerType(dEntity->getDynamicEntityRPT());
        nClient->sendMsgToClient(client, outputMsg);
    }

    //DYNELEM-LVL2
    eLvl = mem->getDynElem_Lvl_2_Map();
    for(auto iterator = eLvl.begin(); iterator != eLvl.end(); iterator++){
        int i = iterator->first;
        dEntity = iterator->second;

        EventMsg *outputMsg = new EventMsg(TRAMA_GET_DATASERVER,inputMsg->getTramaSend(),inputMsg->getTramaGet(),OK,OK,(uint16_t)0);
        outputMsg->setRemotePlayerType(dEntity->getDynamicEntityRPT());
        nClient->sendMsgToClient(client, outputMsg);
    }

    //DYNELEM-LVL3
    eLvl = mem->getDynElem_Lvl_3_Map();
    for(auto iterator = eLvl.begin(); iterator != eLvl.end(); iterator++){
        int i = iterator->first;
        dEntity = iterator->second;

        EventMsg *outputMsg = new EventMsg(TRAMA_GET_DATASERVER,inputMsg->getTramaSend(),inputMsg->getTramaGet(),OK,OK,(uint16_t)0);
        outputMsg->setRemotePlayerType(dEntity->getDynamicEntityRPT());
        nClient->sendMsgToClient(client, outputMsg);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //REMOTEPLAYERS
    eLvl = mem->getRemPlayerMap();
    for(auto iterator = eLvl.begin(); iterator != eLvl.end(); iterator++){
        int i = iterator->first;
        dEntity = iterator->second;

        if (dEntity->isEnabled()){
            EventMsg *outputMsg = new EventMsg(TRAMA_GET_DATASERVER,inputMsg->getTramaSend(),inputMsg->getTramaGet(),OK,OK,(uint16_t)0);
            outputMsg->setRemotePlayerType(dEntity->getDynamicEntityRPT());
            nClient->sendMsgToClient(client, outputMsg);
        }
    }

    //SEND MSG SERVER TO CLIENT.

    //SEND END MSG SERVER TO CLIENT.
    EventMsg *finalMsg = new EventMsg(TRAMA_GET_DATASERVER,inputMsg->getTramaSend(),inputMsg->getTramaGet(),NOK,OK,(uint16_t)0);
    nClient->sendMsgToClient(client,finalMsg);
}


void TCPSession::processCommandsFromClient(TCPsocket client, EventMsg *inputMsg){

    if (inputMsg->getTypeMsg() == TRAMA_COMMAND){
        if (inputMsg->getMovementType().movementID == TYPE_COMMAND_MOVEMENT){
            logger->debug("[SSNETWORKMANAGERSERVER::processCommandsFromClient] PROCESS REMOTE INPUT COMMAND MOVEMENT set IDCLIENT [%d] (lvl:%d,x:%f,y:%f)",
                          inputMsg->getMovementType().idPlayer,
                          inputMsg->getMovementType().lvl,
                          inputMsg->getMovementType().x,
                          inputMsg->getMovementType().y
                          );
            mem->getRemPlayerMapElem(inputMsg->getMovementType().idPlayer)->setRemoteMovement(inputMsg->getMovementType());

        }else if (inputMsg->getShotType().shotID == TYPE_COMMAND_SHOOT){

        }else if (inputMsg->getChangeWeaponType().changeWeaponID == TYPE_COMMAND_CHGWPN){

        }else if (inputMsg->getExitType().exitID == TYPE_COMMAND_EXIT){

        }
    }else if (inputMsg->getTypeMsg() == TRAMA_SND_ORDER_TO_SERVER){


    }
}
