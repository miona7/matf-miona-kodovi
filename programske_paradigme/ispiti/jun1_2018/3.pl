% X je odma desno od Y
desno_od(X, Y, [Y, X | _]).
desno_od(X, Y, [_ | R]):- desno_od(X, Y, R).

sused(X, Y, Z):- desno_od(X, Y, Z).
sused(X, Y, Z):- desno_od(Y, X, Z).

sadrzi(X, [X | _]).
sadrzi(X, [_ | R]):- sadrzi(X, R). 

% a(drzava, proizvodjac, boja, gorivo, cena)

kola(L):- L = [a(_, bmw, _, _, _),
                a(francuska, _, _, _, _),
                a(_, _, _, benzin, _),
                a(_, _, _, _, _),
                a(_, _, _, _, _)],
                
                sadrzi(a(japan, honda, _, _, _), L),
                sadrzi(a(_, fiat, crvena, _, _), L),
                sadrzi(a(sad, _, _, dizel, _), L),
                sadrzi(a(_, reno, _, metanol, _), L),

                desno_od(a(sad, _, _, _, _), a(italija, _, _, _, _), L),

                sadrzi(a(_, _, plava, _, 60000), L),
                sadrzi(a(nemacka, _, _, _, 100000), L),

                sused(a(_, _, _, _, 40000), a(_, _, crna, _, _), L),
                sused(a(_, _, _, _, 100000), a(_, _, zuta, _, _), L),

                sadrzi(a(_, _, _, plin, 30000), L),
                sadrzi(a(_, ford, _, _, 50000), L),

                sadrzi(a(_, _, zelena, _, _), L),
                sadrzi(a(_, _, _, etanol, _), L).

