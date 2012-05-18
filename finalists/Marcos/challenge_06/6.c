#include <cstdio>
#include <cmath>
#include <cstring>

int determinarTamanyoMaximo (int *longitudes, int numPalabras, int Wct, int Hct) {

  // Determinamos el tamaño de la fuente (el máximo posible)
  // Resolveremos este problema por "fuerza bruta", ya que no es muy grande
  // (como mucho el tamaño de la fuente será 500.000)
  int tamActual = 1;
  while (true) {

    // Probamos a encajar con la fuente actual, si no encaja habrá que tomar la anterior como máxima
    // Una forma de hacerlo es ver cuántas líneas se necesitarían para encajar el mensaje,
    // deben ser menos o igual que líneas tiene la tela usando ese tamaño de letra    
    int lineasGastadas = 0;
    bool cabenPalabrasEnteras = true;
    int longitudRestante = Wct;
    // La primera palabra la ponemos aparte
    if (longitudes[0] * tamActual <= Wct) {
      ++lineasGastadas;
      longitudRestante -= longitudes[0] * tamActual;
      for (int i = 1; i < numPalabras; ++i) {
	// Vemos si cabe en la misma línea anterior
	if ((longitudes[i] + 1) * tamActual <= longitudRestante)
	  longitudRestante = longitudRestante - (longitudes[i] + 1) * tamActual;
	// O empezamos una nueva línea
	else {
	  // Vemos si la palabra cabe entera
	  // Si no, rompemos el bucle y habrá que devolver el tamaño anterior
	  if (longitudes[i] * tamActual > Wct) {
	    cabenPalabrasEnteras = false;
	    break;
	  }
	  // Si sí que cabe, lo dejamos todo preparado para la siguiente
	  else {
	    ++lineasGastadas;
	    longitudRestante = Wct - longitudes[i] * tamActual;
	  }
	}
      }
      // Una vez llegamos aquí hay 3 casos posibles:
      // Primer caso: una palabra no ha cabido entera iniciando línea
      if (!cabenPalabrasEnteras) {
	--tamActual;
	break;
      }
      // Segundo caso: se han gastado más filas que las que hay disponibles
      if (lineasGastadas * tamActual > Hct) {
	--tamActual;
	break;
      }
      // Tercer caso: todo ha cabido bien. Probamos con un tamaño de fuente superior
      ++tamActual;
    }
    else {
      // Si la primera palabra ya no cabía, tenemos que devolver el tamaño anterior
      --tamActual;
      break;
    }
  }
  
  return tamActual;
}


int calcularPulgadasHilo (int ct, int tamFuente, int numCaracteres) {

  double factor1 = 1.0/(double)ct;
  double factor2 = (double)tamFuente * (double)tamFuente / 2.0;

  return (int) ceil (factor1 * factor2 * (double)numCaracteres);

}



int main () {

  int ncasos;
  scanf ("%d", &ncasos);

  char mensaje [5500];
  for (int a = 0; a < ncasos; ++a) {
    int W, H, ct;
    scanf ("%d%d%d\n", &W, &H, &ct);
    fgets (mensaje, 5499, stdin);
    // Aquí ya hemos leído el mensaje
    
    // Tenemos que saber la longitud de cada palabra
    int longitudes[5500];
    int numPalabras = 0;
    int longitudTotal = 0;
    char *tokenActual = strtok (mensaje, " \r\n");
    longitudes[numPalabras] = strlen(tokenActual);
    longitudTotal += longitudes[numPalabras];
    ++numPalabras;
    while ((tokenActual = strtok(NULL, " \r\n")) != NULL) {
      longitudes[numPalabras] = strlen(tokenActual);
      longitudTotal += longitudes[numPalabras];
      ++numPalabras;
    }
    // Ya está :)

    int Wct = W * ct; // Anchura de la tela en "cuentas"
    int Hct = H * ct; // Altura de la tela en "cuentas"    
   
    int tamMaximo = determinarTamanyoMaximo (longitudes, numPalabras, Wct, Hct);
    // Si no ha sido posible encajar el mensaje, tamMaximo valdrá 0
    if (tamMaximo == 0)
      printf ("Case #%d: 0\n", a+1);
    else {
      int pulgadasHilo = calcularPulgadasHilo (ct, tamMaximo, longitudTotal);
      printf ("Case #%d: %d\n", a+1, pulgadasHilo);
    }

  }

  return 0;
}
