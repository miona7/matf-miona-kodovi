clan(X, [X | _]).
clan(X, [_ | R]):- clan(X, R).

% X je dosao pre Y
dosaoPre(X, Y, [X | R]):- clan(Y, R).
dosaoPre(X, Y, [_ | R]):- dosaoPre(X, Y, R).

% X je dosao posle Y
dosaoPosle(X, Y, L):- dosaoPre(Y, X, L).

% X je stigao prvi
prvi(X, [X | _]).

% p(imeMuza, maskaMuza, imeZene, maskaZene)
maskenbal(L):- L = [p(_, _, _, _),
                    p(_, _, _, _),
                    p(_, _, _, _),
                    p(_, _, _, _)],

                permutation([marko, vasa, pera, laza], [M1, M2, M3, M4]),
                permutation([marija, bojana, ivana, ana], [Z1, Z2, Z3, Z4]),
                permutation([pajaPatak, medved, betmen, princ], [MM1, MM2, MM3, MM4]),
                permutation([macka, vestica, ciganka, snezana], [ZM1, ZM2, ZM3, ZM4]),
    
                L = [p(M1, MM1, Z1, ZM1),
                    p(M2, MM2, Z2, ZM2),
                    p(M3, MM3, Z3, ZM3),
                    p(M4, MM4, Z4, ZM4)],

                clan(p(marko, _, _, macka), L),

                dosaoPre(p(_, medved, _, _), p(marko, _, _, macka), L),
                dosaoPre(p(_, _, _, _), p(marko, _, _, macka), L),

                dosaoPre(p(vasa, _, _, _), p(_, princ, _, _), L),
                \+ prvi(p(vasa, _, _, _), L),

                clan(p(pera, pajaPatak, _, vestica), L),
                \+ clan(p(_, _, bojana, vestica), L),
                
                dosaoPosle(p(_, _, marija, _), p(laza, _, _, _), L),        
                dosaoPre(p(_, _, marija, _), p(_, _, bojana, _), L),
                dosaoPre(p(laza, _, _, _), p(_, _, bojana, _), L),
                
                dosaoPre(p(_, _, _, ciganka), p(_, _, ana, _), L),
                \+ clan(p(_, betmen, _, ciganka), L),
                \+ clan(p(_, betmen, ana, _), L),

                dosaoPosle(p(_, _, _, snezana), p(_, _, ivana, _), L).


