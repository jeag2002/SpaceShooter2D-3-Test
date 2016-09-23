#include "SDL_net.h"
#include "SDL.h"
#undef main
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>


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
	UDPpacket **packetV;

	packetV = SDLNet_AllocPacketV(12, 100);

	bool endTransmision = false;

	Uint16 port = 12000;
	Uint16 remoteport = 8888;
	int packetSize = 1200;

    FILE * pFile;
    pFile = fopen ("UDPCLIENT.log","w");

	std::string ip = "127.0.0.1";

    std::cout << "Enter local port : ";
	std::cin >> port;


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

    while(!endTransmision){

        for(int i=0; i<100; i++){buffer[i]='\0';}
        num_trama++;
        sprintf(buffer,"(*)MSG TO SERVER TRAMA - (%d)",num_trama);
        std::string msg(buffer);

        for(int i=0; i<100; i++){packet->data[i]='\0';}
        memcpy(packet->data, msg.c_str(), msg.length() );
        packet->len = msg.length();

        if ( SDLNet_UDP_Send(ourSocket, -1, packet) == 0 )
        {
            std::cout << "\tSDLNet_UDP_Send failed : " << SDLNet_GetError() << "\n";
            exit(-1);
        }

        std::cout << "\tData send (TO SERVER) : " << packet->data << "\n";
        fprintf(pFile,"[SEND MSG CLIENT TO SERVER] [%s]\n",packet->data);


        SDL_Delay(100);

        int numrecv = 0;
        for(int i=0; i<100; i++){packet->data[i]='\0';}
        numrecv=SDLNet_UDP_RecvV(ourSocket, packetV);

        if(numrecv==-1) {
           std::cout << "\tData not get from SERVER\n";
           exit(-1);
        }

        std::cout << "sizeofbuffer: " << numrecv << "\n";
        fprintf(pFile,"[GET MSG SERVER FROM SERVER] sizeofbuffer [%d]\n",numrecv);


        for(int i=0; i<numrecv; i++) {
            std::cout << "\tData received (FROM SERVER) : " << packetV[i]->data << "\n";
            fprintf(pFile,"[GET MSG SERVER FROM SERVER][%d] [%s]\n",i,packetV[i]->data);
        }




        /*
        while(!SDLNet_UDP_Recv(ourSocket, packet)){
                SDL_Delay(10);
        }

        std::cout << "\tData received (FROM SERVER) : " << packet->data << "\n";
        fprintf(pFile,"[GET MSG SERVER FROM SERVER] [%s]\n",packet->data);
        */

    }


    SDLNet_UDP_Close(ourSocket);
    SDLNet_FreePacket(packet);
    SDLNet_FreePacketV(packetV);
    SDLNet_Quit();
    SDL_Quit();

    fclose (pFile);

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
void initSDLWindows(){

     SDL_Window* window;
     SDL_Renderer *render;
     window = NULL;

     if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ){
        exit(-1);
     }

     if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
     }

      window = SDL_CreateWindow( "Console SSNETWORKMANAGER-CLIENT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );
      if( window == NULL ){
         exit(-1);
      }

      render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

      if (render == NULL){
        exit(-1);
      }
}





int main(int argc, char **argv)
{
    UDPsocket sd;
    UDPpacket *p;
    IPaddress srvadd;

    SDLNet_Init();

    if(!(sd = SDLNet_UDP_Open(0)))
    {
        printf("Could not create socket\n");
        SDLNet_Quit();
        SDL_Quit();
        exit(1);
    }

    IPaddress* myaddress = SDLNet_UDP_GetPeerAddress(sd, -1);
    if(!myaddress)
    {
        printf("Could not get own port\n");
        exit(2);
    }
    printf("My port: %d\n", myaddress->port);
    UDPpacket* recvp = SDLNet_AllocPacket(30);
    if(!recvp)
    {
        printf("Could not allocate receiving packet\n");
        exit(3);
    }

    UDPsocket socket;
    socket = SDLNet_UDP_Open(myaddress->port);
    //socket = SDLNet_UDP_Open(8888);
    if(!socket)
    {
        printf("Could not allocate receiving socket\n");
        exit(4);
    }

    // resolve server host
    SDLNet_ResolveHost(&srvadd, "localhost", 8888);

    if(!(p = SDLNet_AllocPacket(30)))
    {
        printf("Could not allocate packet\n");
        SDLNet_Quit();
        SDL_Quit();
        exit(2);
    }

    p->address.host = srvadd.host;
    p->address.port = srvadd.port;

    bool run = true;

    initSDLWindows();

    while(run)
    {
        if(SDLNet_UDP_Recv(socket, recvp))
        {
            printf("Receiving packet\n");
            char* data = (char*)recvp->data;
            if(strcmp(data, "left") == 0){
                printf("received left\n");
            }else if (strcmp(data, "right") == 0){
                printf("received right\n");
            }
        }

        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        p->data = (Uint8 *)"left";
                        p->len = strlen("left") + 1;
                        SDLNet_UDP_Send(sd, -1, p);
                        break;
                    case SDLK_RIGHT:
                        p->data = (Uint8 *)"right";
                        p->len = strlen("right") + 1;
                        SDLNet_UDP_Send(sd, -1, p);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    return 0;
}
*/








/*
#define MAX_DELAY 500
#define LOCALHOST "localhost"
#define REMOTE_PORT 8888
#define LOCAL_PORT 20001
#define BUFFER 30

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
*/
