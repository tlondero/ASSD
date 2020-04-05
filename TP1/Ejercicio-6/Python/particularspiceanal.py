from PyLTSpice.LTSpice_RawRead import LTSpiceRawRead
from mpl_toolkits.mplot3d import Axes3D
import scipy.signal
import matplotlib.pyplot as plt
import numpy as np

LTR = LTSpiceRawRead("cshsen.raw")

corr = []
corr_maxes = []
step_vars = []
least_distorted_steps = []
time = LTR.get_trace(0).get_wave(0)
vin = LTR.get_trace("V(vin)").get_wave(0)
vout = LTR.get_trace("V(vout)").get_wave(0)

pow_in = []
pow_out = []
power_restored = []

pow_in.append(0)
pow_out.append(0)
for j in range(len(time)):
    pow_in[0] =  pow_in[0] + abs(vin[j])**2
    pow_out[0] = pow_out[0] + abs(vout[j])**2

power_restored.append(pow_out[0]/pow_in[0])

print(round(power_restored[0], 6))