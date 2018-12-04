#!/usr/bin/env python3
import sys

if len(sys.argv) < 2:
	print("The dimension is needed as argument")
	exit(-1)
d = int(sys.argv[1])

print(d)
print(1)
for i in range(1, d+1):
	print(i, end=' ')
print()
print(1)
for i in range(1, d+1):
	print(1, end=' ')
print()

print(s)
print("# Solving in {} steps for BLAND'S RULE and in 1 step for MAXIMUM RULE".format(d))