krug(L):- L = [X1, X2, X3, X4, X5, X6, X7, X8, X9, X10],
        L :: [1..99],
        alldifferent(L),

        X1*X1 + X2*X2 #= X6*X6 + X7*X7, 
        X2*X2 + X3*X3 #= X8*X8 + X7*X7,
        X3*X3 + X4*X4 #= X8*X8 + X9*X9, 
        X4*X4 + X5*X5 #= X10*X10 + X9*X9, 
        X5*X5 + X6*X6 #= X10*X10 + X1*X1, 
        
        labeling([minimize(X1 + X2 + X3 + X4 + X5 + X6 + X7 + X8 + X9 + X10)], L), ispisi(L).

ispisi([X1, X2, X3, X4, X5, X6, X7, X8, X9, X10]):-
        format("    ~d  ~d\n", [X10, X1]),
        format("  ~d      ~d\n", [X9, X2]),
        format("~d          ~d\n", [X8, X3]),
        format("  ~d      ~d\n", [X7, X4]),
        format("    ~d  ~d\n", [X6, X5]), nl.