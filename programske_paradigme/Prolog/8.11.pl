dodajPocetak1(X, L, [X | L]).

dodajKraj(X, [], [X]).
dodajKraj(X, [G | R], [G | NLR]):- dodajKraj(X, R, NLR).

obrisiPrvi([], _):- fail.
obrisiPrvi([_ | R], R).


obrisiPoslednji([], _):- fail.
obrisiPoslednji([_], []):- !.
obrisiPoslednji([G | R], [G | R1]):- obrisiPoslednji(R, R1).

obrisi(_, [], []).
obrisi(X, [X | R], R1):- obrisi(X, R, R1), !.
obrisi(X, [G | R], [G | R1]):- G \== X, obrisi(X, R, R1).

obrisiPrvo(_, [], []).
obrisiPrvo(X, [X | R], R):- !.
obrisiPrvo(X, [G | R], [G | R1]):- G \== X, obrisiPrvo(X, R, R1).

obrisiK([], K, []):- K > 0.
obrisiK([G | R], 1, R):- !.
obrisiK([G | R], K, [G | R1]):- K > 1, K1 is K-1, obrisiK(R, K1, R1).
