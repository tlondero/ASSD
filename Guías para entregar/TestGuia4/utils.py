import numpy as np
import matplotlib.pyplot as plt
import scipy.signal as signal
import math


def io(x):
    io1=1
    oldio=0
    error = 1e-9
    k=1
    while(abs(io1-oldio)>error):
        newio = ((1/math.factorial(k))*(x/2)**k)**2
        oldio=io1
        io1=io1+newio
        k=k+1
    return io1


def kai(N, alfa):
    wka=[]
    for n in range(int((N-1)/2)+1):
        beta= alfa*np.sqrt((1-((2*n)/(N-1))**2))
        wka.append(io(beta)/io(alfa))
    wk=[]
    for n in range(len(wka)):
        wk.append(wka[len(wka) - 1 - n])
    for n in range(1,len(wka)):
        wk.append(wka[n])
    return wk