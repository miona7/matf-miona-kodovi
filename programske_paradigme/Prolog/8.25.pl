nzd(A, 0, A):- !.
nzd(A, B, R):- A1 is A mod B, nzd(B, A1, R).

nzs(A, B, R):- nzd(A, B, N), R is A*B // N.