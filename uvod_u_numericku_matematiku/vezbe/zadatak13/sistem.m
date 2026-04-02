function [A, b] = sistem(d, t, n)

A = zeros(n+1, n+1);
b = zeros(n+1, 1);

f = [0 1];
for i = 0 : n
    g = @(x) t(x) .* polyval(f, x);
    b(i + 1) = integral1(g, 0, d);
    for j = 0 : n
        A(i+1, j+1) = polyval(f, j*d/n);
    end
    f = [f 0];
end

b