/* Autor: José Mª Pérez Ramos
 * Fecha: 2012.04.30
 * 
 * Programa de prueba para el segundo concurso de
 * de programación de Tuenti, prueba 7
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//varias alternativas:
	//alfabeto completo
	//alfabeto reducido
	//alfabeto reducido sin caracteres de palabra
	//solo primeros caracteres de subentradas //peor en caso de muchas subentradas

char * eliminarCaracter(char * alfabeto,char c){
	char * ret = NULL;	
	int indiceLectura = 0;
	int indiceInsercion = 0;
	char a;
	while((a=alfabeto[indiceLectura++]) != '\0'){
		if (a == c)
			continue;

		if (ret==NULL)
			ret = malloc(63*sizeof(char));

		ret[indiceInsercion++] = a;
	}
	if (ret!=NULL)
		ret[indiceInsercion++] = '\0';

	return ret;
}


void resolver(char * alfabeto, char ** listaSubentradas,int * posicionSubentradas,int tamanio_lista_subentradas, char* palabra, int posicion_escritura_palabra){
	//palabra[posicion_escritura_palabra] = '\0';
	//fprintf(stdout,">%s\n",palabra);		

	if(alfabeto == NULL){ //Si no queda alfabeto, es que todas las letras del alfabeto están en la palabra, por lo que hemos terminado
		palabra[posicion_escritura_palabra] = '\0';
		fprintf(stdout,"%s\n",palabra);
		return;
	}

	int c,i = 0; 
	while((c = alfabeto[i++])!='\0'){
		//Para cada letra del alfabeto, buscamos que si aparece
		//en una subentrada, aparece en la primera posición de la subentrada
		
		//Se va a realizar una copia de las posiciones en las subentradas
		int * nueva_posicionSubentradas = calloc(tamanio_lista_subentradas,sizeof(int));

		int aparece_en_subentrada = 0;

		int suma_posiciones_encontradas = 0;

		int indice_filas_subentradas;
		char * subentrada;
		for(indice_filas_subentradas = 0; indice_filas_subentradas < tamanio_lista_subentradas; indice_filas_subentradas++){
			//Recorremos la lista de subentradas
			subentrada = listaSubentradas[indice_filas_subentradas];
			int posicion_inicial_subentrada = posicionSubentradas[indice_filas_subentradas];
		
			//Copiamos la posicion inicial
			nueva_posicionSubentradas[indice_filas_subentradas] = posicion_inicial_subentrada;

			int indice_caracter_subentrada = posicion_inicial_subentrada;
			char caracter_subentrada;
			while((caracter_subentrada= subentrada[indice_caracter_subentrada])!= '\0'){
				//recorremos la subentrada
				if(caracter_subentrada == c){
					aparece_en_subentrada = 1;
					suma_posiciones_encontradas += (indice_caracter_subentrada-posicion_inicial_subentrada);
	
					nueva_posicionSubentradas[indice_filas_subentradas] = indice_caracter_subentrada+1;
					//Si no es el primero, da igual porque el array se descartará
					break;
				}
				indice_caracter_subentrada++;
			}
		}
 		
		if(aparece_en_subentrada && !suma_posiciones_encontradas){ 
			//Aparece y es siempre en las primeras posiciones de las subentradas
			//Llamamos recursivamente con los nuevos inicios quitando el caracter del alfabeto
			//fprintf(stdout,"Fin: %i\n",suma_posiciones_caracter_nulo);
			palabra[posicion_escritura_palabra] = c;
		resolver(eliminarCaracter(alfabeto,c),listaSubentradas,nueva_posicionSubentradas,tamanio_lista_subentradas,palabra,posicion_escritura_palabra+1);
		}

		//borramos
		free(nueva_posicionSubentradas);
	}
	free(alfabeto);
}

int main(int argc, char* argv[]){
	char* alfabetoCompleto = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int longitud_alfabeto = strlen(alfabetoCompleto);
	
	int tamanio_e = 20;
	char ** e = malloc(tamanio_e*sizeof(char*));
	int puntero_e = 0;
	int *tabla_caracteres_encontrados = calloc(256,sizeof(int));

	char* buffer = malloc(sizeof(char)*(longitud_alfabeto+2));
	while(fgets(buffer,longitud_alfabeto+1, stdin)!= NULL){
		//Quitar salto de línea mientras buscamos caracteres del alfabeto
		int indice_busqueda = 0;
		char c;
		while((c = buffer[indice_busqueda++])!='\0'){
			if (c == '\n'){
				buffer[indice_busqueda-1] = '\0';
				break;
			}else
				tabla_caracteres_encontrados[c] = 1;
		}		

		//insertamos buffer en e (lista de subcadenas) y creamos un nuevo buffer
		e[puntero_e++] = buffer;	
		buffer = malloc(sizeof(char)*(longitud_alfabeto+2));
		
		if(puntero_e == tamanio_e)
			e = realloc(e,(tamanio_e*=2)*sizeof(char*));
	}

	char * alfabeto = calloc(longitud_alfabeto+1,sizeof(char));
	int indice_insercion = 0;
	int indice_lectura = 0;
	for (indice_lectura = 0;indice_lectura<longitud_alfabeto;indice_lectura++)
		if (tabla_caracteres_encontrados[alfabetoCompleto[indice_lectura]])
			alfabeto[indice_insercion++] = alfabetoCompleto[indice_lectura];
			
	free(tabla_caracteres_encontrados);
	free(buffer);

	/*fprintf(stdout,"alfabeto: <%s>\n",alfabeto);
	int jjj = 0;
	for(;jjj < puntero_e; jjj++)
		fprintf(stdout,"subentrada: <%s>\n",e[jjj]);*/

	char * palabra = malloc(sizeof(char)*(indice_insercion+1));
	int * lista_posiciones = calloc(puntero_e,sizeof(int));
	resolver(alfabeto,e,lista_posiciones,puntero_e,palabra,0);
	free(palabra);
	free(lista_posiciones);
}


