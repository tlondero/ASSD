import matplotlib.pyplot as plt
import numpy as np
import array as arr


def an(n):
    return(12/np.pi * 1/(9-4*n**2))

def bn(n):
        return(8*(-1)**(((2*n+1)-1)/2)/(np.pi**2*(2*n+1)**2))






N=5
f0=1
t=np.arange(0,2*np.pi,0.01)
y=arr.array('f')
for i in range(int(t.size)):
    yt=0
    for n in range(N):
        #yt+=an(n) * np.cos(2*np.pi * n * f0 * t[i])# 3/2 seno
        yt += bn(n) * np.sin(2 * np.pi * (2*n+1) * f0 * t[i]) #triangular
    y.append(yt)
plt.plot(t, y ,label="Con 5 armónicos")
y2=arr.array('f')
y1=arr.array('f')
for i in range(int(t.size)):
    yt=0
    for n in range(int(3)):
       # yt+=an(n) * np.cos(2*np.pi * n * f0 * t[i])# 3/2 seno
        yt += bn(n) * np.sin(2 * np.pi * (2*n+1) * f0 * t[i]) #triangular
    y1.append(yt)
plt.plot(t, y1,label="Con 3 armónico" )
for i in range(int(t.size)):
    yt=0
    for n in range(1):
        #yt+=an(n) * np.cos(2*np.pi * n * f0 * t[i])# 3/2 seno
        yt += bn(n) * np.sin(2 * np.pi * (2*n+1) * f0 * t[i]) #triangular
    y2.append(yt)
plt.plot(t, y2,label="Con 1 armónicos" )
plt.grid()
plt.legend()
plt.xlabel('Time')
plt.ylabel('Y(t)')
plt.show()
pn=0
fig=plt.figure()
porc=arr.array('f')
for n in range(N):
#    pn+= an(n)**2
    pn += bn(n) ** 2
    porc.append(pn)
for n in range(N):
    porc[n]=porc[n] / porc[len(porc)-1]
    plt.plot(n, porc[n] ,'ro')
ax = fig.add_subplot(1, 1, 1)

# Major ticks every 20, minor ticks every 5
major_ticksx = np.arange(0, 6, 1)
minor_ticksx = np.arange(0, 6, 1)
major_ticksy = np.arange(0, 1, 0.05)
minor_ticksy = np.arange(0, 1, 0.05)

ax.set_xticks(major_ticksx)
ax.set_xticks(minor_ticksx, minor=True)
ax.set_yticks(major_ticksy)
ax.set_yticks(minor_ticksy, minor=True)

# And a corresponding grid
ax.grid(axis='x')

# Or if you want different settings for the grids:
ax.grid(which='minor', alpha=0.2)
ax.grid(which='major', alpha=0.5)

plt.xlabel('Armónico')
plt.ylabel('Potencia[%]')
plt.show()
