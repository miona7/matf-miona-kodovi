prefiksi1([], Ak, [Ak]).
prefiksi1([G | R], Ak, [Ak | SviPref]):- append(Ak, [G], NoviAk), prefiksi1(R, NoviAk, SviPref).

prefiksi(L, P):- prefiksi1(L, [], P).