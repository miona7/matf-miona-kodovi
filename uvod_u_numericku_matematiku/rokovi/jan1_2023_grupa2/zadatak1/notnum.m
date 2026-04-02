function [X, p, A] = notnum(ind, i, j, n);

Z = [1, 2, 3, 4, 5];

if mod(ind, 2) == 0
    X = zeros(1, n);
    X(j) = Z(i);
    for k = 1:i-1
        X(k) = Z(k);
    end
    for k = i+1:j
        X(k-1) = Z(k);
    end
    for k = j+1:n
        X(k) = Z(k);
    end
    X
else 
    X = zeros(1, n);
    for k = 1:i-1
        X(k) = Z(k);
    end
    Y = Z(i:j);
    Y = flip(Y);
    for k = 1:length(Y)
        X(i+k-1) = Y(k);
    end
    for k = j+1:n
        X(k) = Z(k);
    end
    X
end

p = poly(X)

tmp = X' * X

A = tmp;
A(i, :) = [];
A(:, j) = [];

A

