function i = inverz(A)

i = [];

[n, m] = size(A);

E = eye(n);

for j = 1 : m
    tmp = LUdekompozicija(A, E(:, j));
    i = [i tmp];
end