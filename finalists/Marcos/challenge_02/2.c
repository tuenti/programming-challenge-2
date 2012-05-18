#include <cstdio>

void rellenarPotencias2Menos1 (unsigned long long int *v) {
  for (int i = 0; i < 63; ++i)
    v[i] = (1 << (i+1)) - 1;
  v[63] = 0xFFFFFFFFFFFFFFFF;
}


// Función que cuenta el número de unos de un número
int contarUnos (unsigned long long int n) {
  
  if (n == 0)
    return 0;

  int cuenta = 0;
  while (n > 1) {
    if (n % 2 == 1)
      ++cuenta;
    n/=2;
  }
  ++cuenta;
  return cuenta;
}


int main () {

  // La posición i del vector tiene (i+1) unos exactamente (menor número que lo cumple)
  unsigned long long int potencias2Menos1 [64];

  rellenarPotencias2Menos1 (potencias2Menos1);

  int ncasos;
  scanf ("%d", &ncasos);
  
  unsigned long long int numOriginal;
  for (int a = 0; a < ncasos; ++a) {
    scanf ("%lld", &numOriginal);

    // Buscamos la mayor potencia de 2 menor que el número proporcionado
    int i = 0;
    while (potencias2Menos1[i] <= numOriginal)
      ++i;
    --i;

    unsigned long long int restaNumeros = numOriginal - potencias2Menos1[i];

    int numUnos = i+1; // El número que ocupa la posición i en el vector tiene exactamente i+1 unos
    //printf ("Un sumando tiene %d unos\n", i+1);
    
    numUnos += contarUnos (restaNumeros);
    //printf ("Y el otro %d unos\n", contarUnos(restaNumeros));

    printf ("Case #%d: %d\n", a+1, numUnos);
  }

  return 0;
}
