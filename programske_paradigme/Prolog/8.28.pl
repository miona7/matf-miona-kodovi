praviDelioci(K, N, []):- K >= N, !. 
praviDelioci(K, N, [K | L]):- K < N, N mod K =:= 0, K1 is K + 1, praviDelioci(K1, N, L). 
praviDelioci(K, N, L):- K < N, N mod K =\= 0, K1 is K + 1, praviDelioci(K1, N, L). 

suma([], 0).
suma([G | R], S):- suma(R, S1), S is G + S1. 

savrsen(N):- N =< 0, write('greska'), nl, fail.
savrsen(N):- praviDelioci(1, N, L), suma(L, S), S =:= N.
