import matplotlib.pyplot as plt
import numpy as np

f = np.logspace(0, 3, 1000)
H = []
arg = []
for i in range(len(f)):
    H.append(20*np.log10( 0.4 / np.sqrt(1 + 0.4**2 - 0.8 * np.cos(2*np.pi*f[i]*0.001))))
    arg.append(np.arctan((0.4*np.sin(2*np.pi*f[i]*0.001)) / (0.4*np.cos(2*np.pi*f[i]*0.001) - 1)))

plt.title("Ganancia en modulo")
plt.xlabel("$Frecuencia \ [Hz]$")
plt.ylabel("$H \ [dB]$")
plt.plot(f, H)
plt.xscale('log')
plt.grid()
plt.show()

plt.title("Ganancia en fase")
plt.xlabel("$Frecuencia \ [Hz]$")
plt.ylabel("$Fase \ [°]$")
plt.plot(f, arg)
plt.xscale('log')
plt.grid()
plt.show()