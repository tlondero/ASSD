from SigmaDelta import SigmaDelta
import numpy as np
import matplotlib.pyplot as plt
from scipy import signal
# from scipy.fft import fft


def bitStreamDemo():
    f0 = 500  # Sine wave fundamental frequency
    T0 = 1/f0
    fs = 5*f0  # Nyquist frecuency
    Ts = 1/fs  # Time between samples
    p = 3  # Ammount of periods to display
    L = 64  # Oversampling factor
    A = 0.5  # Sinewave amplitud

    sd = SigmaDelta()

    time = np.arange(0, p*T0, Ts)

    sine1 = A*np.sin(2*np.pi*f0*time)

    resampled_y, resampled_t, out_binary_stream = sd.modulator(
        time, sine1, L=L)

    plt.step(resampled_t, out_binary_stream, label="bit-stream")
    plt.plot(resampled_t, resampled_y,
             label="Oversampled Input signal", color="black")

    plt.title(f"Salida del modulador OS factor L: {L}")
    plt.xlabel("tiempo [segs]")
    plt.ylabel("amplitud [V]")
    plt.legend(loc="upper right")

    plt.show()


def noiseShapingDemo1(scale="linear"):
    """
    Parameters
    ----------
    scale: str
            type of yaxis scale, {"linear","dbm"}s
            for close up looks of noise shapping effects dbm scale is prefered
    """

    f0 = 500  # Sine wave fundamental frequency
    T0 = 1/f0
    fs = 2.2*f0  # Nyquist frecuency
    Ts = 1/fs  # Time between samples
    p = 3  # Ammount of periods to display
    L = 256  # Oversampling factor
    A = 0.5  # Sinewave amplitud

    if scale != "linear" and scale != "dbm":
        print("""Scale :{scale} is not supported
                Please use "linear" or "dbm" """)
    sd = SigmaDelta()
    time = np.arange(0, p*T0, Ts)
    sine1 = 0.5*np.sin(2*np.pi*f0*time)
    L1 = 16
    L2 = 32
    L3 = 64
    L4 = 128
    L5 = 256

    Ls = [L1, L2, L3, L4, L5]
    for os_factor in Ls:
        resampled_y, resampled_t, out_binary_stream = sd.modulator(
            time, sine1, L=os_factor)

        f, Pxx = signal.periodogram(
            out_binary_stream, fs=os_factor*fs, nfft=1024)
        if scale == "dbm":
            plt.plot(f, np.log10(Pxx/1e-3),
                     label=f"OS factor = {os_factor}")
        elif scale == "linear":
            plt.plot(f, Pxx*1000,
                     label=f"OS factor = {os_factor}")
            plt.xlim(0, 15000)
            plt.hlines(1.4, 0, 1000, linestyle="--")
            plt.vlines(1000, 1.4, 0, linestyle="--")

    plt.title(f"Noise Shaping $f_0$: {f0} Hz")
    plt.xlabel('frequency [Hz]')
    if scale == "dbm":
        plt.ylabel('PSD dbm')
    elif scale == "linear":
        plt.ylabel('PSD $\\frac{V^2}{Hz}\\cdot 10^{-3}$')

    plt.legend()
    plt.show()


def noiseShapingDemo2(scale="dbm"):
    """
    Parameters
    ----------
    scale: str
            type of yaxis scale, {"linear","dbm"}s
            for close up looks of noise shapping effects dbm scale is prefered
    """

    f0 = 500  # Sine wave fundamental frequency
    T0 = 1/f0
    fs = 2.2*f0  # Nyquist frecuency with some guard
    Ts = 1/fs  # Time between samples
    p = 3  # Ammount of periods to display
    A = 0.5  # Sinewave amplitud

    if scale != "linear" and scale != "dbm":
        print("""Scale :{scale} is not supported
                Please use "linear" or "dbm" """)

    sd = SigmaDelta()
    time = np.arange(0, p*T0, Ts)
    sine1 = 0.5*np.sin(2*np.pi*f0*time)
    L1 = 16
    L2 = 32
    L3 = 64
    L4 = 128
    L5 = 256

    Ls = [L5]
    for os_factor in Ls:
        resampled_y, resampled_t, out_binary_stream = sd.modulator(
            time, sine1, L=os_factor)

        f, Pxx = signal.periodogram(
            out_binary_stream, fs=os_factor*fs, nfft=1024, window="boxcar")

        if scale == "dbm":
            plt.plot(f, np.log10(Pxx/1e-3),
                     label=f"OS factor = {os_factor}")
            plt.xlim(0, 27000)
            plt.ylim(-5, 0)

        elif scale == "linear":
            plt.plot(f, Pxx*1000,
                     label=f"OS factor = {os_factor}")
            plt.xlim(0, 15000)
            plt.hlines(1.4, 0, 1000, linestyle="--")
            plt.vlines(1000, 1.4, 0, linestyle="--")

    plt.title(f"Noise Shaping $f_0$: {f0} Hz")
    plt.xlabel('frequency [Hz]')
    if scale == "dbm":
        plt.ylabel('PSD dbm')
    elif scale == "linear":
        plt.ylabel('PSD $\\frac{V^2}{Hz}\\cdot 10^{-3}$')

    plt.legend()
    plt.show()


def quantizationNoiseShapingDemo():

    f0 = 500  # Sine wave fundamental frequency
    T0 = 1/f0
    fs = 2.2*f0  # Nyquist frecuency
    Ts = 1/fs  # Time between samples
    p = 1

    sd = SigmaDelta()

    # L1 = 16
    # L2 = 32
    # L3 = 64
    # L4 = 128
    L5 = 256

    time = np.arange(0, p*T0, Ts)
    zeros = np.zeros_like(time)

    # Ls = [L1, L2, L3, L4, L5]
    Ls = [L5]
    for os_factor in Ls:
        resampled_y, resampled_t, out_binary_stream = sd.modulator(
            time, zeros, L=os_factor)
        # out_binary_stream = np.array(out_binary_stream, dtype=np.int) == 1
        plt.title("Modulator response to Zero input")
        plt.step(resampled_t, out_binary_stream)
        plt.show()

        f, Pxx = signal.periodogram(
            out_binary_stream, fs=os_factor*fs, nfft=1024)

        plt.plot(f, np.log10(Pxx/1e-3),
                 label=f"OS factor = {os_factor}")
        plt.xlim(0, 29090)
        plt.ylim(-5.3, 0.3)

    plt.title(f"Quantization Noise Shaping with no input")
    plt.xlabel('frequency [Hz]')
    plt.ylabel('PSD dbM')
    plt.legend()
    plt.show()


def fullDemo():
    f0 = 500
    fn = 2*500
    T0 = 1/500
    K = 128
    # Sampleamos nuestra señal 64 veces por encima de la frecuencia de Nyquist, es decir
    # a unos 64Khz
    time = np.arange(0, 4*T0, 1/(fn*K))
    sineDemo = 0.5*np.sin(2*np.pi*time*f0)

    sigma_delta_ADC = SigmaDelta()

    # Podemos simular una operación de sobremuestreo para expandir nuestra base de muestras
    # pero en este caso no lo haremos
    resampled_y, resampled_t, out_binary_stream = sigma_delta_ADC.modulator(
        time, sineDemo, L=10)

    plt.xlabel("time [seg]")
    plt.ylabel("amplitude [V]")

    plt.step(resampled_t, out_binary_stream)
    plt.plot(time, sineDemo, label=f"original waveform f0: {f0} Hz")
    plt.show()


# bitStreamDemo()
# noiseShapingDemo1("linear")
# noiseShapingDemo2("dbm")
quantizationNoiseShapingDemo()
# fullDemo()
