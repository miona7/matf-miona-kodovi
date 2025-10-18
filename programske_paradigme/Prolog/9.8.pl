% A   F
%  B G
%   C
%  H D
% I   E

raspored(Vars):- Vars = [A, B, C, D, E, F, G, H, I],
                    Vars :: 1..9,
                    alldifferent(Vars),
                    A + B + C + D + E #= 25,
                    F + G + C + H + I #= 25,
                    A #< B,
                    B #< C,
                    C #< D,
                    D #< E,
                    F #< G,
                    G #< C,
                    C #< H,
                    H #< I,
                    labeling(Vars),
                    write(A), write(' '), write(' '), write(' '), write(F), nl,
                    write(' '), write(B), write(' '), write(G), write(' '), nl,
                    write(' '), write(' '), write(C), write(' '), write(' '), nl,
                    write(' '), write(H), write(' '), write(D), write(' '), nl,
                    write(I), write(' '), write(' '), write(' '), write(E), nl.
