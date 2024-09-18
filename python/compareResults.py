import numpy as np
import subprocess
import matplotlib.pyplot as plt


## FreeFem Code
######################################################################
commandFree = ["FreeFem++", "/Users/djo/Dev/OxyFEM/FREEFEMTESTS/pb3.edp"]  

resultatFree = subprocess.run(commandFree, capture_output=True, text=True)

print(resultatFree.stdout)
######################################################################


# ## OxyFEM Code
# ######################################################################
# commandOxy = ["FreeFem++", "/Users/djo/Desktop/MEF/C++/FREEFEMTESTS/pb3.edp"]  

# resultatOxy = subprocess.run(commandOxy, capture_output=True, text=True)

# print(resultatOxy.stdout)
# ######################################################################

doss = "/Users/djo/Dev/OxyFEM/results/"


fileFree = "solPb3.txt"
fileOxy = "simu1.txt"

solFree = np.loadtxt(doss + fileFree)
solOxy = np.loadtxt(doss + fileOxy)


error = np.abs(solOxy - solFree[:,2])

relativeError = np.linalg.norm(error) / np.linalg.norm(solFree[:,2])
print("Relative error : ", np.round(relativeError, 4)*100, "%")

size = len(solFree[:,0])


# ## 1D comparaison
# ######################################################################
plt.figure(figsize=(12,8))

x = np.linspace(0, size, size)
plt.plot(x, solFree[:,2], "-or", label="Sol FreeFem", linewidth=3)
plt.plot(x, solOxy, "-bx", label="Sol Oxy", linewidth=3)
plt.plot(x, error, "--y", label="Error", linewidth=3)
plt.title("Relative error : " + str(np.round(relativeError*100,4))+"%")
plt.grid()
plt.legend()
# ######################################################################


## 2D comparaison
######################################################################
# x = solFree[:, 0].astype(int)
# y = solFree[:, 1].astype(int)
# resultFree = solFree[:, 2]
# resultFree = solOxy


# taille = np.sqrt(len(resultFree[:])).astype(int)
# U = resultFree.reshape((taille,taille))
# x = np.linspace(0, 3, taille)
# y = np.linspace(0, 3, taille)
# X, Y = np.meshgrid(x, y)


# fig = plt.figure(figsize=(10,8))
# ax = fig.add_subplot(111, projection='3d')
# ax.grid(False)
# surf = ax.plot_surface(X,Y,U, cmap='turbo', shade=True, rstride=1, cstride=1, alpha=None, antialiased=True)
# fig.colorbar(surf)
# ax.view_init(45, 0)
# plt.xlabel('X', fontsize=22)
# plt.ylabel('Y', fontsize=22)


## To Delete ?

# x_max, y_max = x.max() + 1, y.max() + 1

# # Reshape des résultats en fonction de la grille (x, y)
# grid = np.zeros((x_max, y_max))
# for i in range(len(resultFree)):
#     grid[x[i], y[i]] = resultFree[i]
#     # grid[x[i], y[i]] = np.abs(resultFree[i] - solOxy[i])

# plt.figure(figsize=(12,8))
# plt.imshow(grid, cmap='viridis', origin='lower')
# plt.colorbar(label="Sol FreeFem")
# plt.title("Solution en 2D")
# plt.xlabel("X")
# plt.ylabel("Y")

######################################################################

plt.show()