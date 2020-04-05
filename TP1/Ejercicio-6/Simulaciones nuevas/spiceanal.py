from PyLTSpice.LTSpice_RawRead import LTSpiceRawRead
from mpl_toolkits.mplot3d import Axes3D
import scipy.signal
import matplotlib.pyplot as plt
import numpy as np

LTR = LTSpiceRawRead("llavetriang.raw")

corr = []
corr_maxes = []
step_vars = []
least_distorted_steps = []
time = LTR.get_trace(0)
vin = LTR.get_trace("V(vin)")
vout = LTR.get_trace("V(vout)")

for i in LTR.get_steps():
    corr.append(scipy.signal.correlate(vin.get_wave(i), vout.get_wave(i)))
    step_vars.append(LTR.steps[i])
    corr_maxes.append(np.max(corr[i]))

least_distorted_steps.append(np.where(corr_maxes == np.max(corr_maxes)))
plt.show()
print("Least distorted: ")

for i in range(len(least_distorted_steps)):
    print(LTR.steps[(least_distorted_steps[i][0][0])])

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
x = [(i['freqs']/1000) for i in step_vars]
y = [i['dts'] for i in step_vars]
z = [i['amp'] for i in step_vars]
c = corr_maxes
img = ax.scatter(x, y, z, c=c, cmap='Spectral', alpha=1)
cbar = plt.colorbar(img)
cbar.set_label('Correlacion')
plt.title("Maxima correlacion entre entrada y salida")
ax.set_zlabel('Amplitud [V]', rotation = 0)
ax.set_ylabel('Duty Cycle [%]', rotation = 0)
ax.set_xlabel('Frecuencia [kHz]', rotation = 0)

plt.show()

pow_in = []
pow_out = []
power_restored = []

for i in LTR.get_steps():
    pow_in.append(0)
    pow_out.append(0)
    for j in range(len(time.get_wave(i))):
        pow_in[i] =  pow_in[i] + abs(vin.get_wave(i)[j])**2
        pow_out[i] = pow_out[i] + abs(vout.get_wave(i)[j])**2

for i in LTR.get_steps():
    power_restored.append(pow_out[i]/pow_in[i])

print(round(power_restored[least_distorted_steps[0][0][0]], 4))

plt.plot(power_restored)
plt.plot(least_distorted_steps[0][0][0], power_restored[least_distorted_steps[0][0][0]], "ro")
plt.show()

