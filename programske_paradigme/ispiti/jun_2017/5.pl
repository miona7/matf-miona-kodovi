stepenice(Vars):- Vars = [A, B, C, D, E, F, G, H, I],
                Vars :: [1..9],
                alldifferent(Vars),

                A + B + C #= 15,
                D + E + F #= 15,
                G + H + I #= 15,
                
                A + D + G #= 15,
                B + E + H #= 15,
                C + F + I #= 15,

                labeling(Vars),

                write(A), write(' '), write(B), write(' '), write(C), nl,
                write(' '), write(D), write(' '), write(E), write(' '), write(F), nl,
                write(' '), write(' '), write(G), write(' '), write(H), write(' '), write(I), nl.