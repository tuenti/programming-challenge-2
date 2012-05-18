/* Autor: José Mª Pérez Ramos
 * Fecha: 2012.04.28
 * 
 * Programa de prueba para el segundo concurso de
 * de programación de Tuenti, prueba 4
 *
 */

#include <stdlib.h>
#include <stdio.h>

void tratarCaso(){
	//Leemos datos de entrada
	long R,k,num_grupos,litros_gas = 0,grupo_actual = 0,total_personas = 0;
	if (fscanf(stdin,"%ld", &R) == EOF)
		exit(-1);

	if (fscanf(stdin,"%ld", &k) == EOF)
		exit(-1);

	if (fscanf(stdin,"%ld", &num_grupos) == EOF)
		exit(-1);

	if (num_grupos<=0)
		return;

	long * grupos = malloc(num_grupos * sizeof(long));
	int *  insertado_grupo_terminado_en = calloc(num_grupos, sizeof(int));
	long cicloEnGrupo = -1;
	for(;grupo_actual<num_grupos;grupo_actual++)
		if (fscanf(stdin,"%ld",&(grupos[grupo_actual])) == EOF)
			exit(-1);
		else
			total_personas+=grupos[grupo_actual];

	//Se van a agrupar los grupos de gente por rondas para buscar ciclos
	int maxGruposAgrupados = num_grupos;
	int indiceGruposAgrupados = 0;
	long * gruposAgrupados = malloc(maxGruposAgrupados * sizeof(long));
	int * grupoAgrupadoEmpiezaEn = malloc(maxGruposAgrupados * sizeof(int));
	
	grupo_actual = 0;
	while(1){ //Agrupamos los grupos de gente en rondas
		long subidas_esta_ronda = 0;
		grupoAgrupadoEmpiezaEn[indiceGruposAgrupados] = grupo_actual;
		while(1){ //Creamos un grupo de personas
			long quieren_subir = grupos[grupo_actual];
			if (((subidas_esta_ronda + quieren_subir) <= k) && ((subidas_esta_ronda + quieren_subir)<=total_personas)){
				subidas_esta_ronda += quieren_subir;				
				grupo_actual = (grupo_actual+1)%num_grupos;
			}else
				break;
		}
		gruposAgrupados[indiceGruposAgrupados++] = subidas_esta_ronda;
		
		if(indiceGruposAgrupados == maxGruposAgrupados){ //Guardamos el grupo
			maxGruposAgrupados*=2;
			gruposAgrupados = realloc(gruposAgrupados,maxGruposAgrupados * sizeof(long));
			grupoAgrupadoEmpiezaEn = realloc(grupoAgrupadoEmpiezaEn,maxGruposAgrupados * sizeof(int));
		}

		if (insertado_grupo_terminado_en[grupo_actual]){ //Se ha encontrado un ciclo!, guardamos el inicio del ciclo en la lista original y terminamos
			cicloEnGrupo = grupo_actual;		
			break;
		}

		if (indiceGruposAgrupados >= R) //No hemos encontrado un ciclo, pero no merece la pena buscar más, el número de rondas calculadas es inferior a las que vamos a simular
			break;

		insertado_grupo_terminado_en[grupo_actual] = 1; //Anotamos donde hemos terminado para encontrar ciclos más tarde
	}

	int indice = 0;
	int indiceCiclo = -1; //Buscamos el inicio del ciclo en la nueva lista de grupos
	for (;indice<indiceGruposAgrupados;indice++)
		if (grupoAgrupadoEmpiezaEn[indice]  == cicloEnGrupo)
			indiceCiclo = indice;


	grupo_actual = 0;
	for(;R > 0; R--){
		//Para cada carrera
		long subidos = gruposAgrupados[grupo_actual++];
		
		if (grupo_actual == indiceGruposAgrupados) //Volvemos al principio del ciclo
			grupo_actual = indiceCiclo;

		//Se suman los litros consumidos en la carrera
		litros_gas += subidos;
	}

	//Para cada carrera del día
	/*for(;R > 0; R--){
		fprintf(stdout,"Quedan %li carreras, se han consumido %li\n",R,litros_gas);
		long k_libres = k;
		long grupos_subidos = 0; //Para evitar que una persona se monte en dos coches al mismo tiempo
		//Se descuentan todos los carts que se pueden siempre que haya personas para llenarlos
		while((k_libres >= grupos[grupo_actual]) && (grupos_subidos++ < num_grupos)){
			k_libres -= grupos[grupo_actual++];
			grupo_actual %= num_grupos;
		}
		//Se suman los litros consumidos en la carrera
		litros_gas += (k-k_libres);
	}*/
	fprintf(stdout,"%li\n",litros_gas);
}

int main(int argc, char* argv[]){
	long num_casos;
	
	if (fscanf(stdin,"%ld",&num_casos) == EOF)
		exit(1);

	for(;num_casos > 0; num_casos--)
		tratarCaso();
}


