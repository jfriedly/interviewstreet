#! /usr/bin/python

from random import randint
print 10
for i in range(10):
    N = randint(1,50000)
    print N
    print 0,
    for j in range(N):
        if j != N - 1:
            print randint(0,N/100),
        else:
            print randint(0,N/100)
