#include <cstdio>

int main () {

  // Leemos el primer número, que es el que lo inicializa todo
  int precioActual;
  scanf ("%d", &precioActual);

  //int mejorPrecioCompra = precioActual;
  int precioCompraActual = precioActual;

  //int mejorPrecioVenta = -1;
  int precioVentaActual = -1;

  int instanteCompraActual = 0;
  int mejorInstanteCompra = 0;

  int mejorInstanteVenta = -1;
  int instanteVentaActual = -1;

  int mejorBeneficio = -1;
  int beneficioActual = -1;
 

  int instanteActual = 0;
  while (scanf ("%d", &precioActual) == 1) {
    ++instanteActual;
    if (precioActual < precioCompraActual) {
      // Guardamos los datos de la mejor transacción hasta el momento si supera lo que había
      if (mejorBeneficio < beneficioActual) {
	mejorBeneficio = beneficioActual;
	mejorInstanteCompra = instanteCompraActual;
	mejorInstanteVenta = instanteVentaActual;
      }
      // Actualizamos el instante y el precio de compra
      instanteCompraActual = instanteActual;
      precioCompraActual = precioActual;
      beneficioActual = -1; // Porque todos los instantes de venta serán futuros
      precioVentaActual = -1; // Mismo motivo
    }
    if (precioActual > precioVentaActual) {
      // Guardamos los datos de la mejor transacción hasta el momento si supera lo que había
      if (mejorBeneficio < beneficioActual) {
	mejorBeneficio = beneficioActual;
	mejorInstanteCompra = instanteCompraActual;
	mejorInstanteVenta = instanteVentaActual;
      }
      // Actualizamos el instante de venta
      instanteVentaActual = instanteActual;
      precioVentaActual = precioActual;
      beneficioActual = precioVentaActual - precioCompraActual;
    }
  }

  // Tras leer la última línea, tenemos que comprobar si ésta forma parte del mejor beneficio
  if (mejorBeneficio < beneficioActual) {
      mejorBeneficio = beneficioActual;
      mejorInstanteCompra = instanteCompraActual;
      mejorInstanteVenta = instanteVentaActual;
  }
  
  printf ("%d00 %d00 %d\n", mejorInstanteCompra, mejorInstanteVenta, mejorBeneficio);

  return 0;
}
