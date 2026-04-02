function [R, y] = Njutn(x)

tablica;

n = length(X);
kr = zeros(n, n-1);
for i = 1:n-1
    kr(i, 1) = Y(i+1) - Y(i);
end

for j = 2:n-1
    for i = 1:n-j
        kr(i, j) = kr(i+1, j-1) - kr(i, j-1);
    end
end

disp([X' Y' kr]);

h = X(2) - X(1);
q = (x - X(1)) / h;

y = Y(1);
for i = 1:3
    y = y + kr(1, i) * q / factorial(i);
    q = q * (q - i);
end

y

q = (x - X(1)) / h;
R = q;
for i = 1:3
    q = q * (q - i);
    R = R * q;
end

R = R / 24;
R = R * (8 * 10^-4 + 10^-4);
R