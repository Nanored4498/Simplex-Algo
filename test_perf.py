#!/usr/bin/env python3
from time import time
from subprocess import call

calcs = {}

f = open("perf.txt", 'r')
for li in f:
	n, m, num, t = li.split()
	calcs[(int(n), int(m))] = (int(num), float(t))
f.close()

N = int(input())
for _ in range(N):
	n, m = map(int, input().split())
	t0 = time()
	call('./gen_random.py {} {} | ./coudert-exec -b > temp'.format(n, m), shell=True)
	t1 = time()
	i = (n, m)
	num, t = calcs[i] if i in calcs else (0, 0)
	calcs[i] = (num+1, (num*t + t1 - t0) / (num + 1))
call(['rm', 'temp'])

f = open("perf.txt", 'w')
for (n, m) in calcs:
	num, t = calcs[(n, m)]
	f.write("{} {} {} {}\n".format(n, m, num, t))
f.close()