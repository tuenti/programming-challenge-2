#!/usr/bin/python

import sys
import datetime

LEV = [6,2,5,5,4,5,6,3,7,6]  # LEV = Leds Encendidos Viejo (reloj viejo)

# Precalculamos dos matrices para saber la diferencia dependiendo de la hora en la que se quedo
# Las matrices se indexan por hora, minuto, segundo
relojviejo = [[[0 for k in range(60)] for j in range (60)] for i in range (24)]
relojnuevo = [[[0 for k in range(60)] for j in range (60)] for i in range (24)]

acumViejo = 0
# Rellenamos el reloj viejo
for hora in range(24):
    for minuto in range(60):
        for segundo in range(60):
            relojviejo[hora][minuto][segundo] = acumViejo + LEV[hora/10] + LEV[hora%10] + LEV[minuto/10] + LEV[minuto%10] + LEV[segundo/10] + LEV[segundo%10]
            acumViejo = relojviejo[hora][minuto][segundo]

acumNuevo = 0
# Rellenamos el reloj nuevo (lo separo en unos bucles aparte por claridad)
# Primero inicializamos un diccionario con los costes
costesNuevo = {}
costesNuevo[('0','1')] = 0
costesNuevo[('1','2')] = 4
costesNuevo[('2','3')] = 1
costesNuevo[('3','4')] = 1
costesNuevo[('4','5')] = 2
costesNuevo[('5','6')] = 1
costesNuevo[('6','7')] = 1
costesNuevo[('7','8')] = 4
costesNuevo[('8','9')] = 0
costesNuevo[('9','0')] = 1
costesNuevo[('3','0')] = 2
costesNuevo[('2','0')] = 2
costesNuevo[('5','0')] = 2
horaAnterior = "235959"
for hora in range(24):
    for minuto in range(60):
        for segundo in range(60):
            horaActual = str(hora).rjust(2,'0') + str(minuto).rjust(2,'0') + str(segundo).rjust(2,'0')
            costeCambioActual = 0
            for i in range(6): # Longitud de las horas
                if horaAnterior[i] != horaActual[i]:
                    costeCambioActual += costesNuevo[(horaAnterior[i], horaActual[i])]
            relojnuevo[hora][minuto][segundo] = acumNuevo + costeCambioActual
            acumNuevo = relojnuevo[hora][minuto][segundo]
            horaAnterior = horaActual
            

ledsDiaCompletoViejo = acumViejo
ledsDiaCompletoNuevo = acumNuevo

for line in sys.stdin:
    fechas = line.split() # Separamos las fechas
    fechaIni = fechas[0].split('-')
    horaIni = fechas[1].split(':')
    # El 2 nos lo saltamos porque es el separador
    fechaFin = fechas[3].split('-')
    horaFin = fechas[4].split(':')
    
    # Calculamos la diferencia entre los instantes de inicio y final
    instanteInicial = datetime.datetime(long(fechaIni[0]),long(fechaIni[1]),long(fechaIni[2]),long(horaIni[0]),long(horaIni[1]),long(horaIni[2]))
    instanteFinal = datetime.datetime(long(fechaFin[0]),long(fechaFin[1]),long(fechaFin[2]),long(horaFin[0]),long(horaFin[1]),long(horaFin[2]))
    diferenciaInstantes = instanteFinal - instanteInicial

    #print diferenciaInstantes

    # Sacamos la diferencia en dias, horas, minutos y segundos
    diferenciaDias = diferenciaInstantes.days
    diferenciaSegundos = diferenciaInstantes.seconds % 60
    minutosRestantes = diferenciaInstantes.seconds / 60
    diferenciaMinutos = minutosRestantes % 60
    diferenciaHoras = minutosRestantes / 60
    
    #print "Diferencia: " + str(diferenciaDias) + " dias " + str(diferenciaHoras) + " horas " + str(diferenciaMinutos) + " minutos " + str(diferenciaSegundos) + " segundos"
     
    #print "Leds del viejo: " + str (diferenciaDias * ledsDiaCompletoViejo + relojviejo[diferenciaHoras][diferenciaMinutos][diferenciaSegundos])
    #print "Coste de un dia en el viejo: " + str(ledsDiaCompletoViejo)
    #print "Coste de un dia en el nuevo: " + str(ledsDiaCompletoNuevo)
    #print "Leds del nuevo: " + str (diferenciaDias * ledsDiaCompletoNuevo + relojnuevo[diferenciaHoras][diferenciaMinutos][diferenciaSegundos] + 36 - relojnuevo[0][0][0]) # Hay que hacer este ajuste al final porque al principio se encienden todos los LEDs

    ledsTotalesRelojViejo = diferenciaDias * ledsDiaCompletoViejo + relojviejo[diferenciaHoras][diferenciaMinutos][diferenciaSegundos]
    ledsTotalesRelojNuevo = diferenciaDias * ledsDiaCompletoNuevo + relojnuevo[diferenciaHoras][diferenciaMinutos][diferenciaSegundos] + 36 - relojnuevo[0][0][0]

    print ledsTotalesRelojViejo - ledsTotalesRelojNuevo
