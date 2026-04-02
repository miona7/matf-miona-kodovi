function [c, d] = promenaZnaka(a, b, n)

[X, Y] = tablica(a, b, n);

i = 1;
while (i < n && Y(i) * Y(i+1) > 0)
    i = i + 1;
end

c = X(i);
d = X(i+1);