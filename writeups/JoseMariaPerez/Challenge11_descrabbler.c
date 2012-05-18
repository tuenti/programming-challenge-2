/* Autor: José Mª Pérez Ramos
 * Fecha: 2012.05.02
 * 
 * Programa de prueba para el segundo concurso de
 * de programación de Tuenti, prueba 11
 *
 * Como hay que leer toda la lista al menos una vez,
 * leemos primero la palabra, generamos una tabla
 * con los caracteres que hay en esa palabra para poder buscar con O(1)
 * Lo siguiente leemos la lista, palabra por palabra, miramos a ver si tiene
 * al menos una de las letras de la palabra original y todas sus letras las tenemos en 
 * el rack, al mismo tiempo que almacenamos su puntuación
 * si tiene al menos una y la puntuacion es mejor, almacenamos
 * Por ultimo, se devuelve la mejor palabra encontrada.
 * SE HACE EN PARALELO PARA TODOS LOS CASOS
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct {
        int* letras_palabra_tablero;
	int* letras_usables;
	int  cuenta_letras_usables;
	char* mejor_palabra;
	int puntuacion;
}CASO;

#define MAX_W_LEN 26
#define ORIGEN_ALFABETO 65
#define FINAL_ALFABETO 91

int contenidosEn(int* cantidades_letras_palabra, int* cantidades_letras){
	int j;
	for(j= ORIGEN_ALFABETO; j <FINAL_ALFABETO; j++)
		if (cantidades_letras_palabra[j]>cantidades_letras[j])
			return 0;

	return 1;
}

void comprobarCasos(CASO** lista_casos, int num_casos, int* array_palabra, int* valor_letras, int num_letras_restantes, char* palabra){
	int i,j, puntuacion_palabra=0;
	CASO * temp;
	int * comprobarPuntuacion = calloc(num_casos,sizeof(int));
	for(j= ORIGEN_ALFABETO; j <FINAL_ALFABETO; j++){ //para cada letra del alfabeto, comprobamos si está en la palabra
		if (!array_palabra[j])
			continue;

		if(!num_letras_restantes) //No tiene sentido seguir buscando letras
			break;

		num_letras_restantes -= array_palabra[j]; //
		
		puntuacion_palabra += array_palabra[j]*valor_letras[j]; //Si está, actualizamos puntuacion, suponemos que esa letra es la que está en el tablero
		array_palabra[j]--;
		
		for(i=0; i< num_casos;i++){ //Para cada caso, comprobamos si se pueden construir la palabra, en ese caso retrasamos la comp. de puntuación
			temp = lista_casos[i];
			if ((temp->letras_palabra_tablero[j]) && contenidosEn(array_palabra,temp->letras_usables))
				comprobarPuntuacion[i]=1;
		}

		array_palabra[j]++; //Volvemos a suponer que la letra no está en el tablero
	}

	for(i=0; i< num_casos;i++){ //miramos la puntuación para comprobar si es mejor
		temp = lista_casos[i];
		if ((comprobarPuntuacion[i]) && ((temp->puntuacion) < puntuacion_palabra)){
			temp->puntuacion = puntuacion_palabra;
			strcpy(temp->mejor_palabra,palabra);
		}
	}
}

int main(int argc, char* argv[]){
	int num_casos;
	if (fscanf(stdin,"%d", &num_casos) == EOF)
		exit(-1);

	//Leemos todos los casos y montamos las estructuras
	CASO **  lista_casos = malloc(num_casos*sizeof(CASO*));
	int i,j;
	CASO * temp;
	char * buffer_palabra = malloc((MAX_W_LEN+2)*sizeof(char));
	char * palabra_vacia = "";
	for(i=0; i< num_casos;i++){
		temp = malloc(sizeof(CASO));
		lista_casos[i] = temp;
		temp->puntuacion = 0;
		temp->cuenta_letras_usables = 0;
		temp->letras_palabra_tablero = calloc(256,sizeof(int));
		temp->letras_usables = calloc(256,sizeof(int));
		temp->mejor_palabra = malloc((MAX_W_LEN+2)*sizeof(char));
		temp->mejor_palabra[0]='\0';

		if (fscanf(stdin,"%s ",buffer_palabra) == EOF)
			exit(-1);
		for(j=0;j<MAX_W_LEN;j++){
			if (buffer_palabra[j] == '\0')
				break;

			temp->cuenta_letras_usables++;
			temp->letras_usables[toupper(buffer_palabra[j])]++;		
		}	

		//fprintf(stdout,"<%s>",buffer_palabra);

		if (fscanf(stdin,"%s",buffer_palabra) == EOF)
			exit(-1);
		for(j=0;j<MAX_W_LEN;j++){
			if (buffer_palabra[j] == '\0')
				break;

			temp->letras_palabra_tablero[toupper(buffer_palabra[j])]++;		
		}

		//fprintf(stdout,"<%s>\n",buffer_palabra);
	}


	int* valorLetra = calloc(256,sizeof(int));
	//Se construye la tabla de valores de las letras:
	char ** valorLetras = calloc(11,sizeof(char*));
	valorLetras[1]="AEILNORSTU";
   	valorLetras[2]="DG";
    	valorLetras[3]="BCMP";
    	valorLetras[4]="FHVWY";
    	valorLetras[5]="K";
    	valorLetras[8]="JX";
    	valorLetras[10]="QZ";

	for(i = 1; i<= 10; i++)
		if (valorLetras[i] == NULL)
			continue;
		else
			for(j = 0; j<26;j++)
				if (valorLetras[i][j] == '\0')
					break;
				else
					valorLetra[valorLetras[i][j]] = i;

	//for(i = 0; i< 256; i++)
	//	fprintf(stdout,"%i:%c->%i\n",i,i,valorLetra[i]);



	//Buscamos en la lista, una única pasada
	FILE * ficheroLista = fopen("descrambler_wordlist.txt", "r");


	char c;
	while(fgets(buffer_palabra,MAX_W_LEN+2, ficheroLista)!= NULL){
		//Hemos leido una palabra de la lista, 
		//creamos su array yse comprueba si es válida para cada caso,
		int* array_palabra_leida = calloc(256,sizeof(int));
		int longitud_palabra_leida = 0;
		for(j = 0; j<26;j++){
			c=buffer_palabra[j];
			if ((c=='\n') || (c == '\0')){
				buffer_palabra[j] = '\0';
				break;
			}
			array_palabra_leida[c]++;
			longitud_palabra_leida++;
		}

		/*getchar();
		fprintf(stdout,"Buscando palabra: >%s<, letras: \n",buffer_palabra);
		for (i=0;i<256;i++)
			if(array_palabra_leida[i])
				fprintf(stdout,"%c",i);
		fprintf(stdout,"\n",i);
		*/
	
		comprobarCasos(lista_casos,num_casos, array_palabra_leida, valorLetra,longitud_palabra_leida,buffer_palabra);
		
		free(array_palabra_leida);
	}

	//Imprimir resultados
	fclose(ficheroLista);
	for(i=0; i< num_casos;i++){
		temp = lista_casos[i];
		fprintf(stdout,"%s %i\n",temp->mejor_palabra,temp->puntuacion);
		
		free(temp->letras_palabra_tablero);
		free(temp->letras_usables);
		free(temp->mejor_palabra);
		free(temp);
	}
	free(lista_casos);
	free(buffer_palabra);
	free(valorLetra);
	free(valorLetras);

}


