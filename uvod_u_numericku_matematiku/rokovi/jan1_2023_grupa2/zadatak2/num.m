function L = num(a, b, tol)

f = @(x) 2 .* cos(x) + 3;

F = sym(f);
F1 = diff(F);

f1 = matlabFunction(F1);

g = @(x) sqrt(1 + f1(x).^2)

n = 3;
I1 = simps(g, a, b, n);

n = 2*n-1;
I2 = simps(g, a, b, n);

while abs(I1-I2) / 15 > tol
    I1 = I2;
    n = 2*n-1;
    I2 = simps(g, a, b, n);
end

L = I2;



function I = simps(g, a, b, n)
X = linspace(a, b, n);
Y = g(X);

h = X(2) - X(1);
I = (h/3) * (Y(1) + Y(n) + 2 * sum(Y(3:2:n-1)) + 4 * sum(Y(2:2:n-1)));
