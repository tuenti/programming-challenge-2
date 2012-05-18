/* Autor: José Mª Pérez Ramos
 * Fecha: 2012.04.30
 * 
 * Programa de prueba para el segundo concurso de
 * de programación de Tuenti, prueba 6
 * 
 */

#include <stdlib.h>
#include <stdio.h>

double filas_conforme(int* lista, double num_columnas,int* indice_final_primera_fila, int* primera_fila_menos_ultimo){
	int indice = *indice_final_primera_fila;
	int i_filas= 0;
	int i_columnas = *primera_fila_menos_ultimo;

	int valor_longitud;
	while(valor_longitud = lista[indice++]){ //lista acaba con un int 0
		int tamanio_fila_con_valor = i_columnas + valor_longitud;

		if(num_columnas > tamanio_fila_con_valor){
			i_columnas += valor_longitud;
		}else if(num_columnas == tamanio_fila_con_valor){
			if(!i_filas){ //si es la primera fila almacenamos para reutilizar
				*indice_final_primera_fila = indice-1;
				*primera_fila_menos_ultimo = i_columnas;
			}

			i_columnas = 0;
			i_filas++;
			if(!lista[indice])
				return i_filas;
		}else if (i_columnas){ //num_columnas >= valor
			if(!i_filas){ //si es la primera fila almacenamos para reutilizar
				*indice_final_primera_fila = indice-1;
				*primera_fila_menos_ultimo = i_columnas;
			}

			i_columnas = valor_longitud;
			i_filas++;		
		}else
			return 0;
	}	

	return  i_filas+1;
}

int mejorResolucion(int* lista_longitudes_palabras,int longitud_palabra_maxima,int suma_total_lista, double alto_pixeles, double ancho_pixeles){
	int mejor_resolucion = 0;
	
	int indice_final_primera_fila = 0;
	int primera_fila_menus_ultimo =0;
		
	double num_columnas;
	for(num_columnas = longitud_palabra_maxima; num_columnas <=suma_total_lista; num_columnas++){
		
		int resolucion_horizontal = (ancho_pixeles / (num_columnas-1)); //descontamos el espacio al final de las filas
		
		if (resolucion_horizontal<=mejor_resolucion) //De aquí en adelante, siempre serán menores
			break;

		double num_filas = filas_conforme(lista_longitudes_palabras,num_columnas,&indice_final_primera_fila,&primera_fila_menus_ultimo);

		if(!num_filas) //No vale la matriz
			continue;

		int resolucion_vertical = (alto_pixeles / num_filas); 

		//fprintf(stdout,"Válido: c:%10e f:%10e w:%e h:%e\n",num_columnas,num_filas,ancho_pixeles,alto_pixeles);
		//fprintf(stdout,"Resoluciones: H:%i V:%i",resolucion_horizontal,resolucion_vertical);			

		if (resolucion_vertical < resolucion_horizontal) //Ajustamos al menor de las dos
			resolucion_horizontal = resolucion_vertical;

		//fprintf(stdout," Mejor de las dos:%i \n",resolucion_horizontal);

		if (resolucion_horizontal > mejor_resolucion){ //Si es mejor que la que teníamos, actualizamos
			mejor_resolucion = resolucion_horizontal;
			//fprintf(stdout,"Mejor: %i\n",resolucion_horizontal);			
		}		
	}

	return mejor_resolucion;
}

int tratarCaso(){
	//Leemos datos de entrada
	int W,H,ct;
	char * buffer = calloc(5002,sizeof(char));
	fgets(buffer, 5002, stdin);
	//fprintf(stdout, "1>>> %s <<<\n",buffer);
	sscanf(buffer,"%d %d %d", &W,&H,&ct);

	int indice_insercion = 0;
	int max_tamanio = 25;
	int* lista = malloc(max_tamanio * sizeof(int));
	int no_blancos = 0;
	int total_caracteres = 0;
	int maximo_valor = 0;
	

	fgets(buffer, 5002, stdin);
	//fprintf(stdout, "2>>> %s <<<\n",buffer);
	int longitud = 0;
	int indice_lectura = 0;
	for(;indice_lectura<5002;indice_lectura++){
		switch(buffer[indice_lectura]){
		case '\n':
		case '\0':
			indice_lectura = 5002;
		case ' ':
			if(longitud >0){
				longitud+=1; //sumar 1 a todas longitudes para 'olvidar' los espacios, después se descuenta	

				if (maximo_valor < longitud)
					maximo_valor = longitud; 
		
				total_caracteres += longitud;
				lista[indice_insercion++] = longitud; 
				longitud = 0;
				if (indice_insercion == max_tamanio)
					lista = realloc(lista, (max_tamanio*=2)*sizeof(int));
			}

			break;
		default:	
			no_blancos++;
			longitud++;	
		}	
	}
	free(buffer);
	lista[indice_insercion++] = 0;
	
	int tamanio_fuente = mejorResolucion(lista,maximo_valor,total_caracteres,(double)(H*ct),(double)(W*ct));
	
	free(lista);

	//fprintf(stdout,"-> palabras %i res: %i\n",indice_insercion-1,tamanio_fuente);

	if (tamanio_fuente){
		double longitud_hilo = ((double)(no_blancos * tamanio_fuente*tamanio_fuente))/((double)(2 * ct));
		//fprintf(stdout,"->c:%i r:%i ct:%i l:%e \n",no_blancos,tamanio_fuente,ct,longitud_hilo);

		int longitud_hilo_int = (int) longitud_hilo;

		if( longitud_hilo == (double)longitud_hilo_int)
			return longitud_hilo_int;
		else
			return longitud_hilo_int+1;
	}else
		return 0;

}

int main(int argc, char* argv[]){
	long num_casos;
	
	if (fscanf(stdin,"%ld",&num_casos) == EOF)
		exit(1);
	getchar();
	int i = 1;
	for(;i<=num_casos; i++)
		fprintf(stdout,"Case #%i: %i\n",i,tratarCaso());
}


