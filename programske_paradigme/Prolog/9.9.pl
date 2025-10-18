umesi:- Vars = [H, K],
                H :: 0..66,
                K :: 0..100,
                10*H + 12*K #=< 1200,
                300*H + 120*K #=< 20000,
                labeling([maximize(7*H + 9*K)], Vars),
                Zarada is 7*H + 9*K, write('Maksimalna zarada je '), write(Zarada), nl,
                write(H), nl,
                write(K), nl.