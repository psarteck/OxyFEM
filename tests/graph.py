import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


name = "./tests/references/results.txt"
data = np.loadtxt(name)
tab = data[:].astype(float)
taille = np.sqrt(len(tab[:])).astype(int)
U = tab.reshape((taille,taille))
x = np.linspace(0, 1, taille)
y = np.linspace(0, 1, taille)
X, Y = np.meshgrid(x, y)

nameRef = "./tests/references/refNeDir.txt"
dataRef = np.loadtxt(name)
tabRef = dataRef[:].astype(float)
URef = tab.reshape((taille,taille))


uex = np.cos(np.pi * X) * np.cos(np.pi * Y)
absUex = np.linalg.norm(uex)

errorAbs = np.linalg.norm(U - URef)
absURef = np.linalg.norm(URef)
relativeError = errorAbs / absUex
txtRelErr = np.round(relativeError, 5) * 100

print("Relative Error : ", txtRelErr)

fig = plt.figure(figsize=(10,8))
ax = fig.add_subplot(111, projection='3d')
ax.grid(False)
surf = ax.plot_surface(X,Y,U, cmap='turbo', shade=True, rstride=1, cstride=1, alpha=None, antialiased=True)
fig.colorbar(surf)
ax.view_init(45, 0)
plt.xlabel('X', fontsize=22)
plt.ylabel('Y', fontsize=22)
plt.title('Solution pour le Domaine, err =  '+str(txtRelErr)+'%', fontsize=20)
ax.view_init(90, 0)

plt.savefig('tests/references/graph.png')
