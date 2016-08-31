#!/usr/bin/python3

import argparse
import numpy

def polydiv_start(base):
    digits = list(range(1, base))

    polydiv_loop(base, 0, digits, 1)

def polydiv_loop(base, value, digits, step):
    if step == base:
        if base > 36:
            print("*", value)
        else:
            print(numpy.base_repr(value, base), value)

    value *= base
    for d in digits:
        if (value + d) % step == 0:
            newdigits = digits[:]
            newdigits.remove(d)
            polydiv_loop(base, value+d, newdigits, step+1)


parser = argparse.ArgumentParser(description="Calculate polydivisible\
                    numbers for a given base")
parser.add_argument('base', metavar='N', type=int, nargs='*', default=10,
                    help="The base of the number")
args = parser.parse_args()

for base in args.base:
    print("Testing base {}...".format(base))
    polydiv_start(base)
