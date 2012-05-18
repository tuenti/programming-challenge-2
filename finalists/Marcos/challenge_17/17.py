#!/usr/bin/python
# -*- coding: utf-8 -*-

from __future__ import division
import sys
import math

# OJO! giro debe estar en radianes
# Función para girar un punto 'punto' 'giro' radianes con respecto a un punto 'origen'
def rotacion (origen, punto, giro):
    x = punto[0]
    y = punto[1]
    a = origen[0]
    b = origen[1]
    xNueva = (x-a) * math.cos(giro) - (y-b) * math.sin(giro) + a
    yNueva = (x-a) * math.sin(giro) + (y-b) * math.cos(giro) + b
    return (xNueva, yNueva)

def obtenerPoligono (centro, vertice, nLados):
    radianesXLado = 2.0 * math.pi / nLados
    poligono = [vertice]
    for i in range(nLados-1):
        poligono.append(rotacion(centro, poligono[-1], radianesXLado))
    return poligono

# Para saber si un polígono es cortado por la recta x=0, simplemente evaluamos que todas las x sean o bien >=0 o bien =<0
# Permitiremos que el polígono sea tangente a la recta en una arista o vértice dado que no quedaría dividido en dos partes de área +
# Devolveremos -1 si queda en el lado negativo de las x, +1 si queda en el positivo y 0 si es partido por la línea
def cortaPoligono (poligono):
    v = []
    for punto in poligono:
        v.append(punto[0])
    if all(x <= 0.0 for x in v):
        return -1
    elif all(x >= 0.0 for x in v):
        return 1
    else:
        return 0


def comprobarCorte (poligonos, numTiposPoligono):
    for i in range(numTiposPoligono):
        # Analizamos los polígonos de cada tipo por separado
        v = []
        for j in range(len(poligonos[i])):
            v.append(cortaPoligono(poligonos[i][j]))
        # Si un solo polígono ha sido cortado, este corte no es válido
        if 0 in v:
            return False
        else:
            if v.count(1) != v.count(-1):
                return False
    return True


# Programa principal
# Leemos la entrada
numcasos = int(sys.stdin.readline())
for caso in range(1,numcasos+1):
    cabecera = sys.stdin.readline().split()
    centro = (float(cabecera[0]), float(cabecera[1]))
    radio = float(cabecera[2])
    numIngredientes = int(sys.stdin.readline())
    ingredientes=[]
    # Para cada ingrediente, hallamos dónde están los polígonos
    for i in range(numIngredientes):
        ingredientes.append([])
        ingrediente = sys.stdin.readline().split()
        numLados = int(ingrediente[1])
        cantidad = int(ingrediente[2])
        for j in range(cantidad):
            linea = sys.stdin.readline().split()
            centroIng = (float(linea[0]), float(linea[1]))
            vertIng = (float(linea[2]), float(linea[3]))
            ingredientes[i].append(obtenerPoligono(centroIng, vertIng, numLados))

    # Comprobamos si la pizza ya está lista para ser cortada en su posición actual
    if comprobarCorte(ingredientes, numIngredientes):
        print "Case #%d: TRUE"%caso
        continue

    # Ahora rotaremos la pizza cada 0.25 grados durante 180 grados, esto es 719 veces, ya que la 720 es la simétrica a la original
    # En cada una de estas rotaciones, comprobaremos si es posible un corte
    # ¡Y esperemos que el intervalo de submuestreo sea suficiente!
    cortada = False
    for g in range(1,720):
        # Giramos todos los puntos de los polígonos exactamente 0.25*g grados --> pi*g/720 radianes
        ingredientesGirados = []
        # Para cada tipo de ingrediente
        for i in range(numIngredientes):
            ingredientesGirados.append([])
            # Para cada ingrediente de ese tipo
            for j in range(len(ingredientes[i])):
                ingredientesGirados[i].append([])
                # Para cada punto del ingrediente
                for k in range(len(ingredientes[i][j])):
                    ingredientesGirados[i][j].append(rotacion(centro, ingredientes[i][j][k], g*math.pi/720.0))

        # Comprobamos si la pizza ya está lista para ser cortada en su posición actual
        if comprobarCorte(ingredientesGirados, numIngredientes):
            print "Case #%d: TRUE"%caso
            cortada = True
            break

    # Si hemos terminado de girar la pizza y no hemos conseguido partirla, imprimimos FALSE
    if not cortada:
        print "Case #%d: FALSE"%caso
