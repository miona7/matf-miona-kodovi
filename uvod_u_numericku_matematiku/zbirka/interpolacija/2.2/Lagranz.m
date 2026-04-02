function [L, y, R] = Lagranz(x)

[X, Y] = tablica();

n = length(X);
L = 0;
for i = 1:n
    p = 1;
    for j = 1:n
        if j ~= i
            p = conv(p, [1; -X(j)] / (X(i) - X(j)));
        end
    end
    L = L + p * Y(i);
end

disp('rezultat')
y = polyval(L, x)
disp('koeficijenti')
L
disp('greska')
R = 1.15 / 24
for i = 1:n
    R = R * (x - X(i));
end
R