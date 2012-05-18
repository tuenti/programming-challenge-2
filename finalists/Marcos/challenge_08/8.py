#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import hashlib

# Primero leemos la cadena original
cadVieja = sys.stdin.readline()
cadVieja = cadVieja.strip()  #Para quitarle el salto de línea

# Ahora vamos leyendo las transformaciones
gramaticaFinal = {}
for linea in sys.stdin:
    linea = linea.strip()
    transformaciones = linea.split(',')
    gramaticaActual = {}
    for t in transformaciones:
        regla = t.split ("=>")
        gramaticaActual[regla[0]] = str(regla[1])
    
    # Aplicamos las reglas nuevas a las partes derechas de las reglas ya existentes
    for regla in gramaticaFinal:
        parteDerechaNueva = ""
        parteDerechaVieja = gramaticaFinal[regla]
        for i in range(len(parteDerechaVieja)):
            if parteDerechaVieja[i] in gramaticaActual:
                parteDerechaNueva += gramaticaActual[parteDerechaVieja[i]]
            else:
                parteDerechaNueva += parteDerechaVieja[i]
        gramaticaFinal[regla] = parteDerechaNueva

    # Si algún no terminal en el lado derecho no existía antes y ahora ha aparecido una regla que lo emplea, lo añadimos
    for regla in gramaticaActual:
        if regla not in gramaticaFinal:
            gramaticaFinal[regla] = gramaticaActual[regla]
    
# Ya hemos leído las transformaciones, y las hemos compuesto, ahora simplemente lo aplicamos a la cadena inicial
m = hashlib.md5()
cadNueva = ""
for i in range(len(cadVieja)):
    if cadVieja[i] in gramaticaFinal:
        m.update(gramaticaFinal[cadVieja[i]])
    else:
        m.update(cadVieja[i])
        
print m.hexdigest()
