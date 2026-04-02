function P = polinom(n, m)

L = legendre(n);

for i = 1 : m
    L = polyder(L);
end

P = conv([-1 0 1], L);