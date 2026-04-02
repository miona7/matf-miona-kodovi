function x = inverz(y)
 
[X, Y] = tablica();

disp([X' Y'])

[X1, I] = sort(Y);
Y1 = X(I);

disp([X1' Y1'])

x = Lagr(y, X1, Y1);

function L = Lagr(x, X, Y)

n = length(X);
L = 0;
for i = 1 : n
    p = 1;
    for j = 1 : n
        if j ~= i
            p = p * (x - X(j)) / (X(i) - X(j));
        end
    end
    L = L + p * Y(i);
end
