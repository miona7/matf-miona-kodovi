function [F, P] = notnum(f)

n = length(f);
P = 1;
for i = 1:n
    znak = (-1)^i;
    P = conv(P, [znak 0 -f(i)]);
end

P

a = ceil(max(f));

F = ones(n, n);
for i = 1:n-1
    for j = 1:n-1
        F(i+1, j+1) = a^(i*j);
    end
end

F 