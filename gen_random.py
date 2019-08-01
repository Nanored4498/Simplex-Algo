#!/usr/bin/env python3
import sys
from random import random

neg_rh = False

if len(sys.argv) < 3:
	print("The dimension is needed as argument")
	exit(-1)
d = int(sys.argv[1])
n = int(sys.argv[2])

print(d)
print(n)

for _ in range(d):
	print(1, end=' ')
print()

for _ in range(n):
	if(neg_rh and random() < 0.5):
		print(-10000, end=' ')
	else:
		print(10000, end=' ')
print()

for _ in range(n):
	for j in range(d):
		print(int(random()*500), end=' ')
	print()

print()
print('# The polytope is random')