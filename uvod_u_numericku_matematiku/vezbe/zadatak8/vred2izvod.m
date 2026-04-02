function y = vred2izvod(x)

[X, ~, Y2i] = drugiizvod();
n = length(X);

X = X(2:n-1);
n = n - 2;

kr = zeros(n, n-1);
kr(1:n-1, 1) = diff(Y2i);

for j = 2 : n-1
    for i = 1 : n-j
        kr(i, j) = kr(i+1, j-1) - kr(i, j-1);
    end
end

[X' Y2i' kr]

h = X(2) - X(1);
q = (x - X(1)) / h;

y = Y2i(1);
p = q;
for j = 1 : n-1
    y = y + kr(1, j) * p / factorial(j);
    p = p * (q - j);
end