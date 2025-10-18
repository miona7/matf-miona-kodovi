clan(X, [X | _]).
clan(X, [_ | R]):- clan(X, R).

prvoSlovo(Atom, L):- atom_chars(Atom, [L | _]). 

% p(imeMajke, prezime, imeCerke)
zag(L):- L = [p(petra, P1, C1),
                p(milica, P2, C2),
                p(lenka, P3, petra),
                p(jovana, P4, C4)],

            permutation([C1, C2, C4], [milica, lenka, jovana]),
            C1 \= petra, C2 \= milica, C4 \= jovana,

            permutation([P1, P2, P3, P4], [peric, mikic, lazic, jovic]),
            P1 \= peric, P2 \= mikic, P3 \= lazic, P4 \= jovic,

            prvoSlovo(C1, LC1), prvoSlovo(P1, LP1), LC1 \= LP1,
            prvoSlovo(C2, LC2), prvoSlovo(P2, LP2), LC2 \= LP2,
            prvoSlovo(petra, LC3), prvoSlovo(P3, LP3), LC3 \= LP3,
            prvoSlovo(C4, LC4), prvoSlovo(P4, LP4), LC4 \= LP4,

            clan(p(MajkaPeric, peric, _), L),
            clan(p(milica, _, MilicinaCerka), L),
            MajkaPeric = MilicinaCerka.

            

