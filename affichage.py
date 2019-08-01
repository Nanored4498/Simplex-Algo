#!/usr/bin/env python3

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as pl
from math import log
import numpy as np

fig = pl.figure()
ax = fig.add_subplot(111, projection='3d')

# Make data
f = open("perf.txt", 'r')
x, y, z = [], [], []
xx, yy, zz = [], [], []
ex = [(1000, 1000, 1000), (-1, 1000, 1000), (-1, -1, -1000), (1000, -1, 1000)]
cs = [(-1, -1, -1), (1, -1, -1), (1, 1, 1), (-1, 1, -1)]
mi_n, ma_n, mi_m, ma_m = 1000, -1, 1000, -1
for l in f:
	n, m, _, t = l.split()
	n, m, t = int(n), int(m), log(float(t))
	x.append(n)
	y.append(m)
	z.append(t)
	for i in range(4):
		if 2 * cs[i][0] * (n - ex[i][0]) + cs[i][1] * (m - ex[i][1]) + 20 * cs[i][2] * (t - ex[i][2]) > 0:
			ex[i] = (n, m, t)
	mi_n, ma_n, mi_m, ma_m = min(n, mi_n), max(n, ma_n), min(m, mi_m), max(m, ma_m)

# Plot the surface
ax.scatter(x, y, z)

co = [[], [], []]
ex = ex[:3] + [ex[0], ex[3], ex[2]]
for i in range(6):
	p = ex[i]
	for j in range(3):
		co[j].append(p[j])
pl.plot(co[0], co[1], co[2], color='red')
pl.plot(co[0], co[1], co[2], color='red')

x = np.linspace(mi_n, ma_n, 30)
y = np.linspace(mi_m, ma_m, 30)
x, y = np.meshgrid(x, y)
d = (ex[2][2] - ex[0][2]) / (ma_n - mi_n) / (ma_m - mi_m)
o = ex[0][2] - ex[0][1]*ex[0][0] * d
print(int(1/d), o)
z = x * y * d + o
ax.plot_surface(x, y, z, color='b', alpha=0.3)

ax.set_xlabel("Nombre de variables")
ax.set_ylabel("Nombre de contraintes")
ax.set_zlabel("Logarithme du temps d'exécution")

pl.show()