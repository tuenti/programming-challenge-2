#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

claves=[]
# Clave 1: código QR
claves.append("ed8ce15da9b7b5e2ee70634cc235e363")
# Clave 2: comentario en la imagen
claves.append("a541714a17804ac281e6ddda5b707952")
# Clave 3: esteganografía
claves.append("62cd275989e78ee56a81f0265a87562e")
# Elemento que se pasa por la entrada
claves.append(sys.stdin.readline().strip())

solucion=""
for j in range(32):
    suma = 0
    for i in range(4):
        elem = '0x' + str(claves[i][j])
        elem = eval(elem)
        suma += elem
    suma = suma % 16
    solucion += (str(hex(suma))[2])

print solucion
