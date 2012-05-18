#include <iostream>
#include <cstdio>
#include <cctype>
#include <cmath>

using namespace std;

// A todos los tiempos les he quitado el 0 final (los he dividido por 10)
int Tvertical = 30;
int Thorizontal = 20;
int Tdiagonal = 35;
int Tpresionar = 10;
int Tesperar = 50;

int numPulsaciones[] = {1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,4,1,2,3,1,2,3,4};
int coordenadaXLetra[] = {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2};
int coordenadaYLetra[] = {1,1,1,2,2,2,0,0,0,1,1,1,2,2,2,0,0,0,0,1,1,1,2,2,2,2};


int tiempoDesplazamiento (int xini, int yini, int xfin, int yfin) {

  if (xini == xfin && yini == yfin)
    return 0;

  // Mientras me pueda desplazar en diagonal, siempre lo hago
  int dx, dy;
  if (xini > xfin)
    dx = xini - xfin;
  else
    dx = xfin - xini;
  if (yini > yfin)
    dy = yini - yfin;
  else
    dy = yfin - yini;
  //int dx = (int) abs ((float) xini - xfin);
  //int dy = (int) abs ((float) yini - yfin);
  int tacum = 0;
  //cout << "dx = " << dx << " dy = " << dy << endl;
  while (dx > 0 && dy > 0) {
    tacum += Tdiagonal;
    --dx;
    --dy;
  }
  // Ahora ya sólo falta vertical u horizontal
  //cout << "dx = " << dx << " dy = " << dy << endl;
  if (dx > 0)
    tacum += (dx * Tvertical);
  else
    tacum += (dy * Thorizontal);

  //cout << "FIN CALCULO\n";
  return tacum;
}


int tiempoDigito (int xact, int yact, int digito, int &xsig, int &ysig) {

  switch (digito) {
  case 0:
    xsig = 3;
    ysig = 1;
    return (tiempoDesplazamiento (xact, yact, 3, 1) + Tpresionar);
  case 1:
    xsig = ysig = 0;
    return (tiempoDesplazamiento (xact, yact, 0, 0) + 2 * Tpresionar);
  case 2:
    xsig = 0;
    ysig = 1;
    return (tiempoDesplazamiento (xact, yact, 0, 1) + 4 * Tpresionar);
  case 3:
    xsig = 0;
    ysig = 2;
    return (tiempoDesplazamiento (xact, yact, 0, 2) + 4 * Tpresionar);
  case 4:
    xsig = 1;
    ysig = 0;
    return (tiempoDesplazamiento (xact, yact, 1, 0) + 4 * Tpresionar);
  case 5:
    xsig = 1;
    ysig = 1;
    return (tiempoDesplazamiento (xact, yact, 1, 1) + 4 * Tpresionar);
  case 6:
    xsig = 1;
    ysig = 2;
    return (tiempoDesplazamiento (xact, yact, 1, 2) + 4 * Tpresionar);
  case 7:
    xsig = 2;
    ysig = 0;
    return (tiempoDesplazamiento (xact, yact, 2, 0) + 5 * Tpresionar);
  case 8:
    xsig = 2;
    ysig = 1;
    return (tiempoDesplazamiento (xact, yact, 2, 1) + 4 * Tpresionar);
  case 9:
    xsig = 2;
    ysig = 2;
    return (tiempoDesplazamiento (xact, yact, 2, 2) + 5 * Tpresionar);
  }
  return -1;
}


int main () {

  int ncasos;
  string mensaje;
  cin >> ncasos;
  getline (cin, mensaje);
  for (int a = 0; a < ncasos; ++a) {
    //string mensaje;
    getline (cin, mensaje);
    //cin >> mensaje;
    //cout << mensaje << endl;
    int lmen = mensaje.length();
    bool caps = false;
    bool primero = true;
    int xact = 3;
    int yact = 1;
    int xsig, ysig;
    int tiempo = 0;
    for (int i = 0; i < lmen; ++i) {
      if (isspace (mensaje[i])) {
	xsig = ysig = 0;
	if (xact == xsig && yact == ysig)
	  tiempo += Tesperar;
	tiempo += tiempoDesplazamiento (xact, yact, 0, 0);
	tiempo += Tpresionar; // El botón del espacio sólo se pulsa una vez
      }
      else if (isdigit (mensaje[i])) {
	tiempo += tiempoDigito (xact, yact, mensaje[i] - '0', xsig, ysig);
	if (!primero && xact == xsig && yact == ysig)
	  tiempo += Tesperar;
      }
      else {
	bool capsAct = isupper (mensaje[i]);
	if (capsAct)
	  mensaje[i] = tolower(mensaje[i]);
	if (capsAct != caps) {
	  tiempo += tiempoDesplazamiento (xact, yact, 3, 2);
	  tiempo += Tpresionar;
	  caps = !caps;
	  xact = 3;
	  yact = 2;
	}
	xsig = coordenadaXLetra [mensaje[i]-'a'];
	ysig = coordenadaYLetra [mensaje[i]-'a'];
	int np = numPulsaciones [mensaje[i]-'a'];
	tiempo += tiempoDesplazamiento (xact, yact, xsig, ysig);
	if (xact == xsig && yact == ysig)
	  tiempo += Tesperar;
	tiempo += (np * Tpresionar);
      }
      
      xact = xsig;
      yact = ysig;
      primero = false;
      //cout << tiempo << "0\n";
    }
    cout << tiempo << "0\n";
    
  }

  return 0;
}
