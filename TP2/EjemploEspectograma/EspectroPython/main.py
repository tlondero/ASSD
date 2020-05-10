from scipy.io import wavfile
import matplotlib.pyplot as plt
import numpy as np
from scipy import signal
import argparse

def generatePlot(path,Nfft,overlap,window,kaiserparam,gaussianparam,expparam):
    '''
    This function computes a stacked pair of plots contaning both time domain
    and spectogram.
    An image file will be stored in that very same directory. 
        Input path: \C\folder\mywav.wav
        Ouput path: \C\folder\mywav.png

    Watch out for duplicates, we will overwrite pre-existing images with the same name.
    '''

    #Unpack .wav data
    try:
        sample_rate, samples = wavfile.read(path)
    except:
        print("The given file could not be opened")
    #We only need mono, getting rid of channel 2
    channel1_samples = samples[:,1] 

    #Setting up our subplot
    fig, axs = plt.subplots(2, 1, sharex=True)
    axs[0].set_title("Spectogram and time domain plot")

    #Computing the spectogram in the first will allow us to use its time axes
    if(window == "boxcar" or window == "triang " or window == "blackman" or window == "hamming" or window == "hanning " or window == "bartlett " or window == "flattop" or window == "parzen"or window == "bohman"or window == "blackmanharris"or window == "nuttall"or window == "barthann"):
        spec = axs[1].specgram(channel1_samples, NFFT=Nfft, Fs=sample_rate,noverlap=overlap,window= signal.get_window(window,Nfft))
    elif(window == "kaiser"):
        spec = axs[1].specgram(channel1_samples,NFFT=Nfft,Fs=sample_rate,noverlap=overlap,window= signal.windows.kaiser(Nfft,kaiserparam) )
    elif(window == "gaussian"):
        spec = axs[1].specgram(channel1_samples,NFFT=Nfft,Fs=sample_rate,noverlap=overlap,window= signal.windows.gaussian(Nfft,gaussianparam) )
    elif(window == "exponential"):
        spec = axs[1].specgram(channel1_samples,NFFT=Nfft,Fs=sample_rate,noverlap=overlap,window= signal.windows.exponential(Nfft,expparam) )
    elif(window == "rectangular"):
        spec = axs[1].specgram(channel1_samples,NFFT=Nfft,Fs=sample_rate,noverlap=overlap,window= signal.windows.tukey(Nfft,0) )

    axs[1].set_xlabel("time [$s$]")
    axs[1].set_ylabel("Frecuency [$Hz$]")

    #Matching Spectogram and time domain axes
    x_axis = np.linspace(spec[2][0],spec[2][-1],len(channel1_samples))
    axs[0].plot(x_axis,channel1_samples/np.max(np.abs(channel1_samples)))
    axs[0].set_ylabel("amplitude")

    #Save the image
    plt.savefig(path[:-3]+"png", format="png")
    plt.show()

if __name__ == '__main__':
    #Create parser
    parser = argparse.ArgumentParser()
    parser.add_argument('path', type=str)
    parser.add_argument('nfft', type=str)
    parser.add_argument('overlap', type=str)
    parser.add_argument('window', type=str)
    parser.add_argument('kaiserparam', type=str)
    parser.add_argument('gaussianparam', type=str)
    parser.add_argument('expparam', type=str)
    args = parser.parse_args()
    path = args.path #<-- Get path
    nfft=args.nfft
    overlap=args.overlap
    window=args.window
    kaiserparam=args.kaiserparam
    gaussianparam=args.gaussianparam
    expparam=args.expparam
    generatePlot(path,int(nfft),int(overlap),window,kaiserparam,gaussianparam,expparam)
#    generatePlot(path)
 #   generatePlot("twinkle.wav")