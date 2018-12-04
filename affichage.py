from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as pl
from math import log

fig = pl.figure()
ax = fig.add_subplot(111, projection='3d')

# Make data
f = open("perf.txt", 'r')
x, y, z = [], [], []
xx, yy, zz = [], [], []
ex = [(1000, 1000, 1000), (-1, 1000, 1000), (-1, -1, -1000), (1000, -1, 1000)]
cs = [(-1, -1, -1), (1, -1, -1), (1, 1, 1), (-1, 1, -1)]
for l in f:
	n, m, _, t = l.split()
	n, m, t = int(n), int(m), log(float(t))
	x.append(n)
	y.append(m)
	z.append(t)
	for i in range(4):
		if 2 * cs[i][0] * (n - ex[i][0]) + cs[i][1] * (m - ex[i][1]) + 20 * cs[i][2] * (t - ex[i][2]) > 0:
			ex[i] = (n, m, t)

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

pl.show()