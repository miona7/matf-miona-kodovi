function grafik(x, a, b, n)

funkcija;
[L, ~] = Lagr1b(x, a, b, n);

xx = linspace(a, b, 1000);
hold on
plot(xx, f(xx), 'r')
plot(xx, polyval(L, xx), 'b')
hold off