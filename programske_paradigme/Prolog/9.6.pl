resi(Vars):- Vars = [T, W, O, F, U, R],
        Vars :: [0..9],
        alldifferent(Vars),
        T #\= 0,
        F #\= 0,

        2*(T*100 + W*10 + O) #= F*1000 + O*100 + U*10 + R,

        labeling(Vars).
