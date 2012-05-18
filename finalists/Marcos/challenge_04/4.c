#include <cstdio>
#include <vector>

using namespace std;

struct viajeEmpezandoEnGrupo {
  
  int kartsUsados;
  int inicioSiguienteCola;

};


int main () {

  int ncasos;
  scanf ("%d", &ncasos);
  for (int a = 0; a < ncasos; ++a) {
    // R: número de carreras
    // K: número de karts
    // G: número de grupos
    int R, K, G;
    scanf ("%d%d%d", &R, &K, &G);
    vector <int> tamGrupos;
    int x;
    for (int i = 0; i < G; ++i) {
      scanf ("%d", &x);
      tamGrupos.push_back (x);
    }

    // Precalculamos para cada grupo, suponiendo que éste comienza la cola
    // dónde empezaría la siguiente y cuántos karts (i.e. litros de gasolina) se gastarían
    vector <viajeEmpezandoEnGrupo> viajesPrecalculados;
    for (int i = 0; i < G; ++i) {
      viajeEmpezandoEnGrupo viajeActual;
      // El primer caso lo hago por separado
      // Si el primer grupo no cabe entero, se han gastado 0 karts y la siguiente cola empezaría por el mismo sitio
      if (K < tamGrupos[i]) {
	viajeActual.kartsUsados = 0;
	viajeActual.inicioSiguienteCola = i;
	viajesPrecalculados.push_back (viajeActual);
	continue;
      }
      else {
	int j = (i + 1) % G;
	int usados = tamGrupos[i];
	while (j != i) {
	  if (usados + tamGrupos[j] <= K) {
	    usados += tamGrupos[j];
	    ++j;
	    if (j == G) // Es una cola circular
	      j = 0;
	  }
	  else
	    break;
	}
	viajeActual.kartsUsados = usados;
	viajeActual.inicioSiguienteCola = j; // Es donde nos hemos quedado
	viajesPrecalculados.push_back (viajeActual);
      }
    }

    // Aquí ya están todos los viajes precalculados, podemos proceder a la simulación
    int inicioColaActual = 0;
    long long int gasolinaGastada = 0;

    for (int i = 0; i < R; ++i) {
      
      gasolinaGastada += viajesPrecalculados[inicioColaActual].kartsUsados;
      inicioColaActual = viajesPrecalculados[inicioColaActual].inicioSiguienteCola;

    }

    printf ("%lld\n", gasolinaGastada);

  }

  return 0;
}
