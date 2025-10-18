manji_i_veci([], _, [], []).
manji_i_veci([G | R], P, [G | R1], VL):- G =< P, manji_i_veci(R, P, R1, VL).
manji_i_veci([G | R], P, ML, [G | R1]):- G > P, manji_i_veci(R, P, ML, R1).

qsort([], []).
qsort([G | R], S):- manji_i_veci(R, G, ML, VL), qsort(ML, S1), qsort(VL, S2), spoji(S1, [G | S2], S).

%, ubaci(SOR, G, S).

% spoji([], [], []).

spoji([], L, L).
spoji(L, [], L).
spoji([G1 | R1], [G2 | R2], [G1 | R]):- G1 =< G2, spoji(R1, [G2 | R2], R).
spoji([G1 | R1], [G2 | R2], [G2 | R]):- G1 > G2, spoji([G1 | R1], R2, R).

ubaci([], P, [P]).
ubaci([G | R], P, [P, G | R]):- P =< G.
ubaci([G | R], P, [G | R1]):- P > G, ubaci(R, P, R1).