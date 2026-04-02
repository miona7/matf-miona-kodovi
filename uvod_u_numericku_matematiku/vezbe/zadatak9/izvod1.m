function y = izvod1(x)

tablica;

n = length(X);

kr = zeros(n, 4);
kr(1:n-1, 1) = diff(Y);

for j = 2 : 4
    for i = 1 : n-j
        kr(i, j) = kr(i+1, j-1) - kr(i, j-1);
    end
end

[X' Y' kr]

h = X(2) - X(1);
q = (x - X(1)) / h;

y = (kr(1, 1) + kr(1, 2)*(2*q-1)/2 + kr(1, 3)*(3*q^2 - 6*q + 2)/6 ...
        + kr(1, 4)*(4*q^3 - 18*q^2 + 22*q - 6)/24) / h;