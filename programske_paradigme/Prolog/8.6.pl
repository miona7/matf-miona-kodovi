maksimum(A, B, M):- A >= B, M is A, !.
maksimum(_, B, M):- M is B.


suma(1, 1).
suma(N, S):- N > 1, N1 is N-1, suma(N1, S1), S is S1 + N.

sumaParnih(2, 2).
sumaParnih(N, S):- N > 2, N1 is N-2, sumaParnih(N1, S1), S is S1 + N. 

proizvod(1, 1).
proizvod(N, P):- N > 1, N1 is N-1, proizvod(N1, P1), P is N*P1.

proizvodNeparnih(1, 1).
proizvodNeparnih(N, P):- N > 1, N1 is N-2, proizvodNeparnih(N1, P1), P is P1*N.


cifre(0, nula).
cifre(1, jedan).
cifre(2, dva).
cifre(3, tri).
cifre(4, cetri).
cifre(5, pet).
cifre(6, sest).
cifre(7, sedam).
cifre(8, osam).
cifre(9, devet).

cifre(N):- N < 1, !.
cifre(N):- N > 0, N < 10, cifre(N, C), write(C), nl, !. 
cifre(N):- N1 is (N div 10), cifre(N1), N2 is (N mod 10), cifre(N2, C), write(C), nl.