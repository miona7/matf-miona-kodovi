function [X, Y, Y2i] = drugiizvod()

tablica;

X = X1;
Y = Y1;

n = length(X);
h = X(2) - X(1);
Y2i = (Y(1:n-2) + Y(3:n) - 2.*Y(2:n-1)) / h^2;