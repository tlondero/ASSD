import numpy as np
import scipy as sp
#import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.pylab as pyl
import scipy.io.wavfile
from scipy import signal
import scipy.fftpack


def karplus_strong(input, L,rf,N):
    out=[input[0]/2]

    for i in range(1,N):
        if(i< len(input)):
            if(i<L):
                out.append(input[i]/2+input[i-1]/2)
            elif(i==L):
              out.append(input[i]/2 + out[i-L]/2+input[i-1]/2)
            else:
              out.append(input[i] / 2 + out[i - L] / 2 + input[i - 1] / 2+out[i-L-1]/2)
        else:
            out.append( out[i - L] / 2  + out[i - L - 1] / 2)
    return out


d=np.zeros(50)
d[0]=1
print("Input: ")
print(d)
N=10000
T=1/41300
out= karplus_strong(d,20,1,N)
print("Output:")
print(out)
yf = scipy.fftpack.fft(out)
xf = np.linspace(0.0, 1.0/(2.0*T),int(N/2))
yfin = scipy.fftpack.fft(d)
xfin = np.linspace(0.0, 1.0/(2.0*T),int(50/2))
plt.plot(out)
plt.plot(d)
plt.show()
fig, ax = plt.subplots()
ax.plot(xf, 2.0/N * np.abs(yf[:N//2]))
ax.plot(xfin, 2.0/50 * np.abs(yfin[:50//2]))
plt.show()
