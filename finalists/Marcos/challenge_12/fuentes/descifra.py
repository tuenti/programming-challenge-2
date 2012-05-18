#!/usr/bin/python
# -*- coding: utf-8 -*-

import Image
import sys

ruta = sys.argv[1]
imagen = Image.open(ruta)
matriz = imagen.load()
columnas,filas = imagen.size

binarios = []
for j in range(filas):
    for i in range(columnas):
            pixel = list(matriz[i, j])
            for k in range(3):
                binarios.append(pixel[k] % 2)
            
result = ''
x = 0
for i in range(32):
    c = binarios[x:x+8]
    x = x + 8
    c = '0b' + str.join('', [str(b) for b in c])
    c = eval(c)
    result += chr(c)

print (result)


