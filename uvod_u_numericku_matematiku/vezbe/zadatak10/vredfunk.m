function [X, Y] = vredfunk(k, p)

X = 2:k;
n = length(X);
Y = zeros(1, n);

for i = 1 : n
    if p == 1
        Y(i) = simps(1, X(i));
    else
        if p == 2
            Y(i) = trapez(1, X(i));
        else
            error('Nedozvoljeno p');
        end
    end
end

[X' Y']