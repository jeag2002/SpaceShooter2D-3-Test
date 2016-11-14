#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

class Resource{

public:

Resource(){
    obsolete = false;
    timestamp = 0;
    type = -1;
};

Resource(bool _isObsolete, uint32_t _timestamp, uint8_t _type){
    obsolete = _isObsolete;
    timestamp = _timestamp;
    type = _type;
};


~Resource(){
    obsolete = false;
    timestamp = 0;
    type = -1;
};

void setObsolete(bool _isObsolete){this->obsolete = _isObsolete;}
bool isObsolete(){return obsolete;}

void setTimeStamp(uint32_t _timestamp){this->timestamp = _timestamp;}
uint32_t getTimeStamp(){return this->timestamp;}

void setType(uint8_t _type){this->type = _type;}
uint8_t getType(){return this->type;}

//virtual void copyTo()=0;
virtual void copyTo(Resource *res)=0;
virtual void clear()=0;

protected:

bool obsolete;
uint32_t timestamp;
uint8_t type;

};

#endif // RESOURCE_H_INCLUDED
