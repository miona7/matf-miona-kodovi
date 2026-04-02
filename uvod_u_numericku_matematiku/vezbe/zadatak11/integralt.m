function [I, briter] = integralt(a, b, tol)

n = 3;
I1 = trapez(a, b, n);

n = 2*n-1;
I2 = trapez(a, b, n);

briter = 2;

while (abs(I1 - I2) / 3 > tol)
    I1 = I2;
    n = 2*n-1;
    I2 = trapez(a, b, n);
    briter = briter + 1;
end

I = I2;

function I = trapez(a, b, n)
funkcija;
X = linspace(a, b, n);
Y = f(X);

h = X(2) - X(1);
I = (h/2) * (Y(1) + 2*sum(Y(2:n-1)) + Y(n));


