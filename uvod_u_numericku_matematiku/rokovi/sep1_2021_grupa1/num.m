function X = num(f, tol, x1, x2)

podaci;

X = [];
for i = 1:length(C)
    g = @(x) f(x) - C(i)*x;
    s = secica(g, tol, x1, x2);
    X = [X s];
end


function s = secica(g, tol, x1, x2)
x0 = x1;
x1 = x2;
x2 = x1 - (g(x1)*(x0-x1)) / (g(x0)-g(x1));

while abs(x2 - x1) > tol
    x0 = x1;
    x1 = x2;
    x2 = x1 - (g(x1)*(x0-x1)) / (g(x0)-g(x1));
end

s = x2;