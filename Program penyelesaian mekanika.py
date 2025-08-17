import matplotlib.pyplot as plt

#inputan
x0 = int(input('masukan nilai x0(m) ='))
v0 = int(input('masukan nilai v0(m/s) ='))
a = int(input('masukan nilai a(m/s2) ='))
t = 0
tmax = 10

vtt=[]
xtt=[]
tt = []
while t <= tmax:
    vt = v0 + a*t
    xt = x0 + (v0*t) + a*(t**2)/2
    vtt.append(vt)
    xtt.append(xt)
    tt.append(t)
    print(t,vt,xt)
    t += 1

plt.subplot(2,1,1)
plt.plot(tt,vtt,color ='red',label ='posisi')
plt.xlabel('waktu(s)')
plt.ylabel('kecepatan(m/s)')
plt.title('Grafik kecepatan(m/s) terhadap waktu(v vs t)')
plt.legend()
plt.grid()

plt.subplot(2,1,2)
plt.plot(tt,xtt,color ='blue',label ='posisi')
plt.xlabel('waktu(s)')
plt.ylabel('posisi(m)')
plt.title('Grafik posisi(m) terhadap waktu(x vs t)')
plt.legend()
plt.grid()
plt.show()
    
