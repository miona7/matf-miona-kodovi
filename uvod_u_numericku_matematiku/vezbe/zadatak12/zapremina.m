function z = zapremina(a, b, tol)

n = 3;
S1 = simps(a, b, n);

n = 2*n-1;
S2 = simps(a, b, n);

while Runge(S1, S2) > tol 
    S1 = S2;
    n = 2*n-1;
    S2 = simps(a, b, n);
end

z = S2;

function I = simps(a, b, n)
funkcija;
X = linspace(a, b, n);
Y = f(X).^2 * pi;
h = X(2) - X(1);
I = (h/3) * (Y(1) + 4*sum(Y(2:2:n-1)) + 2*(sum(Y(3:2:n-1))) + Y(n));