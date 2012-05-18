/* Autor: José Mª Pérez Ramos
 * Fecha: 2012.05.01
 * 
 * Programa de prueba para el segundo concurso de
 * de programación de Tuenti, prueba 9
 * BUSQUEDAS EN PARALELO!!!! CON HASH
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h> 



int comprobar(char* palabra, int len_palabra, char** list_palabras, int* cuenta_palabras, int longitud_lista, int** resultados, int fila, int columna, int archivo, int* hashes, int hash_palabra, int* longitudes){

	int suma_cuenta_palabras = 0;
	int indice_palabra;
	for (indice_palabra=0;indice_palabra<longitud_lista;indice_palabra++){	//PAra cada palabra
		if(hashes[indice_palabra] == hash_palabra){ //compruebo el hash
			int indice_letra;	
			for(indice_letra = 0; indice_letra<len_palabra; indice_letra++) //si es correcto, compruebo la totalidad de la palabra
				if (palabra[indice_letra]!=list_palabras[indice_palabra][indice_letra])
					break;

			if (indice_letra == len_palabra){ //encontrada! descontamos de cuenta_palabras, y, si se ha llegado a 0, actualizamos resultados y hashes
 				cuenta_palabras[indice_palabra]--;
				if (!cuenta_palabras[indice_palabra]){
					hashes[indice_palabra] = 0;
					resultados[indice_palabra][0] = archivo;
					resultados[indice_palabra][1] = fila;
					resultados[indice_palabra][2] = columna;
					longitudes[len_palabra]--;
				}
			}
		}
		suma_cuenta_palabras+=cuenta_palabras[indice_palabra]; 
	}

	return suma_cuenta_palabras;  //Si es 0, se terminará
}



#define MAX_W_LENGTH 400 //2*longitud maxima de palabra encontrada... menudos quebraderos de cabeza me ha dado depurar ese error
int multistrstr(char ** w_list, int * w_counts, int len_lista, int* hashes, int* longitudes, char* texto, int long_max_texto, int ** resultados, int archivo){
	//Se recorre texto, y siempre que se encuentre un espacio o un \n se mira a ver si lo que hemos leido es lo que estábamos buscando
	//se va calculando longitud y hash de lo leido mientras
	//Si Ecuenta_palabras == 0 (comprobar devuelve 0), volvemos con 0 para evitar abrir más archivos
	
	int indice_primera_letra = 0;
	int hash_palabra = 0;
	int fila = 1;
	int columna = 1;

	int indice_lectura = 0;
	char c;
	int longitud;
	char * palabra_leida = malloc(MAX_W_LENGTH*sizeof(char));
	for(indice_lectura = 0; indice_lectura <=long_max_texto; indice_lectura++){
		c=texto[indice_lectura];

		switch(c){	
		case '\n':
		case ' ':
		case '\0':
			longitud = indice_lectura - indice_primera_letra;
			if (longitudes[longitud]){ //quedan palabras de ese tamanio
				//Buscar palabra leida en w_list
				palabra_leida[longitud] = '\0';
				if(!comprobar(palabra_leida,longitud,w_list,w_counts,len_lista,resultados,fila,columna,archivo,hashes,hash_palabra,longitudes)){
					free(palabra_leida); 
					return 0;
				}
			}
			//reseteamos valores
			hash_palabra=0;
			indice_primera_letra = indice_lectura+1;	

			if (c=='\n'){
				columna = 1;
				fila++;
			}

			break;
		default:
			if ((indice_lectura>0) && (texto[indice_lectura-1]==' '))
				columna++;

			c = tolower(c);
			palabra_leida[indice_lectura - indice_primera_letra] = c;

			hash_palabra += c;
		}
	}
	//fprintf(stdout,"leido: %i chars, último: %c:%i\n",indice_lectura,c,c );
	free(palabra_leida);
	//fprintf(stdout,"Pasando al siguiente\n");
	return 1;
}


int calcularHash(char * palabra){
	//Hash muy sencillo, suma de los valores de las letras
	//tiene la ventaja de que se peude calcular al vuelo
	if (palabra[0]=='\0')
		return 0;

	return calcularHash(&(palabra[1])) + palabra[0];
}

int main(int argc, char* argv[]){
	// Se lee stdin y se crea una lista de palabras que buscar con la cantidad de veces que ha de aparecer cada una
	//Se crea una tabla de longitudes de palabras y otra hash
	int longitud_lista;
	if (fscanf(stdin,"%d", &longitud_lista) == EOF)
		exit(-1);
	//fprintf(stdout,"tamanio: %i\n",longitud_lista);

	char ** lista_palabras = malloc(longitud_lista*sizeof(char*));
	int * cuentas = malloc(longitud_lista*sizeof(int));
	int i,j;
	for(i=0; i< longitud_lista;i++){
		if (fscanf(stdin,"%s %d",lista_palabras[i] = malloc(MAX_W_LENGTH*sizeof(char)), &(cuentas[i])) == EOF)
			exit(-1);
		for(j=0;j<strlen(lista_palabras[i]);j++)
			lista_palabras[i][j] = tolower(lista_palabras[i][j]);
	}
	
	//for(i=0; i< longitud_lista;i++)
	//	fprintf(stdout,"W:%s c:%d\n",lista_palabras[i], cuentas[i]);

	int* longitudes = calloc(MAX_W_LENGTH,sizeof(int));
	for(i=0; i< longitud_lista;i++)
		longitudes[strlen(lista_palabras[i])]++;
	
	int * hashes = malloc(longitud_lista*sizeof(int));
	for(i=0; i< longitud_lista;i++)
		hashes[i] = calcularHash(lista_palabras[i]);

	int ** resultado = malloc(longitud_lista*sizeof(int*));
	for(i=0; i< longitud_lista;i++)
		resultado[i] = calloc(3,sizeof(int)); //nombre,fila,offset


	//mientras no se haya terminado de buscar, se mmap un fichero y se realiza la búsqueda sobre él	
	struct stat sb;
	char * nombre_archivo_base = "./documents/0";
 	char * nombre_archivo = malloc((strlen(nombre_archivo_base)+4)*sizeof(char));
	char * mapped;
	for (i = 1; i<= 800; i++){
		sprintf(nombre_archivo,"%s%03i", nombre_archivo_base, i);
		//fprintf(stdout,"Abriendo %s\n",nombre_archivo);
		int fd = open(nombre_archivo,O_RDONLY);
		if (fd == -1) {
                	perror ("open");
                	return 1;
          	}
		if (fstat (fd, &sb) == -1) {
                	perror ("fstat");
                	return 1;
          	}
		mapped = mmap (0, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
          	if (mapped == MAP_FAILED) {
                	perror ("mmap");
                	return 1;
          	}

		if(!multistrstr(lista_palabras,cuentas,longitud_lista,hashes,longitudes, mapped, sb.st_size, resultado,i))
			i=801;

		munmap(mapped,sb.st_size);
		close(fd);
	}
	
	free(cuentas);
	free(longitudes);
	free(hashes);
	free(nombre_archivo);

	//Se imprimen los resultados
	for(i=0; i< longitud_lista;i++){
		fprintf(stdout,"%i-%i-%i\n",resultado[i][0],resultado[i][1],resultado[i][2]);
		free(lista_palabras[i]);
		free(resultado[i]);
	}

	free(lista_palabras);
	free(resultado);
}


