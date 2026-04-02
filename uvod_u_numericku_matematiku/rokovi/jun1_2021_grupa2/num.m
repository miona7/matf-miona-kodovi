function I = num(a, b, epsilon, tol)

I = [];
xx = linspace(a, b);

hold on

n = 1;
f = @(x) (2*n*x.^(n-1)) ./ (1+x);
i1 = int(f, a, b, tol);
I = [I i1];
plot(xx, f(xx));

n = 2;
f = @(x) (2*n*x.^(n-1)) ./ (1+x);
i2 = int(f, a, b, tol);
I = [I i2];
plot(xx, f(xx));

while abs(i2 - i1) > epsilon
    i1 = i2;
    n = n + 1;
    f = @(x) (2*n*x.^(n-1)) ./ (1+x);
    i2 = int(f, a, b, tol);
    I = [I i2];
    plot(xx, f(xx));
end
hold off

I = I'

function i = int(f, a, b, tol)
br_c = 3;
I1 = simps(f, a, b, br_c);

br_c = br_c * 2 - 1;
I2 = simps(f, a, b, br_c);

while abs(I2 - I1) / 15 > tol
    I1 = I2;
    br_c = br_c * 2 - 1;
    I2 = simps(f, a, b, br_c);
end

i = I2;