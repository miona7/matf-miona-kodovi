function [S, A, sd] = num(a, b)

podaci;

A = Q' * Q;
A(3, :) = [];
A(:, 3) = [];
A

sd = diag(fliplr(A));
sd = sd'

P = conv(conv(P, P), P);
Q = conv(Q, Q);
f = @(x) polyval(P, x) .* polyval(Q, x);

n = 3;
I1 = simps(f, a, b, n);

n = 2*n-1;
I2 = simps(f, a, b, n);

while abs(I1-I2)/15 > tol
    I1 = I2;
    n = 2*n-1;
    I2 = simps(f, a, b, n);
end

% S = integral(f, a, b)

S = I2

xx = linspace(a, b);
plot(xx, f(xx))

function I = simps(f, a, b, n)
X = linspace(a, b, n);
Y = f(X);
h = X(2) - X(1);
I = (h/3) * (Y(1) + 2*sum(Y(3:2:n-1)) + 4*sum(Y(2:2:n-1)) + Y(end));