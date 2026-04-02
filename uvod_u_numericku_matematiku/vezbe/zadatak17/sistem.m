function [iter, x] = sistem(A, B, tol)

d = dominantna(A);

if d == 0
    error('Matrica nije dijagonalno dominantna');
end

[n, ~] = size(A);

A1 = zeros(n);
B1 = zeros(n, 1);

for i = 1 : n
    A1(i, :) = -A(i, :) / A(i, i);
    A1(i, i) = 0;
    B1(i) = B(i) / A(i, i);
end

x0 = B1;
x1 = x0;

iter = 0;

while 1
    for i = 1 : n
        x1(i) = A1(i, :)*x1 + B1(i);
    end

    if all(abs(x0 - x1)) <= tol
        break;
    end

    iter = iter + 1;
    x0 = x1;
end

x = x1;
x