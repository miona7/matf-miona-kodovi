clan(X, [X | _]).
clan(X, [_ | R]):- clan(X, R).

% b(ime, broj knjiga, novac)

braca(L):- L = [b(stefan, 3, _), 
                b(milos, K2, 1200),
                b(vanja, K1, _),
                b(petar, _, _)],

                clan(b(_, _, 600), L),
                clan(b(_, _, 3200), L),
                clan(b(_, 4, _), L),
                clan(b(_, 8, _), L),

                clan(b(_, 5, 1500), L),
                
                % clan(b(vanja, K1, _), L),
                % clan(b(milos, K2, _), L),
                K1 =:= K2 + 1,

                not(clan(b(stefan, 3, 600), L)),
                not(clan(b(vanja, _, 600), L)),
                not(clan(b(petar, 4, _), L)).