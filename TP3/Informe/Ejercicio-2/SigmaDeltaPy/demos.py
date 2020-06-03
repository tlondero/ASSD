from SigmaDelta import SigmaDelta
import numpy as np
import matplotlib.pyplot as plt
from scipy import signal
# from scipy.fft import fft


f0 = 500  # Sine wave fundamental frequency
T0 = 1/f0
fs = 2.2*f0  # Nyquist frecuency
Ts = 1/fs  # Time between samples
p = 3  # Ammount of periods to display
L = 64  # Oversampling factor
A = 0.5  # Sinewave amplitud


def bitStreamDemo():
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


def noiseShapingDemo():

    sd = SigmaDelta()
    time = np.arange(0, p*T0, Ts)
    sine1 = A*np.sin(2*np.pi*f0*time)
    L1 = 16
    L2 = 32
    L3 = 64
    L4 = 128
    L5 = 256
    L_low = 2
    L_high = 32
    # Ls = [L3]

    Ls = [L1, L2, L3, L4, L5]
    Ls2 = [L_low, L_high]
    for os_factor in Ls:
        resampled_y, resampled_t, out_binary_stream = sd.modulator(
            time, sine1, L=os_factor)

        f, Pxx = signal.periodogram(
            out_binary_stream, fs=os_factor*fs, nfft=1024)
        # plt.ylim(-10, max(np.log10(Pxx/(1e-3)))+1)
        # plt.ylim(-5, 3)
        # plt.plot(f, np.log10(Pxx/1e-3), label=f"{os_factor}")
        plt.plot(f, Pxx*1000, label=f"OS factor = {os_factor}", alpha=0.5)

    # plt.xlim(0, 20000)
    plt.title(f"Noise Shaping $f_0$: {f0} Hz")
    plt.xlabel('frequency [Hz]')
    plt.ylabel('PSD [V**2/Hz]*(10^-3)')
    plt.legend()
    plt.show()


# bitStreamDemo()
noiseShapingDemo()
