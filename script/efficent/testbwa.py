import numpy as np
from sys import stdin
from sys import argv
import time
from random import randint
def rotation(t):
	""" Return list of rotations of input stringt """
	tt = t*2
	return [ tt[i:i+len(t)] for i in xrange(0, len(t))]

def bwm(t):
	""" Return lexicographically sorted list of t's rotations """
	return sorted(rotation(t))

def bwtViaBwm(t):
	""" Given T, returns BWT(T) by the way of the BWM """
	return ''.join(map(lambda x: x[-1], bwm(t)))
def bwtIndex(t):
        """ Return the index of sorted t """
        t_rots = rotation(t);
        return sorted(range(len(t_rots)), key = lambda k: t_rots[k])

if __name__ == '__main__':
    for i in stdin:
        t = i[0:-1:] + '$'
        res=  bwtIndex(t)
