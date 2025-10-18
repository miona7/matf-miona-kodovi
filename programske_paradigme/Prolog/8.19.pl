podeli([], _, [], []):- !. 
podeli(L, 0, [], L):- !. 
podeli([G | R], N, [G | R1], L2):- N1 is N-1, podeli(R, N1, R1, L2). 