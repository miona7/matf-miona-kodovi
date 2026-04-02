function koef = Lagranz()

tablica;
n = length(X);
koef = 0;

for i = 1:n
    p = 1;
    for j = 1:n
        if j ~= i
            p = conv(p, [1 -X(j)]) / (X(i) - X(j));
        end
    end
    koef = koef + p*F(i);
end