function notnum(g, x)

b = 2;
while g(1) * g(b) < 0
    b = b + 1;
end

G = sym(g);
G1 = diff(G);
g1 = matlabFunction(G1);

xx = linspace(1, b);
hold on 
plot(xx, xx)
title('bla')
xlabel('x');
ylabel('y');
hold off