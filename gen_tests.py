#!/usr/bin/env python3

N0, M0 = 3, 2
N, M = 30, 60
pn, pm = 2, 4

ts = [str(n)+" "+str(m) for n in range(N0, N, pn) for m in range(M0, M, pm)]

print(len(ts))
for t in ts:
	print(t)