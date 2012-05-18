#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import fractions

def construirPermutacion (N, T):
    inicial = range(N)
    permutacion = [0]*N
    monton1 = inicial[:T]
    monton2 = inicial[T:]
    aux = []
    for i in range(min(T, N-T)):
        aux.append(monton1.pop())
        aux.append(monton2.pop())
    monton1.reverse()
    monton2.reverse()
    aux += monton1
    aux += monton2
    for i in range(N):
        permutacion[aux[i]] = i
    return permutacion
    

ncasos = int(sys.stdin.readline())

for caso in range(1,ncasos+1):
    datos = sys.stdin.readline().split()
    numCartas = int(datos[0])
    tamParticion = int(datos[1])
    
    # Construímos el vector permutación
    visitados = [False] * numCartas
    perm = construirPermutacion (numCartas, tamParticion)

    # Buscamos los ciclos
    lciclos = []
    for i in range(numCartas):
        if not visitados[i]:
            p = i
            inicio = True
            lcicloact = 0
            while p != i or inicio:
                inicio = False
                visitados[p] = True
                p = perm[p]
                lcicloact = lcicloact + 1
            lciclos.append(lcicloact)

    # Ahora hacemos el mínimo común múltiplo de todas las longitudes de ciclo
    mcm = lciclos[0]
    for i in range(1, len(lciclos)):
        mcm = mcm * lciclos[i] / fractions.gcd(mcm, lciclos[i])
        
    print "Case #%d: %d"%(caso, mcm)
