function S = notnum(a, k)

if k >= a
    X = [];
    for i = 1 : k
        X = [X a^i];
    end
    X
    S = diag(X);
    for i = 2:k
        S = S + diag(X(i:end), i-1) + diag(X(i:end), -(i-1));
    end
else
    S = 1;
    for i = k : a
        if (mod(i, 1) == 0 && i < ((k+a)/2)) 
            S = S * i;
        end
    end
end