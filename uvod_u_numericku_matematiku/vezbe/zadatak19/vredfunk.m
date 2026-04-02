function y = vredfunk(x)

tablica;

y = 0;
for i = 1 : n
    p = 1;
    for j = 1 : n
        if j ~= i
            p = p * ((x - X(j)) / (X(i) - X(j)));
        end
    end
    y = y + p*Y(i);
end



