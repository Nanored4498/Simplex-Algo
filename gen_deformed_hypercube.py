#!/usr/bin/env python3
import sys

if len(sys.argv) < 2:
	print("The dimension is needed as argument")
	exit(-1)
d = int(sys.argv[1])

print(d)
print(2*d-1)

print(1, end=' ')
for i in range(d-1):
	print(0, end=' ')
print()

print(1, end=' ')
for i in range(d-1):
	print('0 1', end=' ')
print()

print(1, end=' ')
for i in range(d-1):
	print(0, end=' ')
print()
for i in range(d-1):
	for j in range(i):
		print(0, end=' ')
	print('1/3 -1', end=' ')
	for j in range(d-i-2):
		print(0, end=' ')
	print()
	for j in range(i):
		print(0, end=' ')
	print('1/3 1', end=' ')
	for j in range(d-i-2):
		print(0, end=' ')
	print()

print()
print('# The polytope is a deformed hypercube')