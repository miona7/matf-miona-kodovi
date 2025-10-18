kompresuj([], []).
kompresuj([X], [X]):- !.
kompresuj([X, X | R], KL):- kompresuj([X | R], KL).
kompresuj([X, Y | R], [X | KL]):- X \== Y,  kompresuj([Y | R], KL).