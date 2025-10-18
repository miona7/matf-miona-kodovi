ucenik(1, miona, 7).
ucenik(2, matija, 7).
ucenik(3, ognjen, 1).
ucenik(4, sofija, 1).

ocene(1, 100, 5).
ocene(1, 101, 4).
ocene(2, 101, 5).
ocene(3, 100, 5).
ocene(3, 101, 5).
ocene(4, 101, 5).

predmet(100, baze, 6).
predmet(101, vrv, 5).


barDvePeticeSifra(S):- ucenik(S, _, _), ocene(S, P1, 5), ocene(S, P2, 5), P1 \== P2. 
barDvePeticeIme(X):- ucenik(S, X, _), ocene(S, P1, 5), ocene(S, P2, 5), P1 \== P2. 

odeljenjePetice(X, Y):- ocene(U1, Y, 5), ocene(U2, Y, 5), U1 \== U2, ucenik(U1, _, X), ucenik(U2, _, X).