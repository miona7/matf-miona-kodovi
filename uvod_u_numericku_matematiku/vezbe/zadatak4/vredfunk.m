function [Nj, y] = vredfunk(x)

t = tablicaCheck();
if t == 0
    error('Nisu ispunjeni uslovi')
end

tablica;
n = length(X);
pr = zeros(n, n-1);

pr(1:n-1, 1) = diff(Y) ./ diff(X);

for j = 2 : n-1
    for i = 1 : n-j
        pr(i, j) = (pr(i+1, j-1) - pr(i, j-1)) / (X(i+j) - X(i));
    end
end

[X' Y' pr]

y = Y(1);
p = 1;
for j = 1 : n-1
    p = p * (x - X(j));
    y = y + pr(1, j) * p; 
end

Nj = Y(1);
p = 1;
for j = 1 : n-1
    p = conv(p, [1, - X(j)]);
    Nj = [0 Nj] + pr(1, j) * p; 
end

Nj
y