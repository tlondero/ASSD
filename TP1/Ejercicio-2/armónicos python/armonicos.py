import matplotlib.pyplot as plt
import numpy as np
import array as arr


def an(n):
    return(12/np.pi * 1/(9-4*n**2))

def bn(n):
        return(8*(-1)**(((2*n+1)-1)/2)/(np.pi**2*(2*n+1)**2))






N=10
f0=1
t=np.arange(0,2*np.pi,0.01)
y=arr.array('f')
for i in range(int(t.size)):
    yt=0
    for n in range(N):
        yt+=an(n) * np.cos(2*np.pi * n * f0 * t[i])# 3/2 seno
        #yt += bn(n) * np.sin(2 * np.pi * (2*n+1) * f0 * t[i]) #triangular
    y.append(yt)
plt.plot(t, y ,label="Con 10 armónicos")
y2=arr.array('f')
y1=arr.array('f')
for i in range(int(t.size)):
    yt=0
    for n in range(int(3)):
        yt+=an(n) * np.cos(2*np.pi * n * f0 * t[i])# 3/2 seno
        #yt += bn(n) * np.sin(2 * np.pi * (2*n+1) * f0 * t[i]) #triangular
    y1.append(yt)
plt.plot(t, y1,label="Con 1 armónico" )
for i in range(int(t.size)):
    yt=0
    for n in range(6):
        yt+=an(n) * np.cos(2*np.pi * n * f0 * t[i])# 3/2 seno
        #yt += bn(n) * np.sin(2 * np.pi * (2*n+1) * f0 * t[i]) #triangular
    y2.append(yt)
plt.plot(t, y2,label="Con 3 armónicos" )
plt.grid()
plt.legend()
plt.xlabel('Time')
plt.ylabel('Y(t)')
plt.show()
pn=0
plt.figure()
for n in range(N):
    pn+= an(n)**2
#    pn += bn(n) ** 2
    plt.plot(n, pn ,'ro', label="Potencia del acumulada  hasta el Armónicos %d" %n)
plt.grid()
plt.legend()
plt.xlabel('Armónico')
plt.ylabel('Potencia[W]')
plt.show()
