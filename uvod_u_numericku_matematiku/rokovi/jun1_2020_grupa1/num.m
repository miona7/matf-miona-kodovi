function [L, L1, y1] = num(x, a, b, tol)

podaci;
n = 2;
while abs(f(x) - lagr(x, a, b, n)) > tol
    n = n + 1;
end

X = linspace(a, b, n);
Y = f(X);

L = 0;
for i = 1:n
    p = 1;
    for j = 1:n
        if i ~= j
            p = conv(p, [1 -X(j)]) / (X(i) - X(j));
        end
    end
    L = L + p * Y(i);
end

L1 = polyder(L)
y1 = polyval(L1, x)

function y = lagr(x, a, b, n);
podaci;
X = linspace(a, b, n);
Y = f(X);

y = 0;
for i = 1:n
    p = 1;
    for j = 1:n
        if i ~= j
            p = p * (x - X(j)) / (X(i) - X(j));
        end
    end
    y = y + p * Y(i);
end