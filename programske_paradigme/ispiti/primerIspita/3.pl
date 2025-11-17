clan(X, [X | _]).
clan(X, [_ | R]):- clan(X, R).

rodjendan(Lista):- Lista = [o(I1, PR1, P1),
                            o(I2, PR2, P2),
                            o(I3, PR3, P3),
                            o(I4, PR4, P4)],

                    permutation([I1, I2, I3, I4], [marija, stefan, milan, jana]),
                    permutation([PR1, PR2, PR3, PR4], [ivanovic, markovic, aleksic, jankovic]),
                    permutation([P1, P2, P3, P4], [narukvica, cvece, knjiga, torta]),

                    clan(o(_, ivanovic, narukvica), Lista),
                    clan(o(marija, markovic, _), Lista),
                    \+ clan(o(stefan, _, cvece), Lista),
                    \+ clan(o(_, aleksic, cvece), Lista),
                    clan(o(milan, _, knjiga), Lista),
                    clan(o(_, jankovic, torta), Lista),
                    \+ clan(o(jana, jankovic, torta), Lista).

odgovori(X, Y):- rodjendan(Lista), clan(o(X, _, cvece), Lista), clan(o(_, markovic, Y), Lista).

/*[o(jana, ivanovic, narukvica),
                o(marija, markovic, cvece),
                o(milan, aleksic, knjiga),
                o(stefan, jankovic, torta)],*/




