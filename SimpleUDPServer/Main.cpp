#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SDL_net.h"
#include "SDL.h"
#undef main

#include <iostream>
#include <sstream>

int main(int argc, char **argv){


    UDPsocket ourSocket;
	IPaddress serverIP;
	UDPpacket *packet;
	bool endTransmision = false;

	Uint16 port = 8888;
	Uint16 remoteport = 12000;
	int packetSize = 30;

	std::string ip = "127.0.0.1";


	std::cout << "Initializing SDL_net...\n";
    if ( SDLNet_Init() == -1 ){
        std::cout << "\tSDLNet_Init failed : " << SDLNet_GetError() << std::endl;
        exit(-1);
    }
    std::cout << "\tSuccess!\n\n";

    std::cout << "Opening port " << port << "...\n";
    ourSocket = SDLNet_UDP_Open( port );

    if ( ourSocket == nullptr ){
        std::cout << "\tSDLNet_UDP_Open failed : " << SDLNet_GetError() << std::endl;
        exit(-1);
    }
    std::cout << "\tSuccess!\n\n";

    std::cout << "Setting IP ( " << ip << " ) " << "and port ( " << remoteport << " )\n";
    if ( SDLNet_ResolveHost( &serverIP, ip.c_str(), remoteport )  == -1 ){
        std::cout << "\tSDLNet_ResolveHost failed : " << SDLNet_GetError() << std::endl;
        exit(-1);
    }
    std::cout << "\tSuccess!\n\n";

    std::cout << "Creating packet with size " << packetSize << "...\n";
    packet = SDLNet_AllocPacket( packetSize );
    if ( packet == nullptr )
    {
        std::cout << "\tSDLNet_AllocPacket failed : " << SDLNet_GetError() << std::endl;
        exit(-1);
    }

    packet->address.host = serverIP.host;
    packet->address.port = serverIP.port;
    std::cout << "\tSuccess!\n\n";

    char buffer[100];
    int num_trama = 1;
    IPaddress ipAdd;

    while(!endTransmision){

        /****/
        SDLNet_UDP_Unbind(ourSocket, 0);
        /****/

        if ( SDLNet_UDP_Recv(ourSocket, packet))
		{
			std::cout << "\tData received from CLIENT: " << packet->data << "\n";

            /***/
			memcpy(&ipAdd,&packet->address,sizeof(IPaddress));
            const char *host=SDLNet_ResolveIP(&ipAdd);
            Uint32 ipnum=SDL_SwapBE32(ipAdd.host);
            Uint16 port=SDL_SwapBE16(ipAdd.port);
            if(host){
               std::cout << "request from host=" << host << "port=" << port << "\n";
            }else{
               std::cout << "request from host="<< (ipnum>>24) << "." << ((ipnum>>16)&0xff) << "." << ((ipnum>>8)&0xff) << "." << (ipnum&0xff) << ":" << port << "\n";
            }
            if(SDLNet_UDP_Bind(ourSocket, 0, &ipAdd)==-1)
            {
                std::cout << "SDLNet_UDP_Bind: " << SDLNet_GetError() << "\n";
                exit(-1);
            }
            /***/


            for(int i=0; i<100; i++){buffer[i]='\0';}
			num_trama++;
			sprintf(buffer,"(#)MSG TO CLIENT %i",num_trama);
			std::string msg(buffer);

			memcpy(packet->data, msg.c_str(), msg.length() );
            packet->len = msg.length();

            if ( SDLNet_UDP_Send(ourSocket, -1, packet) == 0 )
            {
                std::cout << "\tSDLNet_UDP_Send failed : " << SDLNet_GetError() << "\n";
                exit(-1);
            }

            std::cout << "\tData send to CLIENT: " << packet->data << "\n";

		}else{
            SDL_Delay(10);
		}
    }


    SDLNet_UDP_Close(ourSocket);
    SDLNet_FreePacket(packet);
    SDLNet_Quit();
    SDL_Quit();

    return 0;
}


/*
struct UDPConnection
{
	UDPConnection( )
	{
		quit = false;
	}
	~UDPConnection( )
	{
		SDLNet_FreePacket(packet);
		SDLNet_Quit();
	}
	bool Init( const std::string &ip, int32_t remotePort, int32_t localPort )
	{
		std::cout << "Connecting to \n\tIP : " << ip << "\n\tPort : " << remotePort << std::endl;
		std::cout << "Local port : " << localPort << "\n\n";

		// Initialize SDL_net
		if ( !InitSDL_Net() )
			return false;

		if ( !OpenPort( localPort  ) )
			return false;

		if ( !SetIPAndPort( ip, remotePort ) )
			return false;

		if ( !CreatePacket( 512 ) )
			return false;

		return true;
	}
	bool InitSDL_Net()
	{
		std::cout << "Initializing SDL_net...\n";

		if ( SDLNet_Init() == -1 )
		{
			std::cout << "\tSDLNet_Init failed : " << SDLNet_GetError() << std::endl;
			return false;
		}

		std::cout << "\tSuccess!\n\n";
		return true;
	}
	bool CreatePacket( int32_t packetSize )
	{
		std::cout << "Creating packet with size " << packetSize << "...\n";

		// Allocate memory for the packet
		packet = SDLNet_AllocPacket( packetSize );

		if ( packet == nullptr )
		{
			std::cout << "\tSDLNet_AllocPacket failed : " << SDLNet_GetError() << std::endl;
			return false;
		}

		// Set the destination host and port
		// We got these from calling SetIPAndPort()
		packet->address.host = serverIP.host;
		packet->address.port = serverIP.port;

		std::cout << "\tSuccess!\n\n";
		return true;
	}
	bool OpenPort( int32_t port )
	{
		std::cout << "Opening port " << port << "...\n";

		// Sets our sovket with our local port
		ourSocket = SDLNet_UDP_Open( port );

		if ( ourSocket == nullptr )
		{
			std::cout << "\tSDLNet_UDP_Open failed : " << SDLNet_GetError() << std::endl;
			return false;
		}

		std::cout << "\tSuccess!\n\n";
		return true;
	}
	bool SetIPAndPort( const std::string &ip, uint16_t port )
	{
		std::cout << "Setting IP ( " << ip << " ) " << "and port ( " << port << " )\n";

		// Set IP and port number with correct endianess
		if ( SDLNet_ResolveHost( &serverIP, ip.c_str(), port )  == -1 )
		{
			std::cout << "\tSDLNet_ResolveHost failed : " << SDLNet_GetError() << std::endl;
			return false;
		}

		std::cout << "\tSuccess!\n\n";
		return true;
	}
	// Send data.
	bool Send( const std::string &str )
	{
		// Set the data
		// UDPPacket::data is an Uint8, which is similar to char*
		// This means we can't set it directly.
		//
		// std::stringstreams let us add any data to it using << ( like std::cout )
		// We can extract any data from a std::stringstream using >> ( like std::cin )
		//
		//str
		std::cout << "Type a message and hit enter\n";
		std::string msg = "";
		std::cin.ignore();
		std::getline(std::cin, msg );

		memcpy(packet->data, msg.c_str(), msg.length() );
		packet->len = msg.length();

		std::cout
			<< "==========================================================================================================\n"
			<< "Sending : \'" << str << "\', Length : " << packet->len << "\n";

		// Send
		// SDLNet_UDP_Send returns number of packets sent. 0 means error
		if ( SDLNet_UDP_Send(ourSocket, -1, packet) == 0 )
		{
			std::cout << "\tSDLNet_UDP_Send failed : " << SDLNet_GetError() << "\n"
				<< "==========================================================================================================\n";
			return false;
		}

		std::cout << "\tSuccess!\n"
			<< "==========================================================================================================\n";

		if ( str == "quit" )
			quit = true;
		return true;
	}
	void CheckForData()
	{
		std::cout
			<< "==========================================================================================================\n"
			<< "Check for data...\n";

		// Check t see if there is a packet wauting for us...
		if ( SDLNet_UDP_Recv(ourSocket, packet))
		{
			std::cout << "\tData received : " << packet->data << "\n";

			// If the data is "quit"
			if ( strcmp((char *)packet->data, "quit") == 0)
				quit = true;
		}
		else
			std::cout  << "\tNo data received!\n";

		std::cout << "==========================================================================================================\n";
	}
	bool WasQuit()
	{
		return quit;
	}
	private:
	bool quit;
	UDPsocket ourSocket;
	IPaddress serverIP;
	UDPpacket *packet;
};

UDPConnection udpConnection;

int main(int argc, char **argv)
{
	std::string IP;
	int32_t localPort = 0;
	int32_t remotePort = 0;

	std::cout
		<< "\n==========================================================================================================\n"
		<< "UDP connection - A simple test for UDP connections using SDL_Net!"
		<< "\n==========================================================================================================\n"
		<< "You'll be asked to enter the following :"
		<< "\n\tRemote IP   : The IP you want to connect to"
		<< "\n\tRemote Port : The port you want to connect to"
		<< "\n\tLocal port  : Uour port"
		<< "\nLocal port should be the same as remote port on the other instance of the application"
		<< "\n==========================================================================================================\n\n";

	std::cout << "Enter remote IP ( 127.0.0.1  for local connections ) : ";
	std::cin >> IP;
	std::cout << "...and remote port : ";
	std::cin >> remotePort;

	std::cout << "Enter local port : ";
	std::cin >> localPort;

	udpConnection.Init( IP, remotePort, localPort );


	uint8_t command = 0;

	while ( !udpConnection.WasQuit() )
	{
		std::cout
			<< "Your command : "
			<< "\n\t0 : Send a message"
			<< "\n\t1 : Quit"
			<< "\n\t2 : Check for data"
			<< std::endl;

		std::cin >> command;

		if ( command == '0' )
			udpConnection.Send( "This is a test" );
		else if ( command == '1' )
			udpConnection.Send( "quit" );
		else if ( command == '2' )
			udpConnection.CheckForData();
		else
			std::cout << "Illegal command\n";
	}

	return 0;
}
*/






/*
int main(int argc, char *argv[]) {
    IPaddress serverIP;
    UDPsocket udpsock;
    UDPpacket* recv_packet;
    SDLNet_SocketSet socketset = NULL;
    int numused;
    static const int MAX_PACKET_SIZE = 30;

    if (SDLNet_Init() < 0) {
      printf("Couldn't initialize net: %s\n", SDLNet_GetError());
      exit(1);
    }

    udpsock = SDLNet_UDP_Open(8888);
    if(!udpsock) {
      printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
      exit(2);
    } else {
      printf("listening on 0.0.0.0:8888\n");
    }

    socketset = SDLNet_AllocSocketSet(2);
    if ( socketset == NULL ) {
      fprintf(stderr, "Couldn't create socket set: %s\n", SDLNet_GetError());
      exit(2);
    }

    numused = SDLNet_UDP_AddSocket(socketset,udpsock);
    if(numused==-1) {
      printf("SDLNet_AddSocket: %s\n", SDLNet_GetError());
      exit(2);
    }

    recv_packet = SDLNet_AllocPacket(MAX_PACKET_SIZE);
    if(!recv_packet) {
      printf("Could not allocate packet\n");
      exit(2);
    }

    while(1) {
      SDLNet_CheckSockets(socketset, ~0);
      if (SDLNet_SocketReady(udpsock)) {
        if (SDLNet_UDP_Recv(udpsock, recv_packet)){
          char *data = (char *)recv_packet->data;
          printf("[%s]\n",data);
          //recv_packet->address.port = 20001;
          SDLNet_UDP_Send(udpsock, -1, recv_packet);
        }
      }
    }
    return 0;
}
*/



/*
#include "SDL_net.h"
#include "SDL.h"
#undef main
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_TRAMA 128
#define MAX_DELAY 500

#define REMOTE_PORT 20001
#define LOCAL_PORT 8888

#define LOCALHOST "localhost"

#define MAX_SOCKETS 9
#define MAX_CLIENT 8

#define MAX_DELAY 500
#define ERROR (0xff)

#define BUFFER_SIZE 30

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
    IPaddress address;

    long initialMark = SDL_GetTicks();

    while(!DONE){
          int err = SDLNet_UDP_Recv(serverSocket, in);

          memcpy(&address,&in->address,sizeof(IPaddress));

          const char *host=SDLNet_ResolveIP(&address);
          Uint32 ipnum=SDL_SwapBE32(address.host);
          Uint16 port=SDL_SwapBE16(address.port);

          fprintf(pFile, "request from host=%d.%d.%d.%d port=%hd\n",
          ipnum>>24,
          (ipnum>>16)&0xff,
          (ipnum>>8)&0xff,
           ipnum&0xff,
           port);

            printf("request from host=%d.%d.%d.%d port=%hd\n",
            ipnum>>24,
            (ipnum>>16)&0xff,
            (ipnum>>8)&0xff,
            ipnum&0xff,
            port);


        if (err){

                int channel = SDLNet_UDP_Bind(serverSocket, 0, &address);
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
*/
