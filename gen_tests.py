#!/usr/bin/env python3

N0, M0 = 3, 2 # Nombre de variables et de contraintes minimum
N, M = 30, 60 # Nombre de variables et de contraintes maximum
pn, pm = 2, 4 # Pas entre les nombres de variables et de contraintes

ts = [str(n)+" "+str(m) for n in range(N0, N, pn) for m in range(M0, M, pm)]

print(len(ts))
for t in ts:
	print(t)