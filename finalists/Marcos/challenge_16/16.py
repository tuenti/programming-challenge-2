#!/usr/bin/python
# -*- coding: utf-8 -*-

from __future__ import division
import sys
import math

informesConocidos = int(sys.stdin.readline())
informesDesconocidos = int(sys.stdin.readline())
syscalls = int(sys.stdin.readline())

# Leemos los informes conocidos
conocidos = []
for i in range(informesConocidos):
    # Leemos cada uno de los valores y normalizamos utilizando la norma euclídea
    lineaActual = sys.stdin.readline().split()
    informeActual = [lineaActual[0]]
    for j in range(1,syscalls+1):
        informeActual.append(int(lineaActual[j]))
    norma = 0
    for j in range(1,syscalls+1):
        norma = norma + informeActual[j] ** 2
    norma = math.sqrt(norma)
    # Normalizamos
    conocidos.append([informeActual[0]])
    for j in range(1,syscalls+1):
        conocidos[i].append(informeActual[j]/norma)

# Leemos las "preguntas" o muestras a clasificar
syscallsTotales = 0
for i in range(informesDesconocidos):
    muestra = sys.stdin.readline().split()
    # Normalizamos
    muestraNormalizada = []
    muestraSinNormalizar = []
    norma = 0
    for j in range(syscalls):
        norma = norma + int(muestra[j])**2
    norma = math.sqrt(norma)
    for j in range(syscalls):
        muestraNormalizada.append(int(muestra[j])/norma)
        muestraSinNormalizar.append(int(muestra[j]))
    # Clasificamos la muestra normalizada por el vecino más cercano
    distMin = 10**200
    masCercana = -1
    for j in range(informesConocidos):
        distAct = 0
        for k in range(syscalls):
            distAct = distAct + (muestraNormalizada[k] - conocidos[j][k+1]) ** 2
        distAct = math.sqrt(distAct)
        if distAct < distMin:
            distMin = distAct
            masCercana = j
    # Una vez clasificada la muestra, vemos si es malware
    # Si es así, acumulamos el número de syscalls
    if conocidos[masCercana][0] == 'M':
        syscallsTotales = syscallsTotales + sum(muestraSinNormalizar)
        
print syscallsTotales
    
