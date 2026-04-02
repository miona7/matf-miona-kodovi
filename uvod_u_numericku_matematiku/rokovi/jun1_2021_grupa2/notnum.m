function [A, k, a] = notnum(v)

k = 0;
a = -1;
for i = 1:length(v)
    if v(i) > 0 && mod(v(i), 2) == 0
        k = k + 1;
        a = i;
    end
end

k

a

A = zeros(2*k-1, 2*k-1);

for i = 1 : 2*k-1
    for j = 1 : 2*k-1
        stepen = max(abs(i-k), abs(j-k)) + 1;
        A(i, j) = a ^ stepen;
    end
end

A