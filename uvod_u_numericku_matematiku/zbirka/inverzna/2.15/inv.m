function x = inv(y)

[X1, Y1] = tablica();

[X, I] = sort(Y1);
Y = X1(I);
n = length(X);

x = 0;
for i = 1:n
    p = 1;
    for j = 1:n
        if i ~= j
            p = p * ((y - X(j)) / (X(i) - X(j)));
        end
    end
    x = x + p * Y(i);
end



x