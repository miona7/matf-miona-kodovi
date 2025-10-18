musko(mihajlo).
musko(stevan).
musko(petar).
musko(mladen).
musko(rajko).

zensko(milena).
zensko(milica).
zensko(jelena).
zensko(senka).
zensko(mina).
zensko(maja).

roditelj(mihajlo, milica).
roditelj(mihajlo, senka).
roditelj(milena, rajko).
roditelj(maja, petar).
roditelj(maja, mina).
roditelj(stevan, mladen).
roditelj(stevan, jelena).
roditelj(milica, mladen).
roditelj(milica, jelena).

otac(X, Y):- musko(X), roditelj(X, Y).
majka(X, Y):- zensko(X), roditelj(X, Y).
brat(X, Y):- musko(X), roditelj(Z, X), roditelj(Z, Y), X \== Y.
sestra(X, Y):- zensko(X), roditelj(Z, X), roditelj(Z, Y), X \== Y.
ujak(X, Y):- musko(X), majka(Z, Y), brat(X, Z). 
tetka(X, Y):- zensko(X), roditelj(Z, Y), sestra(X, Z).

predak(X, Y):- roditelj(X, Y).
predak(X, Y):- roditelj(X, Z), predak(Z, Y).