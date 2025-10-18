form(N, L):- form1(1, N, L).

form1(K, N, []):- K >= N, !.
form1(K, N, [K | R]):- K < N, K mod 5 =:= 0, K1 is K + 1, form1(K1, N, R), !.
form1(K, N, R):- K < N, K mod 5 =\= 0, K1 is K + 1, form1(K1, N, R).