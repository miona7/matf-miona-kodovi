function s = simps(f, a, b, n)
X = linspace(a, b, n);
Y = f(X);
h = X(2) - X(1);
s = (h/3) * (Y(1) + 2*sum(Y(3:2:end-1)) + 4*sum(Y(2:2:end-1)) + Y(end));