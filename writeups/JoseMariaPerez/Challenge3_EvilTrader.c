/* Autor: José Mª Pérez Ramos
 * Fecha: 2012.04.27
 * 
 * Programa de prueba para el segundo concurso de
 * de programación de Tuenti, prueba 3
 *
 */

#include <stdlib.h>
#include <stdio.h>

struct item {
	struct item * next;
	struct item * prev;
        int menor;
	long instanteMenor;
        int mayor;
	long instanteMayor;
	int diferencia;
};

typedef struct item DIF;


DIF * crearDiferencia(int instante, int valor, DIF * anterior){
	DIF * nueva = malloc(sizeof(DIF));
	nueva->next = NULL;
	nueva->prev = anterior;
        nueva->menor = valor;
	nueva->instanteMenor = instante;
        nueva->mayor = valor;
	nueva->instanteMayor = instante;
	nueva->diferencia = 0;
	return nueva;
}

int eliminarDiferencia(DIF * condenada){
	condenada->prev->next = condenada->next;
	
	if(condenada->next != NULL)
		condenada->next->prev = condenada->prev;
	
	free(condenada);

	return 0;
}

int main(int argc, char* argv[]){
	DIF cabecera; //Lista doblemente enlazada de diferencias
	cabecera.next = NULL;
	cabecera.diferencia = 0;
	
	DIF * mejor = &cabecera; 

	int num_leido;
	long instante = 0;
	while(fscanf(stdin,"%i",&num_leido)!=EOF){
		DIF * modificado = NULL;
		DIF * ultimo = &cabecera;

		while(ultimo->next != NULL){
			ultimo = ultimo->next;

			//Comprobamos última diferencia
			if(num_leido >= ultimo->mayor){
				//El número leído es mayor, hay que actualizar 
        			ultimo->mayor = num_leido;
				ultimo->instanteMayor = instante;
				ultimo->diferencia = num_leido - ultimo->menor;
			
				if(modificado != NULL){
					//Como ya habia un modificado, borramos el anterior y actualizamos
					//los datos del último con los mejores (evitamos borrar último)
					if(modificado->diferencia > ultimo->diferencia){
						ultimo->menor = modificado->menor;
						ultimo->instanteMenor = modificado->instanteMenor;
						ultimo->diferencia = modificado->diferencia;
					}
						
					eliminarDiferencia(modificado);
				}

				modificado = ultimo; //Guardamos el modificado	
			}

			if (ultimo->diferencia >= mejor->diferencia)
				mejor = ultimo;
		}

		if(modificado == NULL)
			ultimo->next = crearDiferencia(instante,num_leido,ultimo);
			//No se ha modificado ninguno, añadimos una
			//dif nueva al final con todos los valores los actuales
			
		
		instante++;
	}
	fprintf(stdout,"%li %li %i\n",mejor->instanteMenor * 100,mejor->instanteMayor * 100,mejor->diferencia);
}


