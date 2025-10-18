jednake([], []). 
jednake([X], [X]). 
jednake([G | R1], [G | R2]):- jednake(R1, R2).

dodajNaKraj(X, [], [X]).
dodajNaKraj(X, [G | R], [G | R1]):- dodajNaKraj(X, R, R1).

obrni([], []).
obrni([X], [X]):- !.
obrni([G | R], L):- obrni(R, R1), dodajNaKraj(G, R1, L).  

ogledalo(L1, L2):- obrni(L2, NL2), jednake(L1, NL2).