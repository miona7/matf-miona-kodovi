rafinerija:- Vars = [B, D],
                B :: [0..600000],
                D :: [0..600000],
                
                B + D #=< 600000,
                2*D #>= B, 
                B #>= 150000,
                D #=< 325000,
                
                labeling([maximize(2*B + D)], Vars),
                
                Zarada is 2*B + D,

                write('Maksimalna zarada je: '), write(Zarada), write(' dolara'), nl,
                write('Kolicina bezina je: '), write(B), write(' galona'), nl,
                write('Kolicina dizela je: '), write(D), write(' galona').
                