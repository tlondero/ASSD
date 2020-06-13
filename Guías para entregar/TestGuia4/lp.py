import numpy as np
import matplotlib.pyplot as plt
import scipy.signal as signal

def fact(n):
    p=n
    while(n!=1):
        p=p*(n-1)
        n=n-1
    return p

def io(x):
    io1=1
    oldio=0
    error = 1e-9
    k=1
    while(abs(io1-oldio)>error):
        newio = ((1/fact(k))*(x/2)**k)**2
        oldio=io1
        io1=io1+newio
        k=k+1
    return io1


def kai(N, alfa):
    wka=[]
    for n in range(int((N-1)/2)+1):
        beta= alfa*np.sqrt((1-((2*n)/(N-1))**2))
        wka.append(io(beta)  /io(alfa))
    #aca va  la misma mierda de hacer causal.
    wk=[]
    for n in range(len(wka)):
        wk.append(wka[len(wka) - 1 - n])
    for n in range(1,len(wka)):
        wk.append(wka[n])
    return wk


#Especificaciones del filtro
fs=48000
fp=3000
fa=3200
Ap=1
Aa=40
# Diseño del filtro Pasa bajos usando ventana de kaiser
#'Calculo de alfa y N'

deltaa = 10**(-0.05*Aa)
deltap = (10**(.05*Ap)-1)/(10**(.05*Ap)+1)
delta = min([deltaa, deltap])
Aa = -20*np.log10(delta)
alfa=0
D=0
if Aa<= 21:
    alfa = 0
elif Aa <= 50 :
    alfa = 0.5842*(Aa-21)**0.4+0.07886*(Aa-21)
else:
    alfa = 0.1102*(Aa-8.7)

if Aa <= 21:
    D = 0.9222
else:
    D = (Aa - 7.95) / 14.36


N=fs*D/(fa-fp)+1
N=np.ceil(N)
if(N/2-np.fix(N/2)==0):  #Fuerzo N Impar
    N=N+1
fp=fp/fs
fa=fa/fs
fc=(fp+fa)/2
h=[]

for n in range(1,int((N-1)/2+1)):
    h.append(2*fc*(np.sin(2*np.pi*fc*n)/(2*np.pi*fc*n)))
##Aca falta hacer causal la h
hf=[]
N= int(N)
for n in range(len(h)):
    hf.append(h[len(h)-1-n])
hf.append(2 * fc)
for n in range(len(h)):
    hf.append(h[n])

h=hf
##
kaiw=kai(N,alfa)
for n in range(N):
    h[n] = h[n] * kaiw[n]
F0dB = 0
Zo = np.exp(-2j*np.pi*F0dB*1/fs)
gain = abs(np.polyval(h,Zo))
for n in range(len(h)):
    h[n] = h[n]/gain


W = np.linspace(0,np.pi,3000)
a = 1
[W,H]=signal.freqz(h,a,W)
F=(W/(2*np.pi))*fs
modulo= abs(H)
fase = np.angle(H)
plt.semilogx(F,20*np.log10(modulo))
plt.grid()
plt.show()
file = open('coefLP.txt','w')
a= "h :"
for n in range(len(h)):
    a += str(h[n]) + ', '
file.write(a)
file.close()