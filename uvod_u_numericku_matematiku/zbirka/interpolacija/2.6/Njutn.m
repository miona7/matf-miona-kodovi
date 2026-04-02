function y = Njutn(x)

tablica;

n = length(X);
kr = zeros(n, n-1);
for j = 1:n-1
    kr(j, 1) = round(Y(j+1) - Y(j), 6); 
end

for j = 2:n-1
    for i = 1:n-j
        kr(i, j) = kr(i+1, j-1) - kr(i, j-1);
    end
end

[X' Y' kr]

h = X(2) - X(1);
q = (x - X(n)) / h;

y = Y(n);
for i = 1:4
    y = y + q * kr(n-i, i) / factorial(i);
    q = q * (q+i);
end
y