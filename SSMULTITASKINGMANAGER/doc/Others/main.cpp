//funciones de ejemplo que enseñan a como pasar funciones a otras funciones
//las premisas de las que se parte de entrada es que se sabe que clase se ha
//de llamar y los parametros de entrada/salida minimos para hacerlo.
//para ello defino las siguientes clases:

//main.cpp (esta clase ;-)) que es la clase que ejecuta los metodos de A
//A.cpp que es la clase donde estan implementados los wrappers que nos permitirán ejecutar los metodos de B
//B.cpp que es la clase que contiene los metodos que se quieren ejecutar.

//para cualquier otro caso que no cumpla estas premisas ya se debe plantearse la utilización de 
//templates y reflection.

//para estos ejemplos me he basado en esto: http://www.parashift.com/c++-faq-lite/pointers-to-members.html
//compilado con gcc 4.4.1, Code::Blocks 10.05, en un entorno Windows XP SP3 virtualizado con parallels desktop 7.0


#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <iostream>
#include "B.h"
#include "A.h"

using namespace std;


//no hace falta que esté declarado así... se puede inicializar
//en otra parte y despues aprovechar el programa.
B* b;

//wrapper a la funcion que necesitamos.
//también se podría llamar de manera directa una 
//función estatica al signal...
//por ejemplo signal(SIGINT,B::prueba2)

void bPruebaWrapper(int param){
	int valor = b->prueba(2,2);
	printf("\nvalor ejecutado %d",valor);
	//una vez llamado la funcion wrapper, se vuelve a crear el signal
	//si queremos que se vuelva a ejecutar.
	signal(SIGINT,bPruebaWrapper);
}

//funcion que espera un segundo
void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}


int main()
{

b = new B();
signal(SIGINT,bPruebaWrapper);

int n;
printf("\nFuncion PITBULL");


//por cada iteracion
//1-espera un segundo
//2-lanza el signal raise(SIGINT)
for (n=3; n>0; n--){
    wait (1);
	printf("\n%d",n);
	raise(SIGINT);
}

printf("\nDALE!");
return 0;
}






/*
int main()
{
	
	//declaro acceso a funcion prueba (metodo no estatico de 2 parametros clase B) como un tipo
	typedef  int (B::*pBA)(int,int);

	//declaro acceso a funcion prueba1 (metodo no estatico de 1 parametro fijo y tres variables) como un tipo
	typedef  int (B::*pBB)(int,...); 

	B *b = new B();
	A *a = new A();

	printf("\npaso de funciones por parametros");

	int valor = a->processBprueba2(prueba,3);
	printf("\npaso de funcion por parametro de la misma clase (Main) %d",valor);

	valor = a->processBprueba2(B::prueba2,3);
	printf("\npaso de funcion por parametro metodo estatico de dos params clase B %d",valor);

	pBA funcionA = &B::prueba;	
	valor = a->processBprueba(*b, funcionA, 2);
	printf("\npaso de funcion por parametro metodo publico no estatico de dos params clase B %d",valor);

	pBB funcionB = &B::prueba1;
	valor  = a->processBprueba3(*b,funcionB,3,0,1,2);
	printf("\npaso de funcion por parametro metodo publico no estatico de 3 params variables clase B %d",valor);


	return 0;
}*/
