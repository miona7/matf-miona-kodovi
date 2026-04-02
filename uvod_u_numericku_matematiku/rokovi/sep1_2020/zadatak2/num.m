function [L, x] = num(g, y)

podaci;

n = length(X);
s = sum(X(1:end)) / n;
tmp = [];
for i = 1:n
    if X(i) > s
        tmp = [tmp X(i)];
    end
end

X = tmp;
Y = g(X);

[X1, I] = sort(Y);
Y1 = X(I);

n = length(X1);
L = 0;
for i = 1:n
    p = 1;
    for j = 1:n
        if j ~= i
            p = conv(p, [1 -X1(j)]) / (X1(i) - X1(j));
        end
    end
    L = L + p * Y1(i);
end
L
x = polyval(L, y)

xx = linspace(X1(1), X1(end));
hold on
plot(xx, polyval(xx))
hold off