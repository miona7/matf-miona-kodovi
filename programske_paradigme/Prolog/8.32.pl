% da li je X clan liste L
clan(X, [X | _]).
clan(X, [_ | R]):- clan(X, R).

% X je za 1 godinu stariji od Y
stariji(X, Y):- X is Y + 1.

% X je za 3 godine stariji od Y
stariji3(X, Y):- X is Y + 3.

% X je duplo stariji od Y
duploStariji(X, Y):- X is 2*Y.

% d(ime, prezime, godine)
deca(L):- L = [d(lazar, jankovic, G1), 
                d(kata, _, G2),
                d(nevenka, grbovic, G3),
                d(ognjen, _, G4),
                d(petar, _, G5)],

        permutation([2, 3, 4, 5, 6], [G1, G2, G3, G4, G5]),
        
        clan(d(kata, _, G2), L),
        clan(d(_, ivanovic, Gx), L),
        clan(d(nevenka, _, G3), L),
        stariji(G2, Gx),
        stariji(Gx, G3),

        clan(d(_, filipovic, Gf), L),
        clan(d(petar, _, G5), L),
        stariji3(Gf, G5),

        clan(d(ognjen, _, G4), L),
        clan(d(_, hadzic, Gh), L),
        duploStariji(G4, Gh).


