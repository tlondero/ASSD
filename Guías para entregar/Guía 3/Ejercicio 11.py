import matplotlib.pyplot as plt
import numpy as np

omega = np.logspace(0, 6, 5000)

w1=3378.84*(2*np.pi)
w2=2849.16*(2*np.pi)
w3=2263.21*(2*np.pi)

ws = 60E3*(2*np.pi)

q1=3.08
q2=0.95
q3=0.54

#Filtro analógico
Ha = 1/((1j * omega - 2*np.pi*(548.51 + 1j * 3334.02))*(1j * omega - 2*np.pi*(548.51 - 1j * 3334.02))*(1j * omega - 2*np.pi*(1499.87 + 1j * 2424.12))*(1j * omega - 2*np.pi*(1499.87 - 1j * 2424.12))*(1j * omega - 2*np.pi*(2095.56 + 1j * 854.82))*(1j * omega - 2*np.pi*(2095.56 - 1j * 854.82)))
Ha = np.abs(Ha/Ha[0])

#Filtros digitales
h1=(1 + (2*ws/(w1 *q1))*(np.exp( 1j * omega/ws) - 1)/(np.exp( 1j * omega/ws) + 1) + ((2*ws/(w1))*(np.exp( 1j * omega/ws) - 1)/(np.exp( 1j * omega/ws) + 1))**2)**(-1)
h2=(1 + (2*ws/(w2 *q2))*(np.exp( 1j * omega/ws) - 1)/(np.exp( 1j * omega/ws) + 1) + ((2*ws/(w2))*(np.exp( 1j * omega/ws) - 1)/(np.exp( 1j * omega/ws) + 1))**2)**(-1)
h3=(1 + (2*ws/(w3 *q3))*(np.exp( 1j * omega/ws) - 1)/(np.exp( 1j * omega/ws) + 1) + ((2*ws/(w3))*(np.exp( 1j * omega/ws) - 1)/(np.exp( 1j * omega/ws) + 1))**2)**(-1)
H = h1*h2*h3
hi = np.abs(H)**2
hii = np.abs(2 * np.real(H))

#Primer gráfico
plt.figure(num=1, figsize=(15, 5), dpi=80, facecolor='w', edgecolor='k')
plt.title("Comparación de módulos de filtro analógico y $H_{I}$")
plt.xlabel("Frecuencia [rad/s]")
plt.ylabel("Amplitud [dB]")

plt.plot([1, 3E3*(2*np.pi)], [-0.2, -0.2], color = 'red')                           #Plantilla banda pasante
plt.plot([3E3*(2*np.pi), 3E3*(2*np.pi)], [-0.2, -550], color = 'red')
plt.fill_between([1, 3E3*(2*np.pi)], [-550, -550], facecolor='red', alpha=0.25)
plt.fill_between([1, 3E3*(2*np.pi)], [-0.2, -0.2], color = 'white', alpha = 1)


plt.plot([5.7E3*(2*np.pi), 5.7E3*(2*np.pi)], [25, -30], color = 'red')            #Plantilla banda atenueante
plt.plot([5.7E3*(2*np.pi), 10E6*(2*np.pi)], [-30, -30], color = 'red')
plt.fill_between([5.7E3*(2*np.pi), 10E6*(2*np.pi)], [25, 25], facecolor='red', alpha=0.25)
plt.fill_between([5.7E3*(2*np.pi), 10E6*(2*np.pi)], [-30, -30], facecolor='red', alpha=0.25)

plt.semilogx(omega, 20*np.log10(hi), label = "$H_I(e^{j\omega})$")
plt.semilogx(omega, 20*np.log10(Ha), label = "$H(\omega)$")
plt.legend()
plt.minorticks_on()
plt.grid(which='major')
plt.grid(which='minor')
plt.show()

#Segundo gráfico
plt.figure(num=1, figsize=(15, 5), dpi=80, facecolor='w', edgecolor='k')
plt.title("Comparación de módulos de filtro analógico y $H_{II}$")                #Plantilla banda pasante
plt.xlabel("Frecuencia [rad/s]")
plt.ylabel("Amplitud [dB]")

plt.plot([1, 3E3*(2*np.pi)], [0.2, 0.2], color = 'red')                           #Plantilla banda atenueante
plt.plot([3E3*(2*np.pi), 3E3*(2*np.pi)], [0.2, -275], color = 'red')
plt.fill_between([1, 3E3*(2*np.pi)], [-275, -275], facecolor='red', alpha=0.25)
plt.fill_between([1, 3E3*(2*np.pi)], [-0.2, -0.2], color = 'white', alpha = 1)

plt.plot([5.7E3*(2*np.pi), 5.7E3*(2*np.pi)], [25, -30], color = 'red')
plt.plot([5.7E3*(2*np.pi), 10E6*(2*np.pi)], [-30, -30], color = 'red')
plt.fill_between([5.7E3*(2*np.pi), 10E6*(2*np.pi)], [25, 25], facecolor='red', alpha=0.25)
plt.fill_between([5.7E3*(2*np.pi), 10E6*(2*np.pi)], [-30, -30], facecolor='red', alpha=0.25)

plt.semilogx(omega, 20*np.log10(hii), label = "$H_{II}(e^{j\omega})$")
plt.semilogx(omega, 20*np.log10(Ha), label = "$H(\omega)$")
plt.legend()
plt.minorticks_on()
plt.grid(which='major')
plt.grid(which='minor')
plt.show()

n = np.arange(0, 5000, 1)*2*np.pi

h1n=(1 + (2*ws/(w1 *q1))*(np.exp( 1j * n/ws) - 1)/(np.exp( 1j * n/ws) + 1) + ((2*ws/(w1))*(np.exp( 1j * n/ws) - 1)/(np.exp( 1j * n/ws) + 1))**2)**(-1)
h2n=(1 + (2*ws/(w2 *q2))*(np.exp( 1j * n/ws) - 1)/(np.exp( 1j * n/ws) + 1) + ((2*ws/(w2))*(np.exp( 1j * n/ws) - 1)/(np.exp( 1j * n/ws) + 1))**2)**(-1)
h3n=(1 + (2*ws/(w3 *q3))*(np.exp( 1j * n/ws) - 1)/(np.exp( 1j * n/ws) + 1) + ((2*ws/(w3))*(np.exp( 1j * n/ws) - 1)/(np.exp( 1j * n/ws) + 1))**2)**(-1)
Hn = h1n*h2n*h3n
hin = np.abs(Hn)**2
hiin = np.abs(2 * np.real(Hn))

X = []
for ff in n:
  if ff == 1000*2*np.pi:
    X.append(1)
  elif ff == 1206*2*np.pi:
    X.append(1)
  elif ff == 2000*2*np.pi:
    X.append(1)
  elif ff == 500*2*np.pi:
    X.append(1)
  else:
    X.append(0)

plt.figure(num=1, figsize=(15, 5), dpi=80, facecolor='w', edgecolor='k')
plt.title("Entada poliarmónica $X(f)$")                #Plantilla banda pasante
plt.xlabel("Frecuencia [rad/s]")
plt.ylabel("Amplitud")
plt.plot(n, X)
plt.show()

Yi = X*hin
plt.figure(num=1, figsize=(15, 5), dpi=80, facecolor='w', edgecolor='k')
plt.title("Salida poliarmónica $Y(f) = X(f) H_{I} (f)$")                #Plantilla banda pasante
plt.xlabel("Frecuencia [rad/s]")
plt.ylabel("Amplitud")
plt.plot(n, Yi)
plt.show()


Yii = X*hiin
plt.figure(num=1, figsize=(15, 5), dpi=80, facecolor='w', edgecolor='k')
plt.title("Salida poliarmónica $Y(f) = X(f) H_{II} (f)$")                #Plantilla banda pasante
plt.xlabel("Frecuencia [rad/s]")
plt.ylabel("Amplitud")
plt.plot(n, Yii)
plt.show()
