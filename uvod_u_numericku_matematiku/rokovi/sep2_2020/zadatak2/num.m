function I = num(n)

C = cell(n, 1);
C{1} = [1];
C{2} = [1 0];

for i = 2:n
    C{i+1} = 2 * conv([1 0], C{i}) - [0 0 C{i-1}];
end

celldisp(C)
xx = linspace(-1, 1);
hold on
for i = 1:2:n
    plot(xx, polyval(C{i}, xx))
end
hold off

podaci;

X = zeros(1, n);
for i = 1:n
    X(i) = cos(((2*i-1)*pi)/(2*n));
end

X
Y = f(X)

I = (pi/n) * sum(Y(:));  