function nj = Njutn1(x)

tablica;
n = length(X);

kr = zeros(n, n-1);
kr(1:n-1, 1) = diff(Y);

for j = 2 : n-1
    for i = 1 : n-j
        kr(i, j) = kr(i+1, j-1) - kr(i, j-1);
    end
end

[X' Y' kr]

h = X(2) - X(1);
q = (x - X(1)) / h;

nj = Y(1);
p = q;
for j = 1 : n-1
    nj = nj + kr(1, j) * p / factorial(j);
    p = p * (q - j);
end


