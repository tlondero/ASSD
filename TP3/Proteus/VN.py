import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
#df = pd.read_csv('datacsv.dat')
df = pd.read_csv('datacsv2.dat')
t = np.asarray(df['TIME'])
Vrampa = np.asarray(df['Vrampa'])
Vrampaq = np.asarray(df['Vrampaq'])
delta =0.0001458602481- 8.46360221e-005
plt.plot(t,Vrampa)
plt.plot(t,Vrampaq)
dif=[]
Var=np.var(Vrampa-Vrampaq)
print(Var)
plt.show()
