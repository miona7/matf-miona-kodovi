spoj(L1, [], L1):- !. 
spoj([], L2, L2):- !.
spoj([G1 | R1], [G2 | R2], [G1 | R]):- G1 < G2, spoj(R1, [G2 | R2], R), !.  
spoj([G1 | R1], [G2 | R2], [G2 | R]):- G1 >= G2, spoj([G1 | R1], R2, R).  