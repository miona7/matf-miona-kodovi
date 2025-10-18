import math as m
print(m.factorial(5))
print(m.log(4, 2))
print(m.log(10, 10))
print()


import random as r
print(r.random())
print(r.randint(0, 10))
print()


import sys
print(sys.argv)
print()


import os
print(os.listdir())
os.system("ls -l")
print()


import time as t
print(t.time())
print()


from re import search as rs 
print(rs(r'[0-9]+', input("unesite string: ")))