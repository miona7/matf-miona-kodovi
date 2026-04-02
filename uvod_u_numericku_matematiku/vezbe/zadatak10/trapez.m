function I = trapez(a, b)

funkcija;

n = 9;
X = linspace(a, b, n);
Y = f(X);

h = X(2) - X(1);
I = (Y(1) + Y(n) + 2*sum(Y(2:n-1))) * (h/2);