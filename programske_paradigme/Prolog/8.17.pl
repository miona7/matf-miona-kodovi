insertionSort([], []).
insertionSort([G | R], SR):- insertionSort(R, SL1), ubaci(G, SL1, SR). 

ubaci(X, [], [X]).
ubaci(X, [G | R], [X, G | R]):- X =< G, !. 
ubaci(X, [G | R], [G | R1]):- ubaci(X, R, R1).

mergeSort([], []):- !.
mergeSort([X], [X]):- !.
mergeSort(L, SL):- podeli(L, L1, L2), mergeSort(L1, SL1), mergeSort(L2, SL2), objedini(SL1, SL2, SL). 

podeli([], [], []).
podeli([X], [X], []):- !.
podeli([G1, G2 | R], [G1 | R1], [G2 | R2]):- podeli(R, R1, R2).

objedini(L, [], L).
objedini([], L, L).
objedini([G1 | R1], [G2 | R2], [G1 | R]):- G1 =< G2, objedini(R1, [G2 | R2], R), !. 
objedini([G1 | R1], [G2 | R2], [G2 | R]):- G1 > G2, objedini([G1 | R1], R2, R), !. 