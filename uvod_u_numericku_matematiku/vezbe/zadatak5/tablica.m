function [X1, Y1] = tablica()

podaci;

X1 = X(mod(X, 2) == 0);
Y1 = round(f(X1), 3);