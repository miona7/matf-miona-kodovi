import random as r
import math as m
import sys 

def dist(A, B):
    return m.sqrt((A[0] - B[0])**2 + (A[1] - B[1])**2)

try:
    N = int(input("unesite broj iteracija: "))
except ValueError as e:
    print(e)
    sys.exit(1)

A = 0
B = 0

while N >= 0:
    tacka = (r.random(), r.random())
    if dist(tacka, (0.5, 0.5)) <= 0.5:
        A += 1
    
    B += 1
    N -= 1

print("broj PI aproksimiran Monte Karlo metodom: {0:.3f}".format(4*A/B))