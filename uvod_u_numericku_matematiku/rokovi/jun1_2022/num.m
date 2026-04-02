function num(tol)

podaci;

g = @(x) g1(x).^2 - g2(x)

briter = 1;
disp([briter, x0, g(x0)]);

briter = briter + 1;
disp([briter, x1, g(x1)]);

briter = briter + 1;
x2 = x1 - (g(x1) * (x0 - x1)) / (g(x0) - g(x1));
disp([briter, x2, g(x2)]);

while abs(x2 - x1) > tol
    x0 = x1;
    x1 = x2;
    x2 = x1 - (g(x1) * (x0 - x1)) / (g(x0) - g(x1));
    briter = briter + 1;
    disp([briter, x2, g(x2)]);
end