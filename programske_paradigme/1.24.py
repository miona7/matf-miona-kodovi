import random as r

def ispisi_tablu(tabla):
    print("TABLA")
    print("1 2 3")
    print("--- --- ---")

    indeks = 1
    for i in tabla:
        print(indeks, "|", i[0], "|", i[1], "|", i[2], "|")
        print("--- --- ---")
        indeks += 1
    print()

def pobedio(tabla):
    if (tabla[0][0] != "-" and tabla[0][2] != "-") \
        and ((tabla[0][0] == tabla[1][1] == tabla[2][2]) or (tabla[0][2] == tabla[1][1] == tabla[2][0])):
        return True
    for i in range(3):
        if (tabla[0][i] != "-" and tabla[i][0] != "-") \
            and ((tabla[0][i] == tabla[1][i] == tabla[2][i]) or (tabla[i][0] == tabla[i][1] == tabla[i][2])):
            return True
    return False

def ucitaj_koordinate(ime):
    while True:
        print("{0:s} unesite koordinate polja koje zelite da popunite u posebnim linijama".format(ime))
        v = int(input("Unesite vrstu: "))
        k = int(input("Unesite kolonu: "))
        if 1 <= v <= 3 and 1 <= k <= 3:
            return v-1, k-1
        else:
            print("Morate uneti brojeve 1, 2 ili 3")

def korak(igrac):
    while True:
        v, k = ucitaj_koordinate(igrac[0])
        print()
        if tabla[v][k] == "-":
            tabla[v][k] = igrac[1]
            ispisi_tablu(tabla)
            break
        else:
            print(tabla[v][k])
            print("Uneto polje je popunjeno!")

print("IGRA: X-O pocinje")
i1 = input("Unesite ime prvog igraca: ")
print("Zdravo {0:s}".format(i1))
i2 = input("Unesite ime drugog igraca: ")
print("Zdravo {0:s}".format(i2))
print()

ind = r.randint(1, 2)
if ind == 1:
    prvi_igrac = (i1, "X")
    drugi_igrac = (i2, "O")
elif ind == 2:
    prvi_igrac = (i2, "X")
    drugi_igrac = (i1, "O")

print("Igrac ('{0:s}', 'X') igra prvi.".format(prvi_igrac[0]))
print("X : ('{0:s}', 'X')".format(prvi_igrac[0]))
print("O : ('{0:s}', 'X')".format(drugi_igrac[0]))
print()

tabla = [["-", "-", "-"], ["-", "-", "-"], ["-", "-", "-"]]
print("Zapocnimo igru:")
ispisi_tablu(tabla)

na_redu = 0
i = 0
igraci = [prvi_igrac, drugi_igrac]

while i < 9:
    korak(igraci[na_redu])
    if pobedio(tabla):
        print("BRAVO!!! Igrac {0:s} je pobedio!".format(igraci[na_redu][0]))
        break
    i += 1
    na_redu = (na_redu + 1) % 2


if i == 9:
    print("Nereseno! Pokusajte ponovo")