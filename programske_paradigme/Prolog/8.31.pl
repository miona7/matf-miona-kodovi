% da li je X clan liste
clan(X, [X | _]).
clan(X, [_ | R]):- clan(X, R).

% X je desno od Y u listi
desno(X, Y, [Y, X | _]).
desno(X, Y, [_ | R]):- desno(X, Y, R).

% X je pored Y u listi
pored(X, Y, [Y, X | _]).
pored(X, Y, [X, Y | _]).
pored(X, Y, [_ | R]):- pored(X, Y, R).

% k(boja, nacionalnost, pice, jelo, ljubimac)
kuce(L):- L = [k(_, norvezanin, _, _, _),
                k(plava, _, _, _, _),
                k(_, _, mleko, _, _),
                k(_, _, _, _, _),
                k(_, _, _, _, _)],
        clan(k(crvena, englez, _, _, _), L),
        clan(k(_, spanac, _, _, pas), L),
        clan(k(zelena, _, kafa, _, _), L),
        clan(k(_, ukrajinac, caj, _, _), L),
        desno(k(zelena, _, kafa, _, _), k(bela, _, _, _, _), L),
        clan(k(_, _, _, spagete, puz), L),
        clan(k(zuta, _, _, pica, _), L),
        pored(k(_, _, _, piletina, _), k(_, _, _, _, lisica), L),
        pored(k(_, _, _, pica, _), k(_, _, _, _, konj), L),
        clan(k(_, _, narandza, brokoli, _), L),
        clan(k(_, japanac, _, susi, _), L),
        clan(k(_, _, _, _, zebra), L),
        clan(k(_, _, voda, _, _), L).
        
zagonetka(X, Y):- kuce(L), clan(k(_, X, _, _, zebra), L), clan(k(_, Y, voda, _, _), L).