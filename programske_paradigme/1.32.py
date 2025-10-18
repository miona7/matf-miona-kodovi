s1 = input("Unesite prvu nisku: ")
s2 = input("Unesite drugu nisku: ")

if len(s1) >= len(s2):
    n = s1.count(s2)
    if n > 0:
        i = s1.find(s2)
        s1 = s1[0 : i] + "$" + s1[i + len(s2) : ]
        print(s1)
    else:
        print("-".join([s1, s2]))
else:
    print("Duzina niske {0:s} je {1:d}".format(s2, len(s2)))