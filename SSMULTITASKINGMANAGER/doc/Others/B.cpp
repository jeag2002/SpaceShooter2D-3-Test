#include <stdio.h>
#include <stdarg.h>
#include "B.h"

B::B(){
}

B::~B(){
}


//funcion miembro de B con dos parametros
int B::prueba(int a, int b){
	printf("\nsoy funcion prueba B");
	return a+b;
}


//funcion miembro de B con un parametro fijo y el resto variables
int B::prueba1(int a, ...){
	
	printf("\nsoy funcion variarg prueba B");
	
	va_list ap;
    int j;
	int inc = a;

    va_start(ap, a);
    for(j=0; j<a; j++)
       inc+=va_arg(ap, int); //Requires the type to cast to. Increments ap to the next argument.
    va_end(ap);

    return inc;
}

//funcion miembro de B estatico
int B::prueba2(int a, int b){
	printf("\nsoy funcion estatica prueba2 B");
	return a-b;
}