#modul
import matplotlib.pyplot as plt
import numpy as np

#variabel
x = np.arange(-3, 4, 0.01)
y = np.power(x,5)+2*np.power(x,4)-5*np.power(x,3)+7*np.power(x,2)+8*x+9

#Plot Grafik
plt.plot(x,y,
         linewidth = 1.5,
         linestyle = '--',
         color = 'magenta',
         alpha = 0.5,
         marker = '*')
plt.title('Grafik Polinomial')
plt.xlabel('x')
plt.ylabel('y')
plt.grid()
plt.show()
