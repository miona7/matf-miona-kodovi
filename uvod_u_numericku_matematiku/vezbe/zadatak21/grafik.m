function grafik(x0, iterM)

tol = 10^-4:10^-4:10^-3;

n = length(tol);

briter = zeros(1, n);

for i = 1 : n
    [~, briter(i)] = nula(x0, tol(i), iterM);
end

plot(tol, briter)