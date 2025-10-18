opadajuce([]):- !.
opadajuce([_]).
opadajuce([X, Y | R]):- X >= Y, opadajuce([Y | R]).

rastuce([]):- !.
rastuce([_]).
rastuce([X, Y | R]):- X =< Y, rastuce([Y | R]).

sortirana(L):- opadajuce(L).
sortirana(L):- rastuce(L).