
import numpy as np
import scipy as sp
#import matplotlib as mpl
import matplotlib.pyplot as plt
t=np.linspace(0,1,1000)
senardo =np.sin(2*np.pi*t*50)

w=[]
for i in range(len(t)):
    if(i<(len(t)*0.7)):
        w.append(1)
    else:
        w.append(np.cos(np.pi*(i-0.7*len(t))/(0.3*len(t)*2)))
y=w*senardo
plt.plot(t,senardo,label="Salida sin ventana")
plt.plot(t,w,label="Ventana")
plt.plot(t,y,label="Salida con ventana")
plt.title("Continuidad del sonido")

plt.ylabel("Tension [V]")
plt.xlabel("Tiempo [s]")
plt.show()