#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys


def letrasSuficientes (candidata, letrasNuestras):
    for letra in candidata:
        if candidata.count(letra) > letrasNuestras.count(letra):
            return False
    return True


# Cargamos el diccionario de puntuaciones
puntuaciones={}
puntuaciones['A']=1
puntuaciones['B']=3
puntuaciones['C']=3
puntuaciones['D']=2
puntuaciones['E']=1
puntuaciones['F']=4
puntuaciones['G']=2
puntuaciones['H']=4
puntuaciones['I']=1
puntuaciones['J']=8
puntuaciones['K']=5
puntuaciones['L']=1
puntuaciones['M']=3
puntuaciones['N']=1
puntuaciones['O']=1
puntuaciones['P']=3
puntuaciones['Q']=10
puntuaciones['R']=1
puntuaciones['S']=1
puntuaciones['T']=1
puntuaciones['U']=1
puntuaciones['V']=4
puntuaciones['W']=4
puntuaciones['X']=8
puntuaciones['Y']=4
puntuaciones['Z']=10

# Leemos el fichero con el vocabulario
f = open("descrambler_wordlist.txt")

vocabulario={}
for linea in f:
    palabra = linea.strip()
    vocabulario[palabra] = sum([puntuaciones[letra] for letra in palabra])

f.close()

# Ahora leemos las consultas
numCasos = int(sys.stdin.readline().strip())

for caso in range(numCasos):
    info = sys.stdin.readline().split()
    letras = info[0]
    palabraIni = info[1]
    # Quitamos repetidos a la palabra que nos dan
    letrasPalabraIni = set(palabraIni)
    # Para cada letra obligatoria
    maxAct = -1
    for obligatoria in letrasPalabraIni:
        letrasActuales = letras+obligatoria
        coincidentes = [w for w in vocabulario if obligatoria in w and letrasSuficientes (w, letrasActuales)]
        # Buscamos el máximo, y en caso de empate, el lexicográficamente menor
        for palabra in coincidentes:
            if vocabulario[palabra] > maxAct or (vocabulario[palabra] == maxAct and palabra < mejorPalabra):
                mejorPalabra = palabra
                maxAct = vocabulario[palabra]
    print mejorPalabra + " " + str(maxAct)
    
