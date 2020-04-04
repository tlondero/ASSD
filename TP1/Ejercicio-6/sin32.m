amp=5; 
fs=2000000;
freq=15750;
period=1/freq;
values=0:1/fs:period;
a=amp*sin(2*pi*3/2*freq*values);

for i=1:1:5
   a = [a amp*sin(2*pi*3/2*freq*values - i*period)]; 
end

plot(a)
%create_pwl(a, fs, 'sin32corta.pwl');