
grncarija:- Vars = [S, T],
            S :: [0..200],
            T :: [0..400],

            6*S + 3*T #=< 1200,
            75*S + 100*T #=< 250000,

            labeling([maximize(4*S + 3*T)], Vars),

            write(S), nl,
            write(T).