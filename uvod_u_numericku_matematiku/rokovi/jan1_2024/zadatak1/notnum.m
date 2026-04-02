function [I1, I2, I3, M] = notnum(p, a, b)

funkcija;

I1 = integral(f, a, b)

g = @(x) f(x) .* polyval(p, x);
I2 = integral(g, a, b)

I3 = integral(@(x) polyval(p, x), a, b)

X = roots(p);
X = sort(X, "descend");

M = diag(X);

k = length(X);
for i = 2 : k
    M = M + diag(X(i:end), i-1) + diag(X(i:end), -(i-1));
end

M