clan(X, [X | _]).
clan(X, [_ | R]):- clan(X, R).

% d(ime, prezime, igra, grickalica)
prijatelji(X):- X = [d(I1, P1, IG1, G1),
                        d(I2, P2, IG2, G2),
                        d(I3, P3, IG3, G3),
                        d(I4, P4, IG4, G4)],

                        permutation([I1, I2, I3, I4], [marko, ivana, nemanja, milica]),
                        permutation([P1, P2, P3, P4], [markovic, stefanovic, radosavljevic, milic]),
                        permutation([IG1, IG2, IG3, IG4], [bilijar, 'stoni fudbal', 'mini golf', kuglanje]),
                        permutation([G1, G2, G3, G4], [pica, nacos, kokice, sladoled]),

                        \+ clan(d(marko, _, 'stoni fudbal', _), X),
                        clan(d(marko, _, _, nacos), X),
                        clan(d(_, markovic, _, kokice), X),
                        \+ clan(d(milica, milic, _, _), X),
                        clan(d(_, _, bilijar, pica), X),
                        \+ clan(d(milica, _, bilijar, _), X),
                        clan(d(ivana, stefanovic, _, _), X),
                        \+ clan(d(nemanja, radosavljevic, _, _), X),
                        clan(d(nemanja, _, 'mini golf', _), X),
                        \+ clan(d(_, radosavljevic, kuglanje, _), X).

