uzastopni(X, Y, Z, [X, Y, Z | _]).
uzastopni(X, Y, Z, [G | R]):- G \== X, uzastopni(X, Y, Z, R).
