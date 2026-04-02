function [L, y, R] = Lagranz(x)

[X, Y] = tablica();

n = length(X);
L = 0;
for i = 1:n
    q = 1;
    for j = 1:n
        if j ~= i
            q = conv(q, [1, -X(j)]) / (X(i) - X(j));
        end
    end
    L = L + q * Y(i);
end
disp('rezultat')
y = polyval(L, x)
disp('koeficijenti polinoma')
L
disp('greska')
R = 0.72 / 24;
for i = 1:n
    R = R * (x - X(i));
end
R = abs(R)