split([], [], []).
split([X | R], [X | L1], L2):- split(R, L2, L1).

insert(X, [], [X]).
insert(X, [H|T], [X,H|T]) :- X =< H.
insert(X, [H|T], [H|R]) :- X > H, insert(X, T, R).

sort([], []).
sort([X], [X]).
sort([G | R], Sortirana):- sort(R, SortiranRep), insert(G, SortiranRep, Sortirana).

% merge/3 spaja dve sortirane liste
merge([], L, L).
merge(L, [], L).
merge([H1|T1], [H2|T2], [H1|R]):- H1 =< H2, merge(T1, [H2|T2], R).
merge([H1|T1], [H2|T2], [H2|R]):- H1 > H2, merge([H1|T1], T2, R).

% mergeSort/2 sortira listu
mergeSort([], []).
mergeSort([X], [X]).
mergeSort(L, Sorted):- split(L, L1, L2), mergeSort(L1, Sorted1), mergeSort(L2, Sorted2), merge(Sorted1, Sorted2, Sorted).