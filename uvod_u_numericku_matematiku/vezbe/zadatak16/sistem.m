function x = sistem(A, B)

[n, m] = size(A);

A1 = zeros(n);
B1 = zeros(n, 1);

for i = 1 : n
    A1(i, :) = -A(i, :)/A(i, i);
    A1(i, i) = 0;
    B1(i) = B(i) / A(i, i);
end

x = B1;

for i = 1 : 50
    x = A1*x + B1;
end

