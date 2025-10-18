celi(X, Y, []):- X > Y, !.
celi(X, Y, [X | R]):- X1 is X + 1, celi(X1, Y, R). 

interval(X, Y, L):- celi(X, Y, L).