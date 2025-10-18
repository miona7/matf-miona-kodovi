parNepar([], [], []).
% parNepar([X], [X], []):- X mod 2 =:= 0, !.
% parNepar([X], [], [X]):- X mod 2 =\= 0, !.
parNepar([G | R], [G | R1], L2):- (G mod 2) =:= 0, parNepar(R, R1, L2), !.
parNepar([G | R], L1, [G | R2]):- (G mod 2) =\= 0, parNepar(R, L1, R2).

