brojevi(Vars):- Vars = [A, B, C, D, E, F, G, H, I],
            Vars :: 0..9,

            alldifferent(Vars),
            A #\= 0,
            C #\= 0,
            F #\= 0,

            X #= 10*A + B, 
            Y #= 100*C + 10*D + E,
            Z #= 1000*F + 100*G + 10*H + I,
            X*Y #= Z,
            
            labeling([maximize(Z)], Vars),

            write(X), write(' * '), write(Y), write(' = '), write(Z), nl.