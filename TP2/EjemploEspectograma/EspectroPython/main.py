from scipy.io import wavfile
import matplotlib.pyplot as plt
import numpy as np
import argparse

def generatePlot(path):
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
        sample_rate, samples = wavfile.read(path);
    except:
        print("The given file could not be opened")
    #We only need mono, getting rid of channel 2
    channel1_samples = samples[:,1] 

    #Setting up our subplot
    fig, axs = plt.subplots(2, 1, sharex=True);
    axs[0].set_title("Spectogram and time domain plot");

    #Computing the spectogram in the first will allow us to use its time axes
    spec = axs[1].specgram(channel1_samples,NFFT=256,Fs=sample_rate,noverlap=128);
    axs[1].set_xlabel("time [$s$]");
    axs[1].set_ylabel("Frecuency [$Hz$]");

    #Matching Spectogram and time domain axes
    x_axis = np.linspace(spec[2][0],spec[2][-1],len(channel1_samples));
    axs[0].plot(x_axis,channel1_samples/np.max(np.abs(channel1_samples)));
    axs[0].set_ylabel("amplitude");

    #Save the image
    plt.savefig(path[:-3]+"png", format="png")

if __name__ == '__main__':
    #Create parser
    parser = argparse.ArgumentParser()
    parser.add_argument('path', type=str)
    args = parser.parse_args()
    path = args.path #<-- Get path
    generatePlot(path);
