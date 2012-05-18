#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

for linea in sys.stdin:
    tokens = linea.split()
    # Inicializamos la pila --> la pila crecerá hacia el final, el último elemento insertado será el último de la lista
    pila = []
    for token in tokens:
        if token.isdigit():
            pila.append(long(token))
        elif token == ".":
            # Imprimir la cabeza de la pila
            print str(pila[-1])
        elif token == "mirror":
            # Eliminar el último elemento y cambiarle el signo
            elem = pila.pop()
            pila.append(-elem)
        elif token == "breadandfish":
            # Replicar el último elemento (cabeza)
            pila.append(pila[-1])
        elif token == "fire":
            # Quitar un elemento de la pila
            pila.pop()
        elif token == "dance":
            # Darle la vuelta a la pila
            pila.reverse()
        elif token == "conquer":
            # Quitar los dos últimos elementos de la pila y hacer el resto (segundo % primero)
            num1 = pila.pop()
            num2 = pila.pop()
            pila.append(num2 % num1)
        elif token == "$":
            # Quitar los dos últimos elementos de la pila y restarlos
            num1 = pila.pop()
            num2 = pila.pop()
            pila.append (num2 - num1)
        elif token == "&":
            # Quitar los dos úlimos elementos de la pila y dividirlos
            num1 = pila.pop()
            num2 = pila.pop()
            pila.append (num2 / num1)
        elif token == "@":
            # Quitar los dos últimos elementos de la pila y sumarlos
            num1 = pila.pop()
            num2 = pila.pop()
            pila.append (num2 + num1)
        elif token == "#":
            # Quitar los dos últimos elementos de la pila y multiplicarlos
            num1 = pila.pop()
            num2 = pila.pop()
            pila.append (num2 * num1)
            
            
        
