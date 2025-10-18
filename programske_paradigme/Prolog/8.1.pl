zivotinja(slon).
zivotinja(vuk).
zivotinja(zec).
zivotinja(zebra).

veci(slon, vuk).
veci(vuk, zec).
veci(slon, zebra).
veci(zebra, vuk).

je_veci(X, Y):- veci(X, Y).
je_veci(X, Y):- veci(X, Z), je_veci(Z, Y).