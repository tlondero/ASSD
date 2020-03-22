amp=1; 
fs=300000;  
freq=1500;
period=1/freq;
values=0:1/fs:period;
a=amp*sin(2*pi*3/2*freq*values);
plot(a);
audiowrite('sen32.wav',a,fs)

