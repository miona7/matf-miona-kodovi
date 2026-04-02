function x = nula(a, b, n)

[c, d] = promenaZnaka(a, b, n);
[X, Y] = tablica(c, d, n);

kr = zeros(n, 3);
kr(1:n-1, 1) = diff(Y);

for j = 2 : 3
    for i = 1 : n-j
        kr(i, j) = kr(i+1, j-1) - kr(i, j-1);
    end
end

[X' Y' kr]

q0 = 0;
q1 = -(Y(n) + kr(n-2, 2)*q0*(q0 + 1)/2 + kr(n-3, 3)*q0*(q0 + 1)*(q0 + 2)/6) / kr(n-1, 1);
Q = [q0 q1];

while (abs(q1 - q0) > 0.0001)
    q0 = q1;
    q1 = -(Y(n) + kr(n-2, 2)*q0*(q0 + 1)/2 + kr(n-3, 3)*q0*(q0 + 1)*(q0 + 2)/6) / kr(n-1, 1);
    Q = [Q q1];
end

Q'

h = X(2) - X(1);
x = h * q1 + X(n);