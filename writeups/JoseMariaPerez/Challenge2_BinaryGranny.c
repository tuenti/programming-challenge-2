/* Autor: José Mª Pérez Ramos
 * Fecha: 2012.04.27
 * 
 * Programa de prueba para el segundo concurso de
 * de programación de Tuenti, prueba 2
 *
 */

#include <stdio.h>
#include <stdlib.h>

long leerLong(){
	long ret;
	fscanf(stdin,"%li",&ret);
	return ret;			
}
int contarUnosMax(long N){
	int numero_de_unos = 0;	

	while(N>0){
		//Si el último bit es 0, lo contamos como 2 y restamos 1 a N
		/* Esto es porque si el último es 1, solo se puede conseguir 
		 * sumando 0 y 1, pero si es 0, se puede conseguir con 1+1
		 */
		if((N & 1) == 0){
			numero_de_unos +=2;
			N -= 2; 
		}else
			numero_de_unos +=1;
			//N -=1; -> se borra al desplazar N
			
		N = N >> 1;
	}
	return numero_de_unos;
}

int main(int argc, char* argv[]){
	//Se lee número de casos totales
	long num_casos_total = leerLong(), num_caso, N_granny;

	//Para cada caso, se lee un long y se imprime el número máximo de
	// 1 que pueden tener dos números que sumados den el long
	for(num_caso = 1; num_caso <= num_casos_total; num_caso++)
		if ((N_granny = leerLong())>=0)
			fprintf(stdout,"Case #%li: %i\n",num_caso,contarUnosMax(N_granny));
}
