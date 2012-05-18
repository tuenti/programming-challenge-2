#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

# Primero creamos un diccionario para indexar todas las palabras de los ficheros
diccionario = {}
for i in range(1,801):

    #  Utilizaremos un diccionario local al fichero
    dicActual = {}
    nomFich = "/home/mcalvo/Descargas/documents/0" + str(i).rjust(3,'0')
    f = open(nomFich)
    
    for linea in f:
        palabras = linea.lower().split()
        for w in palabras:
            dicActual[w] = dicActual.get(w,0) + 1

    f.close()

    # Ahora combinamos el diccionario actual con el que hubiera antes
    for w in dicActual:
        diccionario.setdefault(w,[]).append((dicActual[w],i))
        #if w in diccionario:
        #    diccionario[w].append((dicActual[w],i))
        #else:
        #    diccionario[w]=[(dicActual[w],i)]

    
# Aquí ya hemos indexado toda la información que necesitamos, procedemos a leer la entrada
numCasos = int(sys.stdin.readline().strip())

for caso in range(numCasos):
    linea = sys.stdin.readline()
    datos = linea.split()
    palabra = datos[0].lower()
    numApariciones = long(datos[1])
    
    # Buscamos en qué fichero se encuentra la aparición que buscamos
    acum = 0
    
    i = 0
    while acum < numApariciones:
        acum = acum + diccionario[palabra][i][0]
        i = i+1

    # Cuando ya sabemos en qué fichero está, lo preparamos todo para la "búsqueda fina"
    i = i-1
    acum -= diccionario[palabra][i][0]
    indiceFich = diccionario[palabra][i][1]
    faltantes = numApariciones - acum

    # Abrimos el fichero y hacemos una "búsqueda fina"
    nomFich = "/home/mcalvo/Descargas/documents/0" + str(indiceFich).rjust(3,'0')
    f = open(nomFich)
    
    encontrada = False
    for numLinea, linea in enumerate(f):
        palabras = linea.strip().split()
        for pos in range(len(palabras)):
            if palabras[pos].lower() == palabra:
                faltantes = faltantes - 1
                if faltantes == 0:
                    print str(indiceFich) + "-" + str(numLinea+1) + "-" + str(pos+1)
                    encontrada = True
                    break
        if encontrada:
            break
    f.close()
                    

        
