dodaj_na_kraj_liste(X, [], [X]). 
dodaj_na_kraj_liste(X, [G | R], [G | R1]):- dodaj_na_kraj_liste(X, R, R1). 

izdvoj_cifre(N, L):- N < 10, L = [N].
izdvoj_cifre(N, L):- N >= 10, C is (N mod 10), N1 is N // 10, izdvoj_cifre(N1, L1), dodaj_na_kraj_liste(C, L1, L).

izbaci([], []).
izbaci([G | R], [G | R1]):- G >= 3, izbaci(R, R1), !. 
izbaci([G | R], R1):- G < 3, izbaci(R, R1). 

napravi1([], Ak, Ak).
napravi1([G | R], X, Ak):- Ak1 is Ak*10 + G, napravi1(R, X, Ak1).

napravi(L, X):- napravi1(L, X, 0).

izbaci3(N, _):- N =< 0, write('greska'), nl, fail.
izbaci3(N, X):- izdvoj_cifre(N, L), izbaci(L, R), napravi(R, X). 