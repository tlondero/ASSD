import matplotlib.pyplot as plt
import numpy as np

class ejercicio9():

    def __init__(self, w):
        self.n = []
        self.xn = []
        self.xn.append(1)
        for i in range(30):
            self.xn.append(w)
            self.n.append(i)
        self.n.append(30)

    def giveN(self):
        return self.n

    def giveXn(self):
        return self.xn

    def salida(self, a, b):
        yn = []
        for i in range(31):
            if i == 0:
                yn.append(0)
            if i == 1:
                yn.append(a*yn[0])
            if i == 2:
                yn.append(0.5*self.xn[0] + a*yn[1] +b*yn[0])
            elif i >= 3:
                yn.append(0.5*self.xn[i-2] + a*yn[i-1] + b*yn[i-2])

        return yn

impulso = ejercicio9(0)
escalon = ejercicio9(1)

print(impulso.giveN())
print(impulso.salida(1, -0.5))      #13 - 5

print(escalon.giveN())
print(escalon.salida(5/4, -25/32))      #12 - 4

plt.title("Respuesta al impulso")
plt.xlabel("$n$")
plt.ylabel("$y(n)$")
plt.plot(impulso.giveN(), impulso.salida(1, -0.5), '-o' , label = r'$\alpha=1$  $\beta=-\frac{1}{2}$')
plt.plot(impulso.giveN(), impulso.salida(0.5, -1/8), '-o', label = r'$\alpha=\frac{1}{2}$  $\beta=-\frac{1}{8}$')
plt.plot(impulso.giveN(), impulso.salida(5/4, -25/32), '-o', label = r'$\alpha=\frac{5}{4}$  $\beta=-\frac{25}{32}$')
plt.legend()
plt.grid()
plt.show()

plt.title("Respuesta al escalón")
plt.xlabel("$n$")
plt.ylabel("$y(n)$")
plt.plot(impulso.giveN(), escalon.salida(1, -0.5), '-o' , label = r'$\alpha=1$  $\beta=-\frac{1}{2}$')
plt.plot(impulso.giveN(), escalon.salida(0.5, -1/8), '-o', label = r'$\alpha=\frac{1}{2}$  $\beta=-\frac{1}{8}$')
plt.plot(impulso.giveN(), escalon.salida(5/4, -25/32), '-o', label = r'$\alpha=\frac{5}{4}$  $\beta=-\frac{25}{32}$')
plt.legend()
plt.grid()
plt.show()