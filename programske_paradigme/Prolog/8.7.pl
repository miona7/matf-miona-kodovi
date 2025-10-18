sumaCifara(N, SC):- N < 0, sumaCifara(-N, SC), !.
sumaCifara(N, SC):- N >= 0, N < 10, SC is N.
sumaCifara(N, SC):- N >= 10, N1 is (N div 10), sumaCifara(N1, SC1), SC is SC1 + (N mod 10).

brojCifara(N, BC):- N < 0, brojCifara(-N, BC), !.
brojCifara(N, BC):- N >= 0, N < 10, BC is 1.
brojCifara(N, BC):- N >= 10, N1 is N div 10, brojCifara(N1, BC1), BC is BC1 + 1. 

maxCifra(N, MC):- N < 0, maxCifra(-N, MC), !.
maxCifra(N, MC):- N >= 0, N < 10, MC is N.
maxCifra(N, MC):- N >= 10, N1 is N div 10, maxCifra(N1, MC1), C is N mod 10, C >= MC1, MC is C, !.
maxCifra(N, MC):- N >= 10, N1 is N div 10, maxCifra(N1, MC1), C is N mod 10, C < MC1, MC is MC1.

sumaKvadrata(0, 0):- !.
sumaKvadrata(N, SK):- N > 0, N1 is N - 1, sumaKvadrata(N1, SK1), SK is SK1 + N*N.

fakt(0, 1):- !.
fakt(N, F):- N > 0, N1 is N - 1, fakt(N1, F1), F is F1 * N.

sumaDel1(X, X, 0):- !.
sumaDel1(X, K, D):- K1 is K + 1, sumaDel1(X, K1, D1), O is X mod K, O == 0, D is D1 + K, !.
sumaDel1(X, K, D):- K1 is K + 1, sumaDel1(X, K1, D1), O is X mod K, O \== 0, D is D1.

sumaDel(X, D):- sumaDel1(X, 2, D).

