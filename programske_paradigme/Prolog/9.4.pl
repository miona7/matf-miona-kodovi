% A B C
% D E F
% G H I

kvadrat:- Vars = [A, B, C, D, E, F, G, H, I],
                Vars :: 1..9,

                alldifferent(Vars),
                
                A + B + C #= 15,
                D + E + F #= 15,
                A + B + C #= 15,

                A + D + G #= 15,
                B + E + H #= 15,
                C + F + I #= 15,

                A + E + I #= 15,
                C + E + G #= 15,

                labeling(Vars),

                write(A), write(' '), write(B), write(' '), write(C), nl,
                write(D), write(' '), write(E), write(' '), write(F), nl,
                write(G), write(' '), write(H), write(' '), write(I), nl.