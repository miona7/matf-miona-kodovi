import sys

try:
    n = int(input("Unesite ceo broj: "))
    print(n)
except ValueError as e:
    print(e)
    sys.exit(1)

s1 = "Miona i Marko"
s2 = "Miona i Rajko"

print(s1, id(s1))
print(s2, id(s2))
print(s1 == s2)