/* Autor: José Mª Pérez Ramos
 * Fecha: 2012.05.03
 * 
 * Programa de prueba para el segundo concurso de
 * de programación de Tuenti, prueba 13
 *
 */

#include <stdlib.h>
#include <stdio.h>


int mcm(int a, int b){
	//Calcula el mínimo común múltiplo de dos elementos
	int n;
	if (a>b){
		for(n=a;;n+=a){
			if(n%b == 0){
	  		  	return n;
			}
		}
	}else{
		for(n=b;;n+=b){
			if(n%a == 0){
	  		  	return n;
			}
		}
	}

	//Se podría hacer de otra forma, factorizando para sacar tablas de primos, pero
	// es demasiado para este problema
}


int* generarTablaSaltos(int N, int L){
	int * tablaSaltos = malloc(sizeof(int)*N);
	int indiceInsercion = 0;
	
	// En tablaSaltos se genera una simulación
	// Se crea una tabla X -> Y donde X es la posicion del elemento x antes del primer salto
	// e y es el elemento que queda después del salto en dicha posición
	// No es necesario generar más simulaciones ya que en una simulación comprobamos dónde se mueven todos los
	// elementos
	// Esta tabla también se puede ver de la siguiente manera:
	// para que el elemento E esté en la posición X, antes tiene que haber estado en la posición tablaSaltos[X], 
	// ya que de tablaSaltos[X] se mueve a X

	int i = L-1,j = N-1;
	while(indiceInsercion<N)
		if((i>=0) && (j>=L)){ //Quedan elementos en ambos mazos
			tablaSaltos[indiceInsercion++] = i--;
			tablaSaltos[indiceInsercion++] = j--;
		}else if(i<0) //Quedan solo elementos en el mazo de la derecha (NO L)
			tablaSaltos[indiceInsercion++] = j--;
		else //Quedan solo elementos en el mazo de la izquierda
			tablaSaltos[indiceInsercion++] = i--;
	
	//for(i=0;i<N;i++)
	//	fprintf(stdout,"%i,",tablaSaltos[i]);

	return tablaSaltos;
} 

int numSaltosElemento(int* tablaSaltos, int* tablaPosicionesUsadas ,int* elementos_restantes_por_comprobar, int elemento){
	if(tablaPosicionesUsadas[elemento]) //evitamos comprobar dos veces el mismo ciclo 
		return 0;

	//Calcula el numero de saltos para saliendo de un elemento, volver a él
	int puntero = elemento;	//empezamos en el elemento y saltamos "hacia atrás", contamos un salto 
	int cuenta = 1;

	tablaPosicionesUsadas[puntero]=1;
	(*elementos_restantes_por_comprobar)--;
	while((puntero=tablaSaltos[puntero])!=elemento){   //Contamos el resto de saltos, marcando los que visitamos y desontando del total.
		tablaPosicionesUsadas[puntero]=1;   
		(*elementos_restantes_por_comprobar)--;
		cuenta++;		 	     
	}

	return cuenta;
}

int contarNumSaltos(int N, int L){
	int* tablaSaltos = generarTablaSaltos(N,L); //Conseguimos la tabla de saltos
	int* tablaPosicionesUsadas = calloc(N,sizeof(int)); //almacenamos todas las posiciones por las que se pasa
	int elementos_restantes_por_comprobar = N;	    //para ahorrar en comprobar más de una vez cada ciclo


	int mejorCuenta = 1; // que calcular el mcm (-1 indica el final) valor=suma(indice^contenido[indice]);
	int cuenta;
	int i;
	for(i=0;i<N;i++){
		if(cuenta = numSaltosElemento(tablaSaltos, tablaPosicionesUsadas ,&elementos_restantes_por_comprobar, i))
			mejorCuenta = mcm(mejorCuenta,cuenta); //si cuenta es positivo (es 0 cuando el ciclo ha sido visitado) recalculamos mcm y lo guardamos en mejorCuenta

		if(!elementos_restantes_por_comprobar){ //Se ha terminado con antelación
			//fprintf(stdout,"Terminado antes: %i de %i\n",i,N);
			break;
		}/*else if(elementos_restantes_por_comprobar<0){ //Probado que no hay errores para todos los L posibles de N=1 a N=5k (~12kk ejecuciones)
			fprintf(stdout,"ERROR %i %i %i\n",N,L,i);
			exit(-1);
		}*/
	}
	
	//fprintf(stdout,"%i\n",cuenta);
	
	free(tablaSaltos);
	free(tablaPosicionesUsadas);
	return mejorCuenta;
}

int main(int argc, char* argv[]){
	int num_casos;	
	long N;
	long L;

	if (fscanf(stdin,"%d", &num_casos) == EOF)
		exit(-1);

	int i;
	for(i=1; i<= num_casos;i++){
		if (fscanf(stdin,"%li %li",&N, &L) == EOF)
			exit(-1);
		fprintf(stdout,"Case #%i: %i\n",i,contarNumSaltos(N, L));
	}
}


