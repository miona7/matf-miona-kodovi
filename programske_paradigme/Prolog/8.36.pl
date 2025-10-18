sufiksi([], [[]]).
sufiksi([G | R], [[G | R] | T]):- sufiksi(R, T).
