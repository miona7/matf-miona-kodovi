function x = nula()

[X, ~, Yi] = izvod();

n = length(X);
X = X(2:n-1);
n = n - 2;

[X1, I] = sort(Yi, 'descend');
Y1 = X(I);

pr = zeros(n, n-1);
pr(1:n-1, 1) = diff(Y1) ./ diff(X1);

for j = 2 : n-1
    for i = 1 : n-j
        pr(i, j) = (pr(i+1, j-1) - pr(i, j-1)) / (X1(i+j) - X1(i));
    end
end

[X1' Y1' pr]

x = Y1(1);
p = 1;
for j = 1 : n-1
    p = p * (-X1(j));
    x = x + p * pr(1, j);
end