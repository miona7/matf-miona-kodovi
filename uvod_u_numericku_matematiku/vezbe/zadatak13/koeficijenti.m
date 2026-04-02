function k = koeficijenti(d, t, n)

[A, b] = sistem(d, t, n);

k = A\b;