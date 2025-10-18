podeli([], [], []).
podeli([G | R], [G | R1], L2):- G >= 0, podeli(R, R1, L2), !.
podeli([G | R], L1, [G | R2]):- G < 0, podeli(R, L1, R2).

dupliraj([], []).
dupliraj([G | R], [G, G | R1]):- G < 0, dupliraj(R, R1), !. 
dupliraj([G | R], [G | R1]):- dupliraj(R, R1). 

zameni(_, _, [], []).
zameni(X, Y, [X | R], [Y | R1]):- zameni(X, Y, R, R1), !.
zameni(X, Y, [Y | R], [X | R1]):- zameni(X, Y, R, R1), !.
zameni(X, Y, [G | R], [G | R1]):- G \== X, G \== Y, zameni(X, Y, R, R1).

izdvojPoslednji([G], G, []):- !.
izdvojPoslednji([G | R], X, [G | R1]):- izdvojPoslednji(R, X, R1).

pretvori1([], 0).
pretvori1(L, X):- izdvojPoslednji(L, Poslednji, Ostatak), pretvori1(Ostatak, X1), X is Poslednji + 10*X1.

maxEl([G], G).
maxEl([G | R], X):- maxEl(R, X1), G >= X1, X is G, !.
maxEl([G | R], X):- maxEl(R, X1), G < X1, X is X1.