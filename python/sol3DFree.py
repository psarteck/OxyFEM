##  Code python pour afficher la solution calculée en 3D pour chaque problème 
##  uniquement pour un maillage triangulaire


import numpy as np
#from scipy.spatial import Delaunay
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


name = "./results/solPb3.txt"
data = np.loadtxt(name)
tab = data[:,2].astype(float)
taille = np.sqrt(len(tab[:])).astype(int)

print(taille)
U = tab.reshape((taille,taille))
x = np.linspace(0, 1, taille)
y = np.linspace(0, 1, taille)
X, Y = np.meshgrid(x, y)

print(tab)
print(U)

fig = plt.figure(figsize=(10,8))
ax = fig.add_subplot(111, projection='3d')
ax.grid(False)
surf = ax.plot_surface(X,Y,U, cmap='turbo', shade=True, rstride=1, cstride=1, alpha=None, antialiased=True)
fig.colorbar(surf)
ax.view_init(45, 0)
plt.xlabel('X', fontsize=22)
plt.ylabel('Y', fontsize=22)
plt.title('Solution pour le Domaine ', fontsize=20)
ax.view_init(90, 0)
plt.show()