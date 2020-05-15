import matplotlib.pyplot as plt
from scipy import fftpack
from scipy.io import wavfile
from scipy.signal import find_peaks
from scipy import signal
import numpy as np
import os

# Return  waveform samples array


def getSamples(path):
    '''
    Get note samples from .wav file
    '''

    try:
        sample_rate, samples = wavfile.read(path)
    except:
        print("The given file could not be opened")
        return
    # We only need mono, getting rid of channel 2
    try:
        channel1_samples = samples[:, 1]
    except:
        channel1_samples = samples

    return sample_rate, channel1_samples

# Get fundamental frequency


def get_f0(samples, sample_rate, time):
    '''
    Computes fundamental frequency using the fft
    Parameters
    ----------
    samples: ndarray
            Wav file samples
    time: ndarray
            auxiliary time axis computed with get_time(), see below

    Returns
    -------
    peak_freq: float,
             Greatest power frequency component
    '''
    # yf = fftpack.fft(samples, len(time))
    # amp = np.abs(yf)  # get amplitude spectrum
    # freq = fftpack.fftfreq(len(time), time[-1]/len(time))
    # freqsize = freq.size
    # yf = yf[0:freqsize//2]
    # freq = freq[0:freqsize//2]
    # return freq[np.argmax(yf)]
    f, Pxx_den = signal.periodogram(
        samples, sample_rate, nfft=1024, return_onesided=True)
    return f[np.argmax(Pxx_den)]
# Return properly spaced time axis


def get_time(samples, sample_rate):
    spec = plt.specgram(samples, NFFT=256, Fs=sample_rate, noverlap=128)
    time = np.linspace(spec[2][0], spec[2][-1], len(samples))
    return time


def get_wav_files_list(instrument):
    wav_list = []
    wav_paths = []
    curDir = os.getcwd()
    curDir = curDir+f"\{instrument}"
    all_files = os.listdir(curDir)
    for file in all_files:
        if ".wav" in file:
            wav_list.append(file)
            wav_paths.append(curDir + f"\{file}")
    return wav_paths, wav_list


def compute_pitch_marks(samples, sampling_rate, f0):
    pitch_period = np.ceil(sampling_rate/f0)  # Estimate pitch period
    pitch_marks, _ = find_peaks(samples, distance=pitch_period)
    return pitch_marks


def store_data(path, pitch_marks, f0):
    '''
    Parameters
    ----------
    path: string
        destination path
    pitch_marks.
    '''
    data = np.append(f0, pitch_marks)
    np.savetxt(path, data, delimiter=",", fmt="%d")
    pass


def take_pictures(samples, pitch_marks, path):
    '''
    Save notes and pitch_marks plot 
    '''
    plt.figure(figsize=(100, 20))
    plt.plot(samples)
    plt.plot(pitch_marks, samples[pitch_marks], 'x')
    plt.savefig(path, format='png')
    pass


if __name__ == '__main__':
    instruments = ["saxofono", "clarinete", "violin", "flautaModernB"]
    wav_paths, wav_list = get_wav_files_list("flautaModernB")
    # Name include extension mywav.wav
    # Path: indicates current working directory to store images and pitch_marks

    print(wav_paths)
    f0s = []
    for path, name in zip(wav_paths, wav_list):
        sample_rate, samples = getSamples(path)  # Read wav file
        # time = get_time(samples, sample_rate)  # Auxiliary time axis
        # Obtain note's fundamnetal frequency
        # 250.56#390.265  # int(np.ceil(get_f0(samples, sample_rate, time)))
        f0 = 531.325
        print(f'name: {name} f0: {f0} sample rate: {sample_rate}')

        # Compute pitch marks using an educated guess via peak_finder
        pitch_marks = compute_pitch_marks(samples, sample_rate, f0)
        store_data(f"{path[:-3]}csv", pitch_marks, int(f0))

        # Uncomment to store pictures /!\ WARNING LONG PROCESS AHEAD/!\
        take_pictures(samples, pitch_marks, f"{path[:-3]}png")

    print(wav_paths)
    print(wav_list)
    print("Work done")
