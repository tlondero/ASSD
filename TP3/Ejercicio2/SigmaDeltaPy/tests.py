from SigmaDelta import SigmaDelta
import numpy as np
import matplotlib.pyplot as plt


def test1():
    sd = SigmaDelta()
    f = 5e+2  # Frecuencia fundamental de la senoidal de prueba
    fs = 25*f  # Frecuencia de sampleo de mi señal, con esto generamos las muestras
    # El espaciado entre las muestras es función de la frecuencia de muestreo
    time = np.arange(0, 2e-3, 1/fs)
    sine = np.sin(2*np.pi*f*time)
    # Por el momento sd.modulator devuelve la señal resampleada (con más samples) para poder plotear
    ry, rt, y = sd.modulator(time, sine, 64)
    plt.plot(rt, ry)
    # Le quitamos los primeros 2 valores porque son artificiales
    plt.plot(rt, y[2:])
    plt.show()


def test2():
    sd = SigmaDelta()
    f = 5e+2  # Frecuencia fundamental de la senoidal de prueba
    fs = 25*f  # Frecuencia de sampleo de mi señal, con esto generamos las muestras
    # El espaciado entre las muestras es función de la frecuencia de muestreo
    time = np.arange(0, 2e-3, 1/fs)
    sine = np.sin(2*np.pi*f*time)

    # Por el momento sd.modulator devuelve la señal resampleada (con más samples) para poder plotear
    ry, rt, y = sd.modulator(time, sine, 64)

    # Aca ploteamos el historial de promedios
    plt.plot(rt, ry)
    plt.plot(rt[:-1], sd.historyChannel)
    plt.show()


def test3():
    sd = SigmaDelta()
    f = 5e+2  # Frecuencia fundamental de la senoidal de prueba
    fs = 25*f  # Frecuencia de sampleo de mi señal, con esto generamos las muestras
    # El espaciado entre las muestras es función de la frecuencia de muestreo
    time = np.arange(0, 2e-3, 1/fs)
    sine = 0.5*np.sin(2*np.pi*f*time)

    # Por el momento sd.modulator devuelve la señal resampleada (con más samples) para poder plotear
    ry, rt, y = sd.modulator(time, sine, 64)

    plt.title("Test3 Amplitud 0.5")
    # Aca ploteamos el historial de promedios
    plt.plot(rt, ry)
    plt.plot(rt[:-1], sd.historyChannel)
    plt.show()


test1()
test2()
test3()
