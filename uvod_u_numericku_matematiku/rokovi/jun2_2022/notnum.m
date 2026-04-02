function [X, Y] = notnum(m, n)

tmp = zeros(m, 2*m-1);

k = 1;
for i = 1:m
    for j = 1:2*i-1
        tmp(i, j) = k;
        k = k + 1;
    end
end

tmp;

X = zeros(1, m);
for i = 1:m
    X(i) = sum(tmp(i, :));
end

X

Y = X(find(X > n));
Y = sort(Y, "descend")
