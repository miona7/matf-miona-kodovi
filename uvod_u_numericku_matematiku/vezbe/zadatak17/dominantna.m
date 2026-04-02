function d = dominantna(A)

d = 1;

[n, ~] = size(A);

for i = 1 : n
    if sum(abs(A(i, :))) - abs(A(i, i)) > abs(A(i, i))
        d = 0;
        break;
    end
end