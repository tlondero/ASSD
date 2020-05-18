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

h1a=np.abs((1 + (1j * omega/(q1*w1)) + (1j * omega/w1)**2 )**(-1))
h2a=np.abs((1 + (1j * omega/(q1*w2)) + (1j * omega/w2)**2 )**(-1))
h3a=np.abs((1 + (1j * omega/(q1*w3)) + (1j * omega/w3)**2 )**(-1))

Ha = h1a*h2a*h3a

h1=(1 + (2*ws/(w1 *q1))*(np.exp( 1j * omega/ws) - 1)/(np.exp( 1j * omega/ws) + 1) + ((2*ws/(w1))*(np.exp( 1j * omega/ws) - 1)/(np.exp( 1j * omega/ws) + 1))**2)**(-1)
h2=(1 + (2*ws/(w2 *q2))*(np.exp( 1j * omega/ws) - 1)/(np.exp( 1j * omega/ws) + 1) + ((2*ws/(w2))*(np.exp( 1j * omega/ws) - 1)/(np.exp( 1j * omega/ws) + 1))**2)**(-1)
h3=(1 + (2*ws/(w3 *q3))*(np.exp( 1j * omega/ws) - 1)/(np.exp( 1j * omega/ws) + 1) + ((2*ws/(w3))*(np.exp( 1j * omega/ws) - 1)/(np.exp( 1j * omega/ws) + 1))**2)**(-1)

H = h1*h2*h3

hi = np.abs(H)**2
hii = np.abs(2 * np.real(H))

#plt.title("Bode del filtro en módulo")
plt.xlabel("Frecuencia [rad/s]")
plt.ylabel("Amplitud [dB]")

plt.plot([1, 3E3*(2*np.pi)], [0.2, 0.2], color = 'red')
plt.plot([3E3*(2*np.pi), 3E3*(2*np.pi)], [0.2, -350], color = 'red')
plt.fill_between([1, 3E3*(2*np.pi)], [-350, -350], facecolor='red', alpha=0.25)

plt.plot([5.7E3*(2*np.pi), 5.7E3*(2*np.pi)], [25, -30], color = 'red')
plt.plot([5.7E3*(2*np.pi), 10E6*(2*np.pi)], [-30, -30], color = 'red')
plt.fill_between([5.7E3*(2*np.pi), 10E6*(2*np.pi)], [25, 25], facecolor='red', alpha=0.25)
plt.fill_between([5.7E3*(2*np.pi), 10E6*(2*np.pi)], [-30, -30], facecolor='red', alpha=0.25)

plt.plot(omega, 20*np.log10(hi), label = "$H_I(e^{j\omega})$")
plt.plot(omega, 20*np.log10(Ha), label = "$H(\omega)$")
plt.xscale('log')
plt.legend()
plt.grid()
plt.show()

#plt.title("Bode del filtro en módulo")
plt.xlabel("Frecuencia [rad/s]")
plt.ylabel("Amplitud [dB]")

plt.plot([1, 3E3*(2*np.pi)], [0.2, 0.2], color = 'red')
plt.plot([3E3*(2*np.pi), 3E3*(2*np.pi)], [0.2, -350], color = 'red')
plt.fill_between([1, 3E3*(2*np.pi)], [-350, -350], facecolor='red', alpha=0.25)

plt.plot([5.7E3*(2*np.pi), 5.7E3*(2*np.pi)], [25, -30], color = 'red')
plt.plot([5.7E3*(2*np.pi), 10E6*(2*np.pi)], [-30, -30], color = 'red')
plt.fill_between([5.7E3*(2*np.pi), 10E6*(2*np.pi)], [25, 25], facecolor='red', alpha=0.25)
plt.fill_between([5.7E3*(2*np.pi), 10E6*(2*np.pi)], [-30, -30], facecolor='red', alpha=0.25)

plt.plot(omega, 20*np.log10(hii), label = "$H_{II}(e^{j\omega})$")
plt.plot(omega, 20*np.log10(Ha), label = "$H(\omega)$")
plt.xscale('log')
plt.legend()
plt.grid()
plt.show()

