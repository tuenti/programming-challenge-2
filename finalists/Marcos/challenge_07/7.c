#include <cstdio>
#include <cctype>
#include <cstring>
#include <vector>

using namespace std;

// Función que convierte un entero (índice en la matriz del grafo) a la letra que representa
char int2letra (int x) {
  char cad[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  return cad[x]; 
}

int letra2int (char x) {
  if (isdigit(x))
    return (x-'0');
  else if (isupper(x))
    return (x-'A'+10);
  else
    return (x-'a'+36);
}


void todosLosOrdenesTopologicos (bool **grafo, bool *aparecido, int *gradosEntrada, int *passActual, int lPassActual, int lPassObjetivo) {

  // Caso base: imprimimos la solución
  if (lPassActual == lPassObjetivo) {
    for (int i = 0; i < lPassObjetivo; ++i)
      printf ("%c", int2letra(passActual[i]));
    printf ("\n");
    return;
  }

  // Caso general
  // Hay 62 símbolos diferentes -> iteraremos hasta 64 por seguridad
  for (int i = 0; i < 64; ++i) {
    // Si el grado de entrada es 0 y ha aparecido en la entrada
    if (gradosEntrada[i] == 0 && aparecido[i]) {

      // Introducimos el nodo en la contraseña
      passActual[lPassActual] = i;
      // Eliminamos el nodo y todos los arcos que parten de él
      aparecido[i] = false;
      vector <int> nodosAlcanzados;      
      for (int j = 0; j < 64; ++j) {
	if (grafo[i][j]) {
	  grafo[i][j] = false;
	  nodosAlcanzados.push_back (j);
	  --gradosEntrada[j];
	}
      }
      // Llamamos recursivamente para encontrar la siguiente contraseña con el grafo que queda
      todosLosOrdenesTopologicos (grafo, aparecido, gradosEntrada, passActual, lPassActual+1, lPassObjetivo);

      // Dejamos todo como estaba para poder llevar a cabo la siguiente ejecución del backtracking
      aparecido[i] = true;
      for (unsigned int j = 0; j < nodosAlcanzados.size(); ++j) {
	grafo[i][nodosAlcanzados[j]] = true;
	++gradosEntrada[nodosAlcanzados[j]];
      }
    }
  }
}

int main () {

  char codigo [100];
  // Grafo dirigido en el que a->b indicará que el símbolo a va antes que el b en la contraseña
  //bool grafo [100][100];
  bool **grafo;
  grafo = new bool* [100];
  for (int i = 0; i < 100; ++i)
    grafo[i] = new bool [100];
  for (int i = 0; i < 100; ++i)
    for (int j = 0; j < 100; ++j)
      grafo[i][j] = false;
  // Vector donde iremos guardando los grados de entrada a cada uno de los nodos
  int gradosEntrada [100];
  for (int i = 0; i < 100; ++i)
    gradosEntrada[i] = 0;
  // Vector donde guardaremos si un carácter ha aparecido hasta ahora o no
  bool aparecido [100];
  for (int i = 0; i < 100; ++i)
    aparecido[i] = false;

  // Calculamos la matriz que nos indica qué símbolos van antes/después de cuáles en la contraseña
  while (scanf ("%s", codigo) == 1) {
    int lcod = strlen(codigo);
    int codant = letra2int(codigo[0]);
    aparecido[codant] = true;
    for (int i = 1; i < lcod; ++i) {
      int codact = letra2int(codigo[i]);
      aparecido[codact] = true;
      if (!grafo[codant][codact]) {
	grafo[codant][codact] = true;
	++gradosEntrada[codact];
      }
      codant = codact;
    }
  }

  // Contamos cuántos símbolos han aparecido realmente
  int totalAparecidos = 0;
  for (int i = 0; i < 100; ++i)
    if (aparecido[i])
      ++totalAparecidos;
  
  int passActual [100];
  todosLosOrdenesTopologicos (grafo, aparecido, gradosEntrada, passActual, 0, totalAparecidos);
  
  for (int i = 0; i < 100; ++i)
    delete [] grafo[i];
  delete [] grafo;
  
  return 0;
}
