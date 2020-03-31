from PyLTSpice.LTSpice_RawRead import LTSpiceRawRead
from mpl_toolkits.mplot3d import Axes3D
import scipy.signal
import matplotlib.pyplot as plt
import numpy as np

#LTR = LTSpiceRawRead("..//Spice//FAA+LL+FR.raw")
LTR = LTSpiceRawRead("..//Spice//FAA+SH+FR.raw")

corr = []
corr_maxes = []
step_vars = []
least_distorted_steps = []
time = LTR.get_trace(0)
vin = LTR.get_trace("V(vin)")
vout = LTR.get_trace("V(vout)")

for i in LTR.get_steps():
    corr.append(scipy.signal.correlate(vin.get_wave(i), vout.get_wave(i), method='fft'))
    step_vars.append(LTR.steps[i])
    corr_maxes.append(np.max(corr[i]))

least_distorted_steps.append(np.where(corr_maxes == np.max(corr_maxes)))

print("Least distorted: ")

for i in range(len(least_distorted_steps)):
    print(LTR.steps[(least_distorted_steps[i][0][0])])

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
x = [(i['freqs']/1000) for i in step_vars]
y = [i['dts'] for i in step_vars]
z = [i['amp'] for i in step_vars]
c = corr_maxes
img = ax.scatter(x, y, z, c=c, cmap='CMRmap_r', alpha=1)
cbar = plt.colorbar(img)
cbar.set_label('Correlacion')
plt.title("Maxima correlacion entre entrada y salida")
ax.set_zlabel('Amplitud [V]', rotation = 0)
ax.set_ylabel('Duty Cycle [%]', rotation = 0)
ax.set_xlabel('Frecuencia [kHz]', rotation = 0)

plt.show()