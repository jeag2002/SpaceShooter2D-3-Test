#include "UDPSession.h"

void UDPSession::Run(EventMsg *msg){

    if (msg->getTypeMsg() == TRAMA_COMMAND){
        if (msg->getMovementType().movementID == TYPE_COMMAND_MOVEMENT){
            logger->debug("[UDPSession::Run] PROCESS REMOTE INPUT COMMAND MOVEMENT set IDCLIENT [%d] (lvl:%d,x:%f,y:%f)",
                          msg->getMovementType().idPlayer,
                          msg->getMovementType().lvl,
                          msg->getMovementType().x,
                          msg->getMovementType().y
                          );
            mem->getRemPlayerMapElem(msg->getMovementType().idPlayer)->setRemoteMovement(msg->getMovementType());

        }else if (msg->getShotType().shotID == TYPE_COMMAND_SHOOT){

        }else if (msg->getChangeWeaponType().changeWeaponID == TYPE_COMMAND_CHGWPN){

        }else if (msg->getExitType().exitID == TYPE_COMMAND_EXIT){

        }
    }
};
