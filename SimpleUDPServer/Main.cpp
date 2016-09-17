#include "SDL_net.h"
#include "SDL.h"
#undef main
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_TRAMA 128
#define MAX_DELAY 500

#define REMOTE_PORT 20001
#define LOCAL_PORT 20001

#define LOCALHOST "localhost"

#define MAX_SOCKETS 9
#define MAX_CLIENT 8

#define MAX_DELAY 500
#define ERROR (0xff)

#define BUFFER_SIZE 128

IPaddress serverIP;
UDPsocket serverSocket;
SDLNet_SocketSet socketSet;
UDPpacket *packet;

UDPpacket *in;
UDPpacket *out;
UDPpacket **packets;
UDPpacket *outs[32];

int len=1400;

const char *host;
IPaddress clientIP;

FILE * pFile;


void initCommunicationUDPServer(){

	if(SDL_Init(0)==-1)
	{
		fprintf(pFile,"SDL_Init: %s\n",SDL_GetError());
		printf("SDL_Init: %s\n",SDL_GetError());
		exit(-1);
	}

	if(SDLNet_Init()==-1)
	{
		fprintf(pFile,"Failed SDLNet_Int [%s]\n",SDLNet_GetError());
        printf("Failed SDLNet_Int [%s]\n",SDLNet_GetError());
        exit(-1);
	}

	if(!(serverSocket=SDLNet_UDP_Open(LOCAL_PORT)))
	{
	    fprintf(pFile,"SDLNet_UDP_Open: %s\n",SDLNet_GetError());
		printf("SDLNet_UDP_Open: %s\n",SDLNet_GetError());
		exit(-1);
	}

	fprintf(pFile," listen from 0.0.0.0/[%d]\n",LOCAL_PORT);
	printf(" listen from 0.0.0.0/[%d]\n",LOCAL_PORT);

	if(!(out=SDLNet_AllocPacket(BUFFER_SIZE)))
	{
		fprintf(pFile,"SDLNet_AllocPacket OUT: %s\n",SDLNet_GetError());
		printf("SDLNet_AllocPacket OUT: %s\n",SDLNet_GetError());
		exit(-1);
	}
	if(!(in=SDLNet_AllocPacket(BUFFER_SIZE)))
	{
		fprintf(pFile,"SDLNet_AllocPacket OUT: %s\n",SDLNet_GetError());
		printf("SDLNet_AllocPacket IN: %s\n",SDLNet_GetError());
		exit(-1);
	}


    fprintf(pFile," UDP SERVER CONFIGURATION DONE!\n");
    printf(" UDP SERVER CONFIGURATION DONE!\n");

};


void sendMsgToClient(int value){

    char msg[100];
    for(int i=0;i<100;i++){msg[i]='\0';}

    sprintf(msg,"(#)ENVIO MSG - %d SERVIDOR AL CLIENTE ",value);

    for(int i=0;i<out->len;i++){out->data[i]='\0';}
    for(int i=0;i<strlen(msg);i++){out->data[i]=msg[i];}

    int err = SDLNet_UDP_Send(serverSocket,-1,out);

    if (!err){
        fprintf(pFile,"[SEND SERVER MSG TO CLIENT] UDP DATA NOT SEND! [%s]\n", SDLNet_GetError());
        printf("[SEND SERVER MSG TO CLIENT] UDP DATA NOT SEND! [%s]\n", SDLNet_GetError());
    }else{
        fprintf(pFile,"[SEND SERVER MSG TO CLIENT] BUFFER SEND [%s] size [%d]\n",out->data, out->len);
        printf("[SEND SERVER MSG TO CLIENT] BUFFER SEND [%s] size [%d]\n",out->data, out->len);
    }
}

void getMsgFromClient(int value){

    bool DONE = false;
    long initialMark = SDL_GetTicks();

    while(!DONE){
          int err = SDLNet_UDP_Recv(serverSocket, out);
          if (err){

                int channel = SDLNet_UDP_Bind(serverSocket, 0, &serverIP);
                if(channel==-1){
                    fprintf(pFile,"[GET CLIENT MSG FROM CLIENT] SDLNet_UDP_Bind: [%s]\n",SDLNet_GetError());
                    printf("[GET CLIENT MSG FROM CLIENT] SDLNet_UDP_Bind: [%s]\n",SDLNet_GetError());
                    exit(-1);
                }

                char *remMSG = (char *)in->data;
                fprintf(pFile,"[GET CLIENT MSG FROM CLIENT] [%s]\n",remMSG);
                printf("[GET CLIENT MSG FROM CLIENT] [%s]\n",remMSG);
                DONE = true;
                sendMsgToClient(value);
                DONE = true;
          }


          if (!DONE){
            long DIFF = SDL_GetTicks()-initialMark;
            fprintf(pFile,"[GET CLIENT MSG FROM CLIENT] --> SOCKET INACTIVE DURING [%d] MS\n", DIFF);
            printf("[GET CLIENT MSG FROM CLIENT] --> SOCKET INACTIVE DURING [%d] MS\n", DIFF);
            if (DIFF >= MAX_DELAY){
                DONE = true;
            }
          }
    }
}


int main(int argc, char **argv)
{

  pFile = fopen ("UDPSERVER.log","w");
  initCommunicationUDPServer();

  int value = 100000;

  while(value >= 0){
    SDLNet_UDP_Unbind(serverSocket, 0);
    getMsgFromClient(value);
    value--;
  }

  SDLNet_UDP_Close(serverSocket);
  SDLNet_FreePacket(out);
  SDLNet_FreePacket(in);
  SDLNet_FreePacketV(packets);
  SDLNet_Quit();
  SDL_Quit();



  fclose (pFile);
  return 0;
}
