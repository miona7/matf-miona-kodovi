mica:- Vars = [S, K],
        S :: [0..40],
        K :: [0..27],

        2*S + 3*K #=< 80,
        120*S + 100*K #=< 5000,

        labeling([maximize(1000*S + 1500*K)], Vars),

        write(S), nl,
        write(K), nl.
