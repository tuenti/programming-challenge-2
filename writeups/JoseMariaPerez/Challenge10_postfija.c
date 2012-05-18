/* Autor: José Mª Pérez Ramos
 * Fecha: 2012.05.01
 * 
 * Programa de prueba para el segundo concurso de
 * de programación de Tuenti, prueba 10
 *
 @ 	:  +
mirror  : *(-1)
conquer : %
&	: /
$	: -
. 	: finLinea
dance 	: intercambia posiciones
breadandfish: push top (copiar el top)
fire	: pop
#	: *

 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h> 


void leerRestoPalabra(){
	//Avanza lectura stdin hasta que llegamos al final de la palabra
	char c;
	while((c = fgetc(stdin))!=EOF)
		if ((c == ' ') || (c == '\n') || (c == '\0'))
			break;
}

int main(int argc, char* argv[]){
	
	int tamanio_pila = 100;
	long * pila = malloc(tamanio_pila*sizeof(long));
	int indice_insercion = 0;
	char c;
	long temp;

	//leemos caracteres de stdin y modificamos la pila de forma acorde
	while((c=fgetc(stdin))!=EOF){
		switch(c){
		case '@':	//pop y suma
			indice_insercion--;
			pila[indice_insercion-1] += pila[indice_insercion];
			break;
		case '$':	//pop y resta
			indice_insercion--;
			pila[indice_insercion-1] -= pila[indice_insercion];
			break;
		case 'm':	//top * -1
			pila[indice_insercion-1] *= -1;
			leerRestoPalabra();
			break;
		case 'c':	//pop y modulo
			indice_insercion--;
			pila[indice_insercion-1] %= pila[indice_insercion];
			leerRestoPalabra();
			break;
		case '&':	//pop y division
			indice_insercion--;
			pila[indice_insercion-1] /= pila[indice_insercion];
			break;
		case '.':	//print y clear
			fprintf(stdout,"%li\n",pila[indice_insercion-1]);
			indice_insercion = 0;
			break;
		case 'd':	//intercambia top y next(top) 
			temp = pila[indice_insercion-1];
			pila[indice_insercion-1] = pila[indice_insercion-2];
			pila[indice_insercion-2] = temp;
			leerRestoPalabra();
			break;
		case 'b':	//Copiamos el elemento superior de la pila en la cima
			pila[indice_insercion] = pila[indice_insercion-1];
			indice_insercion++;

			if(indice_insercion == tamanio_pila)
				pila = realloc(pila,(tamanio_pila *=2)*sizeof(long));

			leerRestoPalabra();
			break;
		case 'f':	//pop de la pila
			indice_insercion--;
			leerRestoPalabra();
			break;
		case '#':	//pop y multiplicacion
			indice_insercion--;
			pila[indice_insercion-1] *= pila[indice_insercion];
			break;
		case ' ': //ignorar c
		case '\n':	//ignorar c
			break;
		case '\0':	//fin de string
			free(pila);
			return 0;
		default:	//se compone el numero caracter a caracter y se añade a la pila
			temp = c -'0';
			//fprintf(stderr,"leido %c de numero\n",c);
			while((c = fgetc(stdin))!=EOF){
				if ((c == ' ') || (c == '\n') || (c == '\0'))
					break;

				temp *= 10;
				temp += c -'0';
			}
			//fprintf(stderr,"-> %li apilado\n", temp);
			pila[indice_insercion++] = temp;

			if(indice_insercion == tamanio_pila)
				pila = realloc(pila,(tamanio_pila *=2)*sizeof(long));
		}
	}
	free(pila);
}


