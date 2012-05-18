#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import string

f = open ("entradaActualTest.txt")
for linea in f:
    linea = linea.strip()
    bitsTotales = []
    if (len(linea) % 7 != 0):
        print "Error!"
        continue

    for ini in range(len(linea)/7):
        # Cogemos los 7 bits
        bitsActualesCadena = linea[7*ini:7*(ini+1)]
        bitsActuales = [0] * 7
        for i in range(7):
            bitsActuales[i] = int(bitsActualesCadena[i])
        # Comprobamos la paridad
        paridad=0;
        if (bitsActuales[0] & 1 != (bitsActuales[2] + bitsActuales[4] + bitsActuales[6])  & 1):
            paridad = paridad + 1
        if (bitsActuales[1] & 1 != (bitsActuales[2] + bitsActuales[5] + bitsActuales[6]) & 1):
            paridad = paridad + 2
        if (bitsActuales[3] & 1 != (bitsActuales[4] + bitsActuales[5] + bitsActuales[6]) & 1):
            paridad = paridad + 4
            
        # Si paridad vale 0, todo está correcto
        # Si no
        if paridad != 0:
            if bitsActuales[paridad-1] == 0:
                bitsActuales[paridad-1] = 1
            else:
                bitsActuales[paridad-1] = 0

        # Una vez corregida la paridad, añadimos a la lista los bits necesarios
        bitsTotales.append(bitsActuales[2])
        bitsTotales.append(bitsActuales[4])
        bitsTotales.append(bitsActuales[5])
        bitsTotales.append(bitsActuales[6])

    # Tomamos los bits de 8 en 8 y vamos decodificando
    result=""
    if (len(bitsTotales) % 8 != 0):
        print "Error!"
        continue
    
    for i in range(len(bitsTotales)/8):
        c = bitsTotales[8*i:8*(i+1)]
        c = '0b' + str.join('', [str(b) for b in c])
        c = eval(c)
        result += chr(c)

    if all(c in string.printable for c in result):
        print result
    else:
        print "Error!"



        
