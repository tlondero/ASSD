import numpy as np
from scipy import signal
import matplotlib.pyplot as plt


class SigmaDelta:

    def __init__(self):
        self.finMax = 40e+3  # Hz
        self.winMax = 2*np.pi*self.finMax
        self.history = 0
        self.historyChannel = []

        self._DA_V_LIMIT = 1
        self._QUANTIZER_OUT = 1

    def faa(self, inputSignal):
        """
        Apply second order low pass filter

        Parameters
        ---------
        inputSignal: np.array
                     analog input signal

        """
        sos = signal.butter(2, self.winMax, btype='low',
                            analog=True, output='sos')
        filteredSignal = signal.sosfilt(sos, inputSignal)
        print(filteredSignal)
        return filteredSignal

    def modulator(self, time, inputSignal, L=10):
        """
        Parameters
        ----------
        inputSignal: np.array
                    input analog signal
        Returns
        -------
        outBitStream: np.array
                      1's and 0's modulator output
        """

        # Oversample input signal
        self.oversampling_factor = L

        resampled_y, resampled_t = signal.resample(
            inputSignal, L*len(time), time)

        # Define 1-bit Digital to analog converter
        def DA(value, begin):
            if value == 1:
                return 1
            elif value == -1 or begin == True:
                return -1
            else:
                return -1

        def quantizer(x):
            """
            If the input value to the quantizer is greater than 0 ==> output 1, else ==> output 0
            """
            return np.int(np.sign(x))

        def integrator(x, begin):
            if begin:
                return 0
            else:
                self.historyChannel.append(x)
                self.history += x
                return self.history

        def feedback(x1, x2, begin):
            if begin == True:
                return 0
            else:
                return x1-x2

        # Initialize buffers
        out_binary_stream = [-1, -1]
        begin = True
        # New output values are updated using past values

        for index, sample in enumerate(resampled_y):
            out_binary_stream.append(
                quantizer(integrator(feedback(sample, DA(out_binary_stream[index-1], begin), begin), begin)))

            begin = False

        return resampled_y, resampled_t, out_binary_stream[2:]

    def digital_filter(self, bitStream):
        """
        This method uses a LPF FIR fiter to reduces the output bandwidth and reject HF noise
        Parameters
        ----------

        Returns
        -------
        filteredSignal: np.array
                        low-pass filtered signal

        """

        pass

    def decimator(self, inputSignal, decimationFactor):
        """
        Parameters
        ----------
        inputSignal: np.array
                    input digital signal
        decimationFactor: int
                          downsampling factor = ceil(foversampling / maxFinput)

        Returns
        -------
        decimatedOut: np.array
                      downsampled signal
        """

        decimatedSignal = signal.decimate(inputSignal, decimationFactor)

        return decimatedSignal

    def plotSpectrum(self, x, y, fs):
        pass

    def plotTimeDomain(self, x, y):
        pass
