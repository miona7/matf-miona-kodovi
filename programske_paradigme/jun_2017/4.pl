% d(ime, godine, muzika)

clan(X, [X | _]).
clan(X, [G | R]):- G \== X, clan(X, R). 

drugari(L):- L = [d(lazar, 24, _),
                    d(_, 25, _),
                    d(_, 26, _),
                    d(_, 27, jazz)],

                    clan(d(maja, _, _), L),
                    clan(d(ana, G4, _), L),
                    G4 < 27,

                    clan(d(jovan, G1, _), L),
                    clan(d(_, G2, pop), L),
                    G2 =:= G1 + 1, 

                    clan(d(_, _, rock), L),
                    clan(d(_, G3, techno), L),
                    G3 > 24,

                    not(clan(d(maja, _, techno), L)).
