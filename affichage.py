from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as pl
from math import log

fig = pl.figure()
ax = fig.add_subplot(111, projection='3d')

# Make data
f = open("perf.txt", 'r')
x, y, z = [], [], []
xx, yy, zz = [], [], []
v = -1
for l in f:
	n, m, _, t = l.split()
	n, m, t = int(n), int(m), log(float(t))
	x.append(n)
	y.append(m)
	z.append(t)

# Plot the surface
ax.scatter(x, y, z)

pl.show()