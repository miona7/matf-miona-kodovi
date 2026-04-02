function [P, pr] = num(g, n)

n = n+1;
X = linspace(0, 20, n);
Y = g(X);

pr = zeros(n, n-1);

pr(1:n-1, 1) = diff(Y) ./ diff(X);

for j = 2:n-1
    for i = 1:n-j
        pr(i, j) = (pr(i+1, j-1) - pr(i, j-1)) / (X(i+j) - X(i));
    end
end

[X' Y' pr]

P = Y(1);
p = 1;
for j = 1:n-1
    p = conv(p, [1 -X(j)]);
    P = [0 P] + pr(1, j)*p;
end

P


xx = linspace(0, 20, n);
plot(xx, g(xx))