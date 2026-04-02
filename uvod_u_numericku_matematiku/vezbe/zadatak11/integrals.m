function [I, briter] = integrals(a, b, tol)

n = 3;
I1 = simps(a, b, n);

n = 2*n-1;
I2 = simps(a, b, n);

briter = 2;

while (abs(I1 - I2) / 15 > tol)
    I1 = I2;
    n = 2*n-1;
    I2 = simps(a, b, n);
    briter = briter + 1;
end

I = I2;

function I = simps(a, b, n)
funkcija;
X = linspace(a, b, n);
Y = f(X);

h = X(2) - X(1);
I = (h/3) * (Y(1) + 2*sum(Y(3:2:n-1)) + 4*sum(Y(2:2:n-1)) + Y(n));


