from PyLTSpice.LTSpice_RawRead import LTSpiceRawRead
import scipy.signal
import matplotlib.pyplot as plt
import numpy as np

LTR = LTSpiceRawRead("32llave.raw")

t = LTR.get_trace(0)
vin = LTR.get_trace("V(vin)")
vout = LTR.get_trace("V(vout)")

pow_in = []
pow_out = []
power_restored = []

for i in LTR.get_steps():
    pow_in.append(0)
    pow_out.append(0)
    for j in range(len(t.get_wave(i))):
        pow_in[i] =  pow_in[i] + abs(vin.get_wave(i)[j])**2
        pow_out[i] = pow_out[i] + abs(vout.get_wave(i)[j])**2

for i in LTR.get_steps():
    power_restored.append(pow_out[i]/pow_in[i])

plt.plot(power_restored)
plt.show()