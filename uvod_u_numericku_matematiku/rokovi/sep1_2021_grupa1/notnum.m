function [A, p] = notnum(b)

n = sqrt(length(b));

A = zeros(n, n);
k = 1;
for i = 1:n
    if mod(i, 2) == 1
        for j = 1:n
            A(i, j) = b(k);
            k = k + 1;
        end
    else
        for j = n:-1:1
            A(i, j) = b(k);
            k = k + 1;
        end
    end
end

p = diag(A)';
p = [p diag(fliplr(A))'];

xx = linspace(-1, 1);
% disp(polyval(b, xx))

plot(xx, polyval(b, xx));