function y = vredizvod(x)

[X, ~, Yi] = izvod();
n = length(X);

X = X(2:n-1);
n = n - 2;

pr = zeros(n, n-1);
pr(1:n-1, 1) = diff(Yi) ./ diff(X);

for j = 2 : n-1
    for i = 1 : n-j
        pr(i, j) = (pr(i+1, j-1) - pr(i, j-1)) / (X(i+j) - X(i));
    end
end

[X' Yi' pr]

y = Yi(1);
p = 1;
for j = 1 : n-1
    p = p * (x - X(j));
    y = y + p * pr(1, j);
end
