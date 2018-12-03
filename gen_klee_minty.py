#!/usr/bin/env python3
import sys

if len(sys.argv) < 2:
	print("The dimension is needed as argument")
	exit(-1)
d = int(sys.argv[1])

print(d)
print(d)

p = [1]
for i in range(d):
	p.append(p[i]*2)
for i in range(d):
	print(p[d-i-1], end=' ')
print()

p5 = 1
for i in range(d):
	p5 *= 5
	print(p5, end=' ')
print()

for i in range(d):
	for j in range(i):
		print(p[1+i-j], end=' ')
	print(1, end=' ')
	for j in range(d-i-1):
		print(0, end=' ')
	print()

print()
print('# The polytope is the Klee-Minty polytope')