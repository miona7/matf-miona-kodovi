function [T, nule] = notnum(f, n, y)

T = f(y);
p = [1 -y];

for i = 1 : n
    F = sym(f);
    F1 = diff(F);
    f1 = matlabFunction(F1);
    f = f1;

    koef = f1(y) / factorial(i);
    
    T = [0 T] + koef * p;

    p = conv(p, [1 -y]);
end

T
nule = sort(roots(T), 'descend')';

T1 = polyder(T)

xx = linspace(-1, 1);

hold on
plot(xx, polyval(T, xx))
plot(xx, polyval(T1, xx))
hold off