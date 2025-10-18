komsa:- Vars = [R, S],
        R :: [0..70],
        S :: [0..125],

        R #=< 30,
        2*R #>= 3*S,

        labeling([maximize(400*R + 140*S)], Vars),

        write(R), nl,
        write(S).