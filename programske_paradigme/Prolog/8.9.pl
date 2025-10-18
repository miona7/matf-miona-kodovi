film(after, erotski, anaTod, 069).
film(after, erotski, hero, 069).
film(after2, komedija, hero, 069).
film(after3, komedija, lena, 096).

glumac(069, hero, 2000, london).
glumac(096, lena, 2001, london).

filmskiUmetnik(X):- film(_, _, X, Y), glumac(Y, X, _, _).
glumacBarDva(X):- film(Z, _, X, Y), film(L, _, X, Y), Z \== L.
opstiGlumac(X):- film(_, Z, X, Y), film(_, L, X, Y), Z \== L.
zanrovskiGlumac(X, Y):- film(_, Y, _, Z), glumac(Z, X, _, _).