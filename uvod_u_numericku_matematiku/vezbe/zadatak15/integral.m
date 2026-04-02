function I = integral(n, m, tol)

P = polinom(n, m);

br_cv = 3;
I1 = simps(@(x) polyval(P, x), br_cv);

br_cv = 2*br_cv - 1;
I2 = simps(@(x) polyval(P, x), br_cv);

while (abs(I1-I2)/15 > tol)
    I1 = I2;
    br_cv = 2*br_cv - 1;
    I2 = simps(@(x) polyval(P, x), br_cv);
end

I = I2;

function s = simps(g, br_cvorova)
f = @(x) exp(x).*g(x);
X = linspace(-1, 1, br_cvorova);
Y = f(X);

h = X(2) - X(1);
s = (h/3)*(Y(1) + 2*sum(Y(3:2:end-1)) + 4*sum(Y(2:2:end-1)) + Y(br_cvorova));