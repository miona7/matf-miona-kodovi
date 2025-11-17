clan(X, [X | _]).
clan(X, [_ | R]):- clan(X, R). 

% d(ime, prezime, vrsta, boja)

drugarice(X):- X = [d(milica, _, sandale, _),
                    d(anja, _, cipele, _),
                    d(jelena, _, _, _),
                    d(kaca, andonov, _, _)],
                
                clan(d(_, ranisavljevic, _, zelena), X),
                clan(d(_, bogdanovic, _, _), X),
                clan(d(_, cugurovic, _, _), X),
                
                clan(d(_, _, patike, _), X),
                
                clan(d(_, _, _, pink), X),
                clan(d(_, _, _, crna), X),
                
                clan(d(_, _, cizme, braon), X),
                \+ clan(d(_, cugurovic, cizme, braon), X),
                
                \+ clan(d(milica, ranisavljevic, _, _), X),                
                \+ clan(d(milica, _, sandale, crna), X),

                \+ clan(d(kaca, andonov, cizme, _), X),
                \+ clan(d(_, _, cipele, pink), X),

                \+ clan(d(anja, bogdanovic, _, _), X),
                \+ clan(d(jelena, _, patike, _), X).