obuka:- Vars = [E, D],
        Vars :: 0..250,
        E + D #= 250,
        150*E + 170*D #=< 51200,
        100*E + 105*D #=< 26000,

        labeling([maximize(150*5*E + 170*6*D - (100*E + 105*D))], Vars),
        Zarada is 50*5*E + 170*6*D - (100*E + 105*D), write(Zarada), nl,
        write(E), nl, 
        write(D), nl.