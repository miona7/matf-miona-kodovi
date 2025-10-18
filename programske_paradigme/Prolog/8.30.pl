sadrzi(X, [X | _]):- !.
sadrzi(X, [G | R]):- G \== X, sadrzi(X, R).

duplikati([], []). 
duplikati([G | R], [G | R1]):- not(sadrzi(G, R)), duplikati(R, R1), !. 
duplikati([_ | R], R1):- duplikati(R, R1). 

spoj([], L, L). 
spoj([G | R1], L2, [G | R]):- spoj(R1, L2, R). 

unija(L1, L2, L):- spoj(L1, L2, NL), duplikati(NL, L).

presek([], _, []).
presek([G | R1], L2, [G | R]):- sadrzi(G, L2), presek(R1, L2, R), !.
presek([_ | R1], L2, L):- presek(R1, L2, L).

razlika([], _, []).
razlika([G | R1], L2, [G | R]):- not(sadrzi(G, L2)), razlika(R1, L2, R), !.
razlika([_ | R1], L2, L):- razlika(R1, L2, L).
