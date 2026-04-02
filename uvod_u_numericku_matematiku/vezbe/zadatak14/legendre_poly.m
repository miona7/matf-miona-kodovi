function L = legendre_poly(n)

L = cell(n+1, 1);

L{1} = 1;
L{2} = [1 0];

for i = 2 : n
    L{i+1} = ((2*i-1)*[L{i} 0] - (i-1)*[0 0 L{i-1}])/i;
end

xx = linspace(-1, 1);
hold on
for i = 1:n+1
    plot(xx, polyval(L{i}, xx));
end
hold off
