function grafik(a, b)

tol = 10.^[-1:-1:-6];
n = length(tol);
brt = zeros(1, n);
brs = zeros(1, n);

for i = 1 : length(tol)
    [~, brt(i)] = integralt(a, b, tol(i));
    [~, brs(i)] = integrals(a, b, tol(i));
end

plot(tol, brt, 'r', tol, brs, 'b');