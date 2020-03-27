import matplotlib.pyplot as plt
import numpy as np
import pandas as pnd
from SpiceParser import SpiceParser
import glob
import os

simulaciones = [f for f in glob.glob("./Simu/*.*", recursive=True)]

#SIMULACION

lt_parser = SpiceParser() #Creamos el parser
a = "string1"
b = "string2"

for i in simulaciones:
    data = lt_parser.parse(i)
    time = np.array(data[1].index)*10E3 # No importa si es 1 o 2, ambos tienen el mismo
    vin = np.array(data[0]["V(vin)"]) #Tomo la magnitud
    vout = np.array(data[1]["V(vout)"]) #Tomo la fase

    if i.find('SH') > -1:
        a = "Sample and Hold"
    else:
        a = "Llave analógica"

    if i.find('Cos') > -1:
        b = " con coseno como entrada"
    elif i.find('Tri') > -1:
        b = " con triangular como entrada"
    else:
        b = " con 3/2 seno como entrada"

    plt.title(a + b)
    plt.xlabel("Tiempo [ms]")
    plt.ylabel("Tensión [V]")
    plt.plot(time, vin, label = "Entrada")
    plt.plot(time, vout, label = "Salida")
    plt.legend()
    plt.grid()
    plt.savefig('../ImagenesEjercicio6/' + i[7:-3] + 'png')
    plt.show()