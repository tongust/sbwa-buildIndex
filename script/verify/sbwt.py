import numpy as np
from sys import argv
from sys import stdin
from testbwa import rotation


def spaced_sort(t,sp):
    return sorted(t, key =  lambda w : w[0::sp])
def sbwm(t,sp):
    return spaced_sort(rotation(t), 2)
def SA(t,sp):
    t = rotation(t)
    return sorted(range(len(t)), key = lambda k: t[k][0::sp])

if __name__ == '__main__':
    for i in stdin:
        i = i[:-1:]
        if (len(i)%2 == 1):
            i = i + '$'
        else:
            i = i + '$$'
        sa = SA(i, 2)
        print sbwm(i, 2)
        for s in sa:
            print s


