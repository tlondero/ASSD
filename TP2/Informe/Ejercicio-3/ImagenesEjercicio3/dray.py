import numpy as np
import matplotlib.pyplot as plt


#BELL       RELACIÓN 2/1
norm = 5000
t = np.linspace(0, 1, norm)
tau = 0.5

Ibell = 0.5 * np.exp(-t/tau)
Abell = np.exp(-t/tau)

plt.title("$A(t)$ e $I(t)$ para la campana")
plt.xlabel("Tiempo [s]")
plt.ylabel("Amplitud")
plt.plot(t, Abell, label = "$A(t)$")
plt.plot(t, Ibell, label = "$I(t)$")
plt.legend()
plt.grid()
plt.show()

#CLARINET       RELACIÓN 3/2

tau = 0.1/3
Iclar = 2 * (1 + np.exp(-t/tau))
Aclar=[]

for i in range(len(t)):
    if (i < norm/11):
        Aclar.append(i*11/norm)
    elif ( (i > norm/11) and (i < 9*norm/11) ):
        Aclar.append(1)
    else:
        Aclar.append( 0.5 + (np.cos(np.pi*11*i/(2*norm) - 9*np.pi/2))/2)

plt.title("$A(t)$ e $I(t)$ para el clarinete")
plt.xlabel("Tiempo [s]")
plt.ylabel("Amplitud")
plt.plot(t, Aclar, label = "$A(t)$")
plt.plot(t, Iclar, label = "$I(t)$")
plt.legend()
plt.grid()
plt.show()

#TROMBON       RELACIÓN 1/1
io = 3
Itro = []
Atro=[]

for i in range(len(t)):
    if (i < norm/11):
        Itro.append(i*io*11/norm)
    elif ( (i > norm/11) and (i < 9*norm/11) ):
        Itro.append(io)
    else:
        Itro.append( io*(0.5 + (np.cos(np.pi*11*i/(2*norm) - 9*np.pi/2))/2))

for i in range(len(t)):
    if (i < norm*2/11):
        Atro.append(i*11/norm)
    elif ( (i > norm*2/11) and (i < 7*norm/22) ):
        Atro.append(i*-11/(6*norm) + 4/3)
    elif ((i > 7*norm/22) and (i < 9*norm/11)):
        Atro.append(i*(-3/(10*norm)) + 93/110 )
    else:
        Atro.append(i*(-33/(10*norm)) + 33/10 )

plt.title("$A(t)$ e $I(t)$ para el trombón")
plt.xlabel("Tiempo [s]")
plt.ylabel("Amplitud")
plt.plot(t, Atro, label = "$A(t)$")
plt.plot(t, Itro, label = "$I(t)$")
plt.legend()
plt.grid()
plt.show()

#TRUMPET       RELACIÓN 1/1
io = 10
Itru = []
Atru = []

for i in range(len(t)):
    if (i < norm*2/11):
        Itru.append(io * i * 11 / norm)
        Atru.append(i*11/norm)
    elif ( (i > norm*2/11) and (i < 7*norm/22) ):
        Itru.append(io *(i*-11/(6*norm) + 4/3))
        Atru.append(i * -11 / (6 * norm) + 4 / 3)
    elif ((i > 7*norm/22) and (i < 9*norm/11)):
        Itru.append(io *(i*(-3/(10*norm)) + 93/110 ))
        Atru.append(i * (-3 / (10 * norm)) + 93 / 110)
    else:
        Itru.append(io *(i*(-33/(10*norm)) + 33/10 ))
        Atru.append(i * (-33 / (10 * norm)) + 33 / 10)

plt.title("$A(t)$ e $I(t)$ para el trompeta")
plt.xlabel("Tiempo [s]")
plt.ylabel("Amplitud")
plt.plot(t, Atru, label = "$A(t)$")
plt.plot(t, Itru, label = "$I(t)$")
plt.legend()
plt.grid()
plt.show()