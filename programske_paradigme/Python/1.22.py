import random as r

broj = r.randint(0, 100)
print(broj)

s = input("unesite svoje ime: ")
print("Zdravo {0:s}".format(s))

pogodio = False

while not pogodio:
    x = int((input("unesite broj: ")))
    if x == broj:
        print("bravo pogodili ste broj")
        pogodio = True
    elif x < broj:
        print("zamisljeni broj je veci")
    else:
        print("zamisljeni broj je manji")