from SigmaDelta import SigmaDelta
import numpy as np
import matplotlib.pyplot as plt
from scipy import signal, ndimage


def test1():
    # PRUEBA A FULL SCALE
    sd = SigmaDelta()
    f = 5e+2  # Frecuencia fundamental de la senoidal de prueba
    fs = 25*f  # Frecuencia de sampleo de mi señal, con esto generamos las muestras
    # El espaciado entre las muestras es función de la frecuencia de muestreo
    time = np.arange(0, 2e-3, 1/fs)
    sine = 0.8*np.sin(2*np.pi*f*time)
    # Por el momento sd.modulator devuelve la señal resampleada (con más samples) para poder plotear
    ry, rt, y = sd.modulator(time, sine, 64)
    # Le quitamos los primeros 2 valores porque son artificiales
    plt.plot(rt, y[2:])
    plt.plot(rt, ry)
    plt.show()


def test2():
    # PRUEBA A FULL SCALE
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

    plt.title("Promedios Test3 Amplitud 0.5")
    # Aca ploteamos el historial de promedios
    plt.plot(rt, ry)
    plt.plot(rt[:-1], sd.historyChannel)
    plt.show()


def test4():
    # PRUEBA mitad de rango
    sd = SigmaDelta()
    f = 5e+2  # Frecuencia fundamental de la senoidal de prueba
    fs = 25*f  # Frecuencia de sampleo de mi señal, con esto generamos las muestras
    # El espaciado entre las muestras es función de la frecuencia de muestreo
    time = np.arange(0, 2e-3, 1/fs)
    sine = 0.5*np.sin(2*np.pi*f*time)
    # Por el momento sd.modulator devuelve la señal resampleada (con más samples) para poder plotear
    ry, rt, y = sd.modulator(time, sine, 64)
    plt.title("Bitstream con Amplitud 0.5")
    plt.plot(rt, ry)
    # Le quitamos los primeros 2 valores porque son artificiales
    plt.plot(rt, y[2:])
    plt.show()

# Observación del espectro a la salida


def test4():
    # PRUEBA A FULL SCALE
    sd = SigmaDelta()
    f = 5e+2  # Frecuencia fundamental de la senoidal de prueba
    fs = 25*f  # Frecuencia de sampleo de mi señal, con esto generamos las muestras
    # El espaciado entre las muestras es función de la frecuencia de muestreo
    time = np.arange(0, 4e-3, 1/fs)
    sine = 0.8*np.sin(2*np.pi*f*time)
    # Por el momento sd.modulator devuelve la señal resampleada (con más samples) para poder plotear
    ry, rt, y = sd.modulator(time, sine, 30)
    # Le quitamos los primeros 2 valores porque son artificiales
    plt.plot(rt, y[2:])
    plt.plot(rt, ry)
    N = 8
    mean_filter = np.divide(np.ones(N), N)
    filteredSignal = signal.fftconvolve(y[2:], mean_filter, mode="same")
    plt.step(rt, filteredSignal, color="black")

    plt.legend()
    plt.show()


# DE LOS MEJORES
def test5():
    # PRUEBA A FULL SCALE
    sd = SigmaDelta()
    f = 5e+2  # Frecuencia fundamental de la senoidal de prueba
    fs = 25*f  # Frecuencia de sampleo de mi señal, con esto generamos las muestras
    # El espaciado entre las muestras es función de la frecuencia de muestreo
    time = np.arange(0, 8e-3, 1/fs)
    sine = 0.8*np.sin(2*np.pi*f*time)
    # Por el momento sd.modulator devuelve la señal resampleada (con más samples) para poder plotear
    ry, rt, y = sd.modulator(time, sine, 30)
    # Le quitamos los primeros 2 valores porque son artificiales
    plt.plot(rt, y[2:])
    plt.plot(rt, ry)

    decimatedSignal = signal.decimate(y[2:], 10, ftype='fir')
    # decimatedSignal = signal.decimate(decimatedSignal, 10)
    plt.plot(np.arange(len(decimatedSignal)) /
             (75*f), decimatedSignal, label="dec")  # 75 = 25*30/10  oversampleado/decimacion
    signalDec = decimatedSignal
    N = 8  # Con 6 anda muy bien
    mean_filter = np.divide(np.ones(N), N)
    filteredSignal = signal.fftconvolve(signalDec, mean_filter, mode="same")
    plt.step(np.arange(len(filteredSignal)) /
             (75*f), filteredSignal, color="black")

    plt.legend()
    plt.title("TEST 5")
    plt.show()


def test6():
    # PRUEBA A FULL SCALE
    sd = SigmaDelta()
    f = 5e+2  # Frecuencia fundamental de la senoidal de prueba
    fs = 25*f  # Frecuencia de sampleo de mi señal, con esto generamos las muestras
    # El espaciado entre las muestras es función de la frecuencia de muestreo
    time = np.arange(0, 8e-3, 1/fs)
    sine = 0.8*np.sin(2*np.pi*f*time)
    # Por el momento sd.modulator devuelve la señal resampleada (con más samples) para poder plotear
    ry, rt, y = sd.modulator(time, sine, 30)
    # Le quitamos los primeros 2 valores porque son artificiales
    # plt.plot(rt, y[2:])
    plt.plot(rt, ry)

    N = 64
    mean_filter = np.divide(np.ones(N), N)
    filteredSignal = signal.fftconvolve(y[2:], mean_filter, mode="same")
    plt.step(rt, filteredSignal, color="black")

    decimatedSignal = signal.decimate(y[2:], 10, ftype='fir')
    # decimatedSignal = signal.decimate(decimatedSignal, 10)
    plt.plot(np.arange(len(decimatedSignal)) /
             (75*f), decimatedSignal, label="dec")  # 75 = 25*30/10  oversampleado/decimacion
    signalDec = decimatedSignal
    plt.legend()
    plt.title("TEST 6, inverted order from 5")
    plt.show()


# Espectro
def test7():
    sd = SigmaDelta()
    f = 5e+2  # Frecuencia fundamental de la senoidal de prueba
    fs = 25*f  # Frecuencia de sampleo de mi señal, con esto generamos las muestras
    # El espaciado entre las muestras es función de la frecuencia de muestreo
    time = np.arange(0, 8e-3, 1/fs)
    sine = 0.8*np.sin(2*np.pi*f*time) + np.random.randn(len(time))/100
    # Por el momento sd.modulator devuelve la señal resampleada (con más samples) para poder plotear
    ry, rt, y = sd.modulator(time, sine, 300)
    # Le quitamos los primeros 2 valores porque son artificiales
    plt.plot(rt, y[2:])
    plt.plot(rt, ry)

    plt.legend()
    plt.title("TEST 5")
    plt.show()

    f, Pxx = signal.periodogram(y[2:], fs=7500*f)

    plt.plot(f, Pxx)
    plt.show()


# test1()
# test2()
# test3()
# test4()
# test5()
# test6()
test7()
