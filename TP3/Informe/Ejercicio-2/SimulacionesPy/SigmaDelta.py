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

    def modulator(self, time, inputSignal, L=1):
        """
        Parameters
        ----------
        time: np.array
              sampling times of input signal

        inputSignal: np.array
                    input analog signal
        L: int
            L=1 (default), does not alter your signal at all.
            Use only if you can't oversample beforehand.
            Otherwise use L to control oversampling.
        Returns
        -------
        resampled_y, resampled_t, out_binary_stream: np.array
                                                    oversampled signal and modulator output
        """

        # Oversample input signal
        self.oversampling_factor = L

        resampled_y, resampled_t = signal.resample(
            inputSignal, L*len(time), time)

        # Define 1-bit Digital to analog converter
        def DA(value, begin):
            if value == self._QUANTIZER_OUT:
                return 1
            elif value == -self._QUANTIZER_OUT or begin == True:
                return -1
            else:
                return -1

        def quantizer(x):
            """
            Parameters
            ----------
            x: float
                quantizer input
            If the input value to the quantizer is greater than 0 ==> output 1, else ==> output 0

            Returns
            ------
            quantized: 1-bit quantized value
            """
            quantized_value = np.int(np.sign(x))

            return quantized_value

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

        decimatedSignal = signal.decimate(
            inputSignal, decimationFactor, ftype="fir")

        return decimatedSignal
