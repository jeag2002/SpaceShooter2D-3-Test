#ifndef STATEDESTINYRES_H_INCLUDED
#define STATEDESTINYRES_H_INCLUDED

/*

TABLE RES_STATEDESTINYDEF
ID              INT             //index del state
TYPE_ACTION     INT             //0->Forward;(se ha pasado de nivel) 1->Finish;(ha acabado el nivel) 2->Stop;(se ha pausado el nivel) 3->Error; (error) 4->Minimapa;
ID_NEXT_ACTION  INT             //index del state siguiente
ID_ACTION_PAR   INT             //index del state padre

*/

class StateDestinyRes{

public:

  StateDestinyRes(){
    this->id_action = -1; //
    this->id_parent = -1;
    this->id_forward = -1;
    this->type = -1;
  };



  ~StateDestinyRes(){
    this->id_action = -1; //
    this->id_parent = -1;
    this->id_forward = -1;
    this->type = -1;
  };

  uint8_t getIdAction(){return this->id_action;}
  void setIdAction(uint32_t _id_action){this->id_action = _id_action;}

  uint32_t getIdParent(){return this->id_parent;}
  void setIdParent(uint32_t _id_parent){this->id_parent = _id_parent;}

  uint32_t getIdForward(){return this->id_forward;}
  void setIdForward(uint32_t _id_forward){this->id_forward = _id_forward;}

  uint32_t getType(){return this->type;}
  void setType(uint32_t _id_type){this->type = type;}

private:

uint8_t id_action; //
uint32_t id_parent;
uint32_t id_forward;
uint8_t type;

};

#endif // STATEDESTINYRES_H_INCLUDED
