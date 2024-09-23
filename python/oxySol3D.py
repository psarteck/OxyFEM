import numpy as np
#from scipy.spatial import Delaunay
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


name = "./results/simu1.txt"
data = np.loadtxt(name)
tab = data[:].astype(float)
taille = np.sqrt(len(tab[:])).astype(int)

nameFree = "./results/solPb3.txt"
dataFree = np.loadtxt(nameFree)

x = dataFree[:,0].astype(float)
y = dataFree[:,1].astype(float)
sol = tab

# print(taille)
# x = np.linspace(0, 1, taille)
# y = np.linspace(0, 1, taille)
# X, Y = np.meshgrid(x, y)
# U = tab.reshape((taille,taille))

# print(U)

# uex = np.cos(np.pi * X) * np.cos(np.pi * Y)
# uex = np.sin(np.pi * X) * np.sin(np.pi * Y)
# errorAbs = np.linalg.norm(U - uex)
# absUex = np.linalg.norm(uex)
# relativeError = errorAbs / absUex
# txtRelErr = np.round(relativeError, 5) * 100

txtRelErr = "None"

print()
print("Python code for the comparaison data...")
print("Relative Error : ", txtRelErr)
print()

fig = plt.figure(figsize=(10,8))
ax = fig.add_subplot(111, projection='3d')
ax.grid(False)
surf = ax.plot_trisurf(x,y,sol, cmap='viridis', shade=True, alpha=None, antialiased=True)
# surf = ax.plot_surface(X,Y,U, cmap='turbo', shade=True, rstride=1, cstride=1, alpha=None, antialiased=True)
fig.colorbar(surf)
ax.view_init(45, 0)
plt.xlabel('X', fontsize=22)
plt.ylabel('Y', fontsize=22)
plt.title('Solution pour le Domaine, err =  '+str(txtRelErr)+'%', fontsize=20)
ax.view_init(90, 0)
plt.show()