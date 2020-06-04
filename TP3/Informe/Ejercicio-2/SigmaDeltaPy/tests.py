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
    plt.plot(rt, y)
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
    plt.plot(rt, y)
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
    filteredSignal = signal.fftconvolve(y, mean_filter, mode="same")
    plt.step(rt, filteredSignal, color="black")

    decimatedSignal = signal.decimate(y, 10, ftype='fir')
    # decimatedSignal = signal.decimate(decimatedSignal, 10)
    plt.plot(np.arange(len(decimatedSignal)) /
             (75*f), decimatedSignal, label="dec")  # 75 = 25*30/10  oversampleado/decimacion
    signalDec = decimatedSignal
    plt.legend()
    plt.title("TEST 6, inverted order from 5")
    plt.show()


# Espectro
def test7():
      # PRUEBA A FULL SCALE
    sd = SigmaDelta()
    f = 5e+2  # Frecuencia fundamental de la senoidal de prueba
    mf = 2*12.5
    fs = 25*f  # Frecuencia de sampleo de mi señal, con esto generamos las muestras
    # El espaciado entre las muestras es función de la frecuencia de muestreo
    time = np.arange(0, 8e-3, 1/fs)
    sine = 0.8*np.sin(2*np.pi*f*time)
    # Por el momento sd.modulator devuelve la señal resampleada (con más samples) para poder plotear
    M = 10
    ry, rt, y = sd.modulator(time, sine, M)
    # Le quitamos los primeros 2 valores porque son artificiales
    plt.step(rt, y, label="Hola")
    plt.plot(rt, ry)
    plt.legend()
    plt.show()
    D = 1

    scaling_factor = (mf*M)/D
    signalDec = y
    N = 64  # Con 6 anda muy bien
    mean_filter = np.divide(np.ones(N), N)
    filteredSignal = signal.fftconvolve(signalDec, mean_filter, mode="same")
    # plt.step(np.arange(len(filteredSignal)),(scaling_factor*f), filteredSignal, color="black")

    f, Pxx = signal.periodogram(y, fs=M*25*f, window="boxcar")

    plt.plot(f, 10*np.log(Pxx/1e-3))
    plt.xlim(0, (M/2)*25*500)
    plt.show()


def test8():
    # PRUEBA A FULL SCALE
    sd = SigmaDelta()
    f = 5e+2  # Frecuencia fundamental de la senoidal de prueba
    mf = 2*12.5
    fs = 25*f  # Frecuencia de sampleo de mi señal, con esto generamos las muestras
    # El espaciado entre las muestras es función de la frecuencia de muestreo
    time = np.arange(0, 8e-3, 1/fs)
    sine = 0.8*np.sin(2*np.pi*f*time)
    # Por el momento sd.modulator devuelve la señal resampleada (con más samples) para poder plotear
    M = 30
    ry, rt, y = sd.modulator(time, sine, M)
    # Le quitamos los primeros 2 valores porque son artificiales
    plt.plot(rt, y)
    plt.plot(rt, ry)
    D = 50
    decimatedSignal = signal.decimate(y[2:], D, ftype='fir')
    # decimatedSignal = signal.decimate(decimatedSignal, 10)
    scaling_factor = (mf*M)/D
    plt.step(np.arange(len(decimatedSignal)) /
             (scaling_factor*f), decimatedSignal, label="dec", color="yellow")  # 75 = 25*30/10  oversampleado/decimacion

    signalDec = decimatedSignal
    # N = 64  # Con 6 anda muy bien
    # mean_filter = np.divide(np.ones(N), N)
    # filteredSignal = signal.fftconvolve(signalDec, mean_filter, mode="same")
    # plt.step(np.arange(len(filteredSignal)) /
    #          (scaling_factor*f), filteredSignal, color="black")

    plt.legend()
    plt.title("TEST 8")
    plt.show()


def test9():
      # PRUEBA A FULL SCALE
    sd = SigmaDelta()
    f = 5e+2  # Frecuencia fundamental de la senoidal de prueba
    mf = 2*12.5
    fs = 25*f  # Frecuencia de sampleo de mi señal, con esto generamos las muestras
    # El espaciado entre las muestras es función de la frecuencia de muestreo
    time = np.arange(0, 8e-3, 1/fs)
    sine = 0.8*np.sin(2*np.pi*f*time)
    # Por el momento sd.modulator devuelve la señal resampleada (con más samples) para poder plotear
    M = 30
    ry, rt, y = sd.modulator(time, sine, M)
    # Le quitamos los primeros 2 valores porque son artificiales
    plt.plot(rt, y[2:])
    plt.plot(rt, ry)
    D = 1

    scaling_factor = (mf*M)/D
    signalDec = y
    N = 64  # Con 6 anda muy bien
    mean_filter = np.divide(np.ones(N), N)
    filteredSignal = signal.fftconvolve(signalDec, mean_filter, mode="same")
    plt.step(np.arange(len(filteredSignal)) /
             (scaling_factor*f), filteredSignal, color="black")

    # plt.legend()
    plt.title("TEST 9")
    plt.show()


def test10():
      # PRUEBA A FULL SCALE
    sd = SigmaDelta()
    f = 5e+2  # Frecuencia fundamental de la senoidal de prueba
    fn = 2*f  # Frecuencia de Nyquist
    fs = 25*f  # Frecuencia de sampleo de mi señal, con esto generamos las muestras
    # El espaciado entre las muestras es función de la frecuencia de muestreo
    time = np.arange(0, 8e-3, 1/fs)
    sine = 0.8*np.sin(2*np.pi*f*time)
    # Por el momento sd.modulator devuelve la señal resampleada (con más samples) para poder plotear
    M = 256
    ry, rt, y = sd.modulator(time, sine, int((256*2)/16))
    # Le quitamos los primeros 2 valores porque son artificiales
    plt.plot(rt, y[2:])
    plt.plot(rt, ry)
    D = 1

    scaling_factor = ((fn/fs)*M)/D
    signalDec = y
    N = 5  # Con 6 anda muy bien
    mean_filter = np.divide(np.ones(N), N)
    filteredSignal = signal.fftconvolve(signalDec, mean_filter, mode="same")
    plt.step(np.arange(len(filteredSignal)) /
             (scaling_factor*f), filteredSignal, color="black")

    # plt.legend()
    plt.title("TEST 10")
    plt.show()


# test1()
# test2()
# test3()
# test4()
# test5()
# test6()
test7()
# test8()
# test9()
# test10()
