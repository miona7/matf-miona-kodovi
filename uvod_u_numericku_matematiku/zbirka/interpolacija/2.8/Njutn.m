function y = Njutn(x)

tablica;

n = length(X);
pr = zeros(n, n-1);
for i = 1:n-1
    pr(i, 1) = (Y(i+1) - Y(i)) / (X(i+1) - X(i));
end

[X' Y' pr]

for j = 2:n-1
    for i = 1:n-j
        pr(i, j) = (pr(i+1, j-1) - pr(i, j-1)) / (X(i+j) - X(i));
    end
end

y = Y(1);
p = 1;
for i = 1;n-1
    p = p * (x - X(i));
    y = y + pr(1, i) * p;
end

y