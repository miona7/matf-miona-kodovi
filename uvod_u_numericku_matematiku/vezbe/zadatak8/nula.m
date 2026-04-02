function x = nula()

[X, ~, Y2i] = drugiizvod();
n = length(X);

X = X(2:n-1);
n = n - 2;

kr = zeros(n, n-1);
kr(1:n-1, 1) = diff(Y2i);

for j = 2 : n-1
    for i = 1 : n-j
        kr(i, j) = kr(i+1, j-1) - kr(i, j-1);
    end
end

[X' Y2i' kr]

q0 = 0;
q1 = (Y2i(1) + kr(1, 2)*q0*(q0-1)/2 + kr(1, 3)*q0*(q0-1)*(q0-2)/6) / (-kr(1, 1));

while (abs(q0-q1) > 0.0001)
    q0 = q1;
    q1 = (Y2i(1) + kr(1, 2)*q0*(q0-1)/2 + kr(1, 3)*q0*(q0-1)*(q0-2)/6) / (-kr(1, 1));
end

h = X(2) - X(1);
x = X(1) + q1 * h;