function [L, y] = Lagr1b(x, a, b, n)

[X, Y] = tablica(a, b, n);

L = 0;
for i = 1 : n
    p = 1;
    for j = 1 : n
        if j ~= i
            p = conv(p, [1, -X(j)]) / (X(i) - X(j));
        end
    end
    L = L + p * Y(i);
end
y = polyval(L, x);
