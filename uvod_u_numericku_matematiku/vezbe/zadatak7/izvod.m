function [X, Y, Yi] = izvod()

tablica;

X = X1;
Y = Y1;

n = length(X);

Yi = (Y(3:n) - Y(1:n-2)) ./ (X(3:n) - X(1:n-2));
