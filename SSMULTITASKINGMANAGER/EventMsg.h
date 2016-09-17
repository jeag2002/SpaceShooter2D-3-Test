#ifndef EVENTMSG_H_INCLUDED
#define EVENTMSG_H_INCLUDED

class EventMsg{

  public:

      EventMsg(){
        typeMsg = 0;
        value = 0.0f;
        TO = 0;
        index = 0;
      }

      EventMsg(EventMsg *_remoteMsg){
        typeMsg = _remoteMsg->getTypeMsg();
        value = _remoteMsg->getValue();
        TO = _remoteMsg->getTO();
        index = _remoteMsg->getIndex();
      }

      EventMsg(int _typeMsg, float _value, int _TO){
        typeMsg = _typeMsg;
        value = _value;
        TO = _TO;
        index = 0;
      }

      EventMsg(int _typeMsg, float _value, int _TO, int _index){
        typeMsg = _typeMsg;
        value = _value;
        TO = _TO;
        index = _index;
      }

      ~EventMsg(){
        typeMsg = 0;
        value = 0.0f;
        TO = 0;
        index = 0;
      };

      int getTypeMsg(){return typeMsg;}
      float getValue(){return value;}
      int getTO(){return TO;}
      int getIndex(){return index;}

      void setTypeMsg(int _typeMsg){typeMsg = _typeMsg;}
      void setValue(float _value){value = _value;}
      void setTO(int _TO){TO = _TO;}
      void setIndex(int _index){index = _index;}

      void setMsg(EventMsg *_remoteMsg){
        typeMsg = _remoteMsg->getTypeMsg();
        value = _remoteMsg->getValue();
        TO = _remoteMsg->getTO();
        index = _remoteMsg->getIndex();
      }

  private:
    int typeMsg;
    float value;
    int TO;
    int index;
};


#endif // EVENTMSG_H_INCLUDED
