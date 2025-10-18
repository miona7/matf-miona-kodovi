opadajuce(1, [1]):- !.
opadajuce(N, [N | R]):- N > 1, N1 is N - 1, opadajuce(N1, R).