function koef = Njutn1()

tablica;

n = length(X);

kr = zeros(n, n-1);
kr(1:n-1, 1) = diff(F);

for j = 2:n-1
    for i = 1:n-j
        kr(i, j) = kr(i+1, j-1) - kr(i, j-1);
    end
end

koef = F(1);
q = [1 0];

for j = 1:n-1
    koef = [0 koef] + kr(1, j) * q / factorial(j);
    q = conv(q, [1 -j]);
end