function [A B x] = matrica(broj, d)

B = ones(d, 1);

A = diag(ones(d, 1)*broj*10);

for i = 1 : d-1
    A = A + diag(ones(1, d-i), i) + diag(ones(1, d-i)*(broj - i), -i);
end

x = sistem(A, B);