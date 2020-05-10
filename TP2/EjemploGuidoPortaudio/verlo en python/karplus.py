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
uniform = np.random.uniform(low=0.0, high=1.0, size=50)
binary=2 * np.random.randint(0, 2, 50) - 1

input = d
print("Input: ")
print(d)
N=10000
T=1/41300
out= karplus_strong(input,20,1,N)
plt.plot(out)
plt.show()
