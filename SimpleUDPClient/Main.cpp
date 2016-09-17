#include "SDL_net.h"
#include "SDL.h"
#undef main
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DELAY 500
#define LOCALHOST "localhost"
#define REMOTE_PORT 20001
#define LOCAL_PORT 20001
#define BUFFER 128

IPaddress serverIP;
IPaddress clientIP;

UDPsocket clientSocket;
UDPpacket *packet;

UDPpacket *in;
UDPpacket *out;

FILE * pFile;


void initCommunicationUDPClient(){

	if(SDL_Init(0)==-1)
	{
		fprintf(pFile,"SDL_Init: %s\n",SDL_GetError());
		printf("SDL_Init: %s\n",SDL_GetError());
		exit(-1);
	}

	if(SDLNet_Init()==-1)
	{
		fprintf(pFile,"SDLNet_Init: %s\n",SDLNet_GetError());
		printf("SDLNet_Init: %s\n",SDLNet_GetError());
		exit(-1);
	}

	if(SDLNet_ResolveHost(&serverIP,LOCALHOST,REMOTE_PORT)==-1)
	{
		fprintf(pFile,"SDLNet_ResolveHost: %s\n",SDLNet_GetError());
		printf("SDLNet_ResolveHost: %s\n",SDLNet_GetError());
		exit(-1);
	}

	if(!(clientSocket=SDLNet_UDP_Open(0)))
	{
		fprintf(pFile,"SDLNet_UDP_Open: %s\n",SDLNet_GetError());
		printf("SDLNet_UDP_Open: %s\n",SDLNet_GetError());
		exit(-1);
	}

	if(!(out=SDLNet_AllocPacket(BUFFER)))
	{
		fprintf(pFile,"SDLNet_AllocPacket: %s\n",SDLNet_GetError());
        printf("SDLNet_AllocPacket: %s\n",SDLNet_GetError());
		exit(-1);
	}

	if(!(in=SDLNet_AllocPacket(BUFFER)))
	{
		fprintf(pFile,"SDLNet_AllocPacket: %s\n",SDLNet_GetError());
		printf("SDLNet_AllocPacket: %s\n",SDLNet_GetError());
		exit(-1);
	}


	if(SDLNet_UDP_Bind(clientSocket, 0, &serverIP)==-1)
	{
		fprintf(pFile,"SDLNet_UDP_Bind: %s\n",SDLNet_GetError());
		printf("SDLNet_UDP_Bind: %s\n",SDLNet_GetError());
		exit(-1);
	}


	out->address.host = serverIP.host;
	out->address.port = serverIP.port;

	fprintf(pFile,"SDLNet_UDP_CLIENT CONFIGURATION DONE!\n");
	printf("SDLNet_UDP_CLIENT CONFIGURATION DONE!\n");
}


void sendMsgToServer(int value){

    char msg[100];
    for(int i=0;i<100;i++){msg[i]='\0';}

    sprintf(msg,"(*)ENVIO MSG - %d CLIENTE AL SERVIDOR ",value);

    for(int i=0;i<out->len;i++){out->data[i]='\0';}
    for(int i=0;i<strlen(msg);i++){out->data[i]=msg[i];}

    int err = SDLNet_UDP_Send(clientSocket,-1,out);

     if (!err){
        fprintf(pFile,"[SEND CLIENT MSG TO SERVER] UDP DATA NOT SEND! [%s]\n", SDLNet_GetError());
        printf("[SEND CLIENT MSG TO SERVER] UDP DATA NOT SEND! [%s]\n", SDLNet_GetError());
    }else{
        fprintf(pFile,"[SEND CLIENT MSG TO SERVER] BUFFER SEND [%s] size [%d]\n",out->data, out->len);
        printf("[SEND CLIENT MSG TO SERVER] BUFFER SEND [%s] size [%d]\n",out->data, out->len);
    }
}

void getMsgFromServer(){

    bool DONE = false;
    long initialMark = SDL_GetTicks();

    while(!DONE){

          int err = SDLNet_UDP_Recv(clientSocket, in);
          if (err){
              char *remMSG = (char *)in->data;
              fprintf(pFile,"[GET SERVER MSG FROM SERVER] [%s]\n",remMSG);
              printf("[GET SERVER MSG FROM SERVER] [%s]\n",remMSG);
              DONE = true;
          }

          if (!DONE){
            long DIFF = SDL_GetTicks()-initialMark;
            fprintf(pFile,"[GET SERVER MSG FROM SERVER] --> SOCKET INACTIVE DURING [%d] MS\n", DIFF);
            printf("[GET SERVER MSG FROM SERVER] --> SOCKET INACTIVE DURING [%d] MS\n", DIFF);
            if (DIFF >= MAX_DELAY){
                DONE = true;
            }
          }
    }
}


int main(int argc, char **argv)
{

  pFile = fopen ("UDPCLIENT.log","w");

  initCommunicationUDPClient();
  int value = 100000;

  while(value >= 0){
    sendMsgToServer(value);
    getMsgFromServer();
    value--;
  }

  SDLNet_UDP_Close(clientSocket);
  SDLNet_FreePacket(out);
  SDLNet_FreePacket(in);
  SDLNet_Quit();
  SDL_Quit();

  fclose (pFile);

  return 0;
}
